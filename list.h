#ifndef LISTH__
#define LISTH__
#include "date.h"

typedef struct id_data_struct
{
    date date;
    int id_code;

} id_data;

struct id_node_struct
{
    id_data data;
    struct id_node_struct *next;
};

typedef struct id_node_struct id_node;

typedef id_node *header_node;

#endif