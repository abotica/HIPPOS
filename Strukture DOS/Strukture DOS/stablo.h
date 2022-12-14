#ifndef STABLO_H
#define STABLO_H

#define MAX_FILE_NAME 256
#include "stog.h"
#include "struktura_stablo.h"
#include "struktura_stog.h"

tree_p make_root(void);
int make_dir(tree_p);
int print_directories(tree_p);
tree_p change_dir(tree_p, position, tree_p);

#endif // !STABLO_H
