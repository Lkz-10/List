#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#define DEBUG

typedef int list_elem_t;

#ifdef DEBUG
    #define ON_DEBUG(...) __VA_ARGS__
    #define LIST_VERIFY                                \
        if (ListVerify(list) != 0) return -1;
#else
    #define ON_DEBUG(...)
    #define LIST_VERIFY
#endif

#define INSERT(index, val)                             \
    if (ListInsert(&list, index, val) != 0) return -1;

#define ERASE(index)                                   \
    if (ListErase(&list, index) != 0) return -1;

const list_elem_t POISON        = -111111;
const int         LIST_MIN_SIZE = 2;

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
