#include <stdio.h>
#include <stdlib.h>

#include "ListFunctions.h"

int main(const int argc, const char** argv)
{
    if (argc < 2) return -1;

    List_t list = {};
    if (ListCtor(&list) != 0) return -1;

    INSERT(0, 31)
    INSERT(0, 25)
    INSERT(1, 30)

    ListErase(&list, 2);

    ListDump(&list, argv[1]);

    ListDtor(&list);

    return 0;
}
