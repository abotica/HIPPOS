#ifndef STOG_H
#define STOG_H
#include "stablo.h"
#include <stdio.h>
#include <stdlib.h>

struct stack;
typedef struct stack* position;

typedef struct stack {

	tree_p dir_address;
	position next;

}stack;

int create_head();

int push(tree_p, position);

tree_p pop(position);










#endif // !STOG_H