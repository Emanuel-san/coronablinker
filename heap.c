#include <stdio.h>
#include <stdlib.h>
#include "date.h"
#include "heap.h"

idNode heapCreate(int MAX_SIZE)
{
    idNode tmp = (idNode)malloc(sizeof(struct idNodeStruct));
    /* Vi utgår här från att endast positiva prioriteter > 0 förekommer */
    // memset(tmp->data, 0, MAX_SIZE * sizeof(int));
    tmp->last = -1;
    return tmp;
}