#include <stdio.h>
#include <stdlib.h>

#include "ListFunctions.h"

int main(ON_DEBUG(const int argc, const char** argv))
{
    if (argc < 2) return -1;

    List_t list = {};
    if (ListCtor(&list) != 0) return -1;

    INSERT(0, 32)
    INSERT(0, 25)
    INSERT(1, 30)
    INSERT(0, 1)

    ERASE(2)

    INSERT(3, 1925)

    ListDump(&list, argv[1]);

    ListDtor(&list);

    return 0;
}
