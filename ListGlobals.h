#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#define LIST_VERIFY                                    \
    if (ListVerify(list) != 0) return -1;

#define INSERT(index, val)                             \
    if (ListInsert(&list, index, val) != 0) return -1;

typedef int list_elem_t;

const list_elem_t POISON        = -111111;
const int         LIST_MIN_SIZE = 16;

struct List_t
{
    int          count;
    int          size;
    int          free;
    list_elem_t* data;
    int*         next;
    int*         prev;

};

#endif
