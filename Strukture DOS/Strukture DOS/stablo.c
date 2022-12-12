#define _CRT_SECURE_NO_WARNINGS
#include "stablo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int make_root() {
	tree_p root = (tree_p)malloc(sizeof(tree));

	if (root == NULL) {
		perror("Error while allocating memory!\n");
		return 1;
	}

	root->children = NULL;
	root->siblings = NULL;
	strcpy(root->directory, "C");

	return 0;
}

int make_dir(tree_p current_dir) {

	current_dir->siblings = (tree_p)malloc(sizeof(tree));

	if (current_dir->siblings == NULL) {
		perror("Error while allocating memory!\n");
		return 1;
	}

	scanf("%s", &current_dir->siblings->directory);

	return 0;
}


