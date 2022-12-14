#ifndef STRUKTURA_STABLO_H
#define STRUKTURA_STABLO_H


struct tree;
typedef struct tree* tree_p;

typedef struct tree {

	char directory[MAX_FILE_NAME];
	tree_p siblings;
	tree_p children;
	char time[100];

}tree;



#endif // !STRUKTURA_STABLO_H
