#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct node
{
    struct node * prev;
    struct node * next;
};

struct info
{
	int data;
	struct node myNodeData;
};

enum my_enum
{
    NULL_Pointer_passed,
    Destroyed,
    inserted_at_beginning,
    inserted_at_end,
    inserted_in_middle,
    deleted_at_beginning,
    deleted_at_end,
    deleted_in_middle,
    got_size
};