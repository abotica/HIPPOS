#ifndef STRUKTURA_STOG_H
#define STRUKTURA_STOG_H

#include "struktura_stablo.h"

struct stack;
typedef struct stack* position;

typedef struct stack {

	tree_p dir_address;
	position next;

}stack;



#endif // !STRUKTURA_STOG_H
