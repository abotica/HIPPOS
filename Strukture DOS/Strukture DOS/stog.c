#define _CRT_SECURE_NO_WARNINGS

#include "stog.h"
#include "stablo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int create_root(position head, tree_p root_address) {
	
	position root_el = (position)malloc(sizeof(stack));
	
	if (NULL == root_el) {
		perror("Error while allocating memory!\n");
		return 1;
	}

	root_el->next = NULL;
	root_el->dir_address = root_address;

	head->dir_address = NULL;
	head->next = root_el;

	
	return 0;
}

int push(tree_p prev_directory, position head) {
	position q = (position)malloc(sizeof(stack));

	if (NULL == q) {
		perror("Error while allocating memory!\n");
		return 1;
	}

	q->dir_address = prev_directory;	//prev_directory is address of previous directory before changing directories

	q->next = head->next;
	head->next = q;

	return 0;
}

tree_p pop(position head, tree_p root_address) {

	tree_p dir_address = NULL;
	position temp = head->next;
	
	if (temp->dir_address == root_address) return root_address;	

	dir_address = temp->dir_address;
	head->next = temp->next;
	free(temp);

	return dir_address;	//address of dir
}