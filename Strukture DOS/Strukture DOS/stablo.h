#ifndef STABLO_H
#define STABLO_H
#define MAX_FILE_NAME 256


struct tree;
typedef struct tree* tree_p;

typedef struct tree {

	char directory[MAX_FILE_NAME];
	tree_p siblings;
	tree_p children;

}tree;

int make_root();
int make_dir(tree_p current_dir);







#endif // !STABLO_H
