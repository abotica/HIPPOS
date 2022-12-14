#ifndef STOG_H
#define STOG_H

#include "stablo.h"
#include <stdio.h>
#include <stdlib.h>
#include "struktura_stog.h"
#include "menu.h"

int create_root(position, tree_p);

int push(tree_p, position);

tree_p pop(position, tree_p);

#endif // !STOG_H