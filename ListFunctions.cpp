#include "ListFunctions.h"

int ListInsert(List_t* list, int index, list_elem_t val)
{
    //ListDump(list, "Dump.dot");
    LIST_VERIFY

    if (index < 0 || index > list->count)
    {
        fprintf(stderr, "Wrong index for insertion: %d (count = %d)\n", index, list->count);
        ListDtor(list);

        return -1;
    }

    if (list->free == 0)
    {
        if (ListRealloc(list) != 0) return -1;
        //ListDump(list, "Dump.dot");
    }

    (list->count)++;

    int free_index = list->free;

    list->free = list->next[free_index];

    int real_index = 0;

    for (int i = 0; i < index; ++i)
    {
        real_index = list->next[real_index];
    }

    index = real_index;

    list->next[free_index] = list->next[index];
    list->next[index]      = free_index;

    list->prev[list->next[free_index]] = free_index;
    list->prev[free_index]             = index;

    list->data[free_index] = val;

    return 0;
}

int ListRealloc(List_t* list)
{
    LIST_VERIFY

    list->data = (list_elem_t*) realloc(list->data, (list->size * 2) * sizeof(list_elem_t));
    list->next = (int*)         realloc(list->next, (list->size * 2) * sizeof(list_elem_t));
    list->prev = (int*)         realloc(list->prev, (list->size * 2) * sizeof(list_elem_t));

    if (list->data == NULL || list->next == NULL || list->prev == NULL)
    {
        fprintf(stderr, "Reallocation error!\n");
        ListDtor(list);

        return -1;
    }

    list->free = list->size;

    for (int i = list->size; i < list->size * 2 - 1; ++i)
    {
        list->data[i] = POISON;
        list->next[i] = i + 1;
        list->prev[i] = -1;
    }

    list->size *= 2;

    list->data[list->size-1] = POISON;
    list->next[list->size-1] = 0;
    list->prev[list->size-1] = -1;

    return 0;
}

int ListErase(List_t* list, int index)
{
    LIST_VERIFY

    if (index < 1 || index > list->count)
    {
        fprintf(stderr, "Wrong index for removing: %d (count = %d)\n", index, list->count);
        ListDtor(list);

        return -1;
    }

    int real_index = 0;

    for (int i = 0; i < index; ++i)
    {
        real_index = list->next[real_index];
    }

    index = real_index;

    list->next[list->prev[index]] = list->next[index];
    list->prev[list->next[index]] = list->prev[index];

    list->next[index] = list->free;
    list->prev[index] = -1;
    list->data[index] = POISON;

    list->free = index;

    (list->count)--;

    return 0;
}

int ListDump(List_t* list, const char* file_name)
{
    FILE* file_ptr = fopen(file_name, "w");

    fprintf(file_ptr, "digraph G\n{\n   rankdir=LR;\n");

    fprintf(file_ptr, "   info [shape = Mrecord, label = \"size = %3d | count = %3d | free = %3d\" ];\n",
            list->size, list->count, list->free);

    for (int i = 0; i < list->size; ++i)
    {
        fprintf(file_ptr, "%4d [shape = Mrecord, label = \"%3d | data = %7d | prev = %3d | next = %3d\" ];\n",
                i, i, list->data[i], list->prev[i], list->next[i]);
    }

    fprintf(file_ptr, "   edge[color=\"green\"];\n");

    for (int i = 0; i < list->size; ++i)
    {
        fprintf(file_ptr, "%4d -> %d;\n", i, list->next[i]);
    }

    fprintf(file_ptr, "   edge[color=\"blue\"];\n");

    for (int i = 0; i < list->size; ++i)
    {
        if (list->prev[i] == -1) continue;
        fprintf(file_ptr, "%4d -> %d;\n", list->prev[i], i);
    }

    fprintf(file_ptr, "}\n");

    fclose(file_ptr);

    system("dot Dump.dot -Tpng -o Dump.png");

    return 0;
}

int ListVerify(List_t* list)
{
    assert(list);
    assert(list->data);
    assert(list->next);
    assert(list->prev);

    int index = list->free;

    while (index != 0 && list->next[index] != 0)
    {
        if (list->prev[index] != -1)
        {
            fprintf(stderr, "Empty element error!\n");
            ListDtor(list);

            return -1;
        }

        index = list->next[index];
    }

    for (int i = 1; i < list->size; ++i)
    {
        if (list->prev[i] != -1 && list->prev[i] != 0 && list->next[i] != 0 &&
            (list->next[list->prev[i]] != i || list->prev[list->next[i]] != i))
        {
            fprintf(stderr, "List verification error\n");
            ListDtor(list);

            return -1;
        }
    }

    return 0;
}

int ListCtor(List_t* list)
{
    list->size = LIST_MIN_SIZE;
    list->free = 1;

    list->data = (list_elem_t*) calloc(LIST_MIN_SIZE, sizeof(list_elem_t));
    assert(list->data);

    list->prev = (int*) calloc(LIST_MIN_SIZE, sizeof(int));
    assert(list->prev);

    list->next = (int*) calloc(LIST_MIN_SIZE, sizeof(int));
    assert(list->next);

    list->data[0] = POISON;
    list->next[0] = 0;
    list->prev[0] = 0;

    for (int i = 1; i < LIST_MIN_SIZE; ++i)
    {
        list->data[i] = POISON;
        list->next[i] = (i + 1) % LIST_MIN_SIZE;
        list->prev[i] = -1;
    }

    return 0;
}

int ListDtor(List_t* list)
{
    list->size = 0;
    list->free = 1;

    free(list->data);
    free(list->next);
    free(list->prev);

    list->data = NULL;
    list->next = NULL;
    list->prev = NULL;

    return 0;
}
