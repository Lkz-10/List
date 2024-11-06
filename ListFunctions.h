#ifndef __LIST_FUNCTIONS_H__
#define __LIST_FUNCTIONS_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "ListGlobals.h"

int ListCtor    (List_t* list);
int ListDtor    (List_t* list);

int ListVerify  (List_t* list);
int ListDump    (List_t* list, const char* file_name, const char* dump_reason);

int ListInsert  (List_t* list, int index, list_elem_t val);
int ListRealloc (List_t* list);

int ListErase   (List_t* list, int index);

#endif
