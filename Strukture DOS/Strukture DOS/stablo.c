#define _CRT_SECURE_NO_WARNINGS
#include "stablo.h"
#include "stog.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "menu.h"

tree_p make_root() {
	tree_p root = (tree_p)malloc(sizeof(tree));
	
	if (root == NULL) {
		perror("Error while allocating memory!\n");
		return NULL;
	}

	root->children = NULL;
	root->siblings = NULL;
	strcpy(root->directory, "C:\\");


	return root;
}

int insert_before(tree_p q, tree_p current_dir) {
	q->siblings = current_dir->children;
	current_dir->children = q;
	return 0;
}

int insert_after(tree_p q, tree_p sub_dir) {
	q->siblings = sub_dir->siblings;
	sub_dir->siblings = q;
	return 0;
}

int make_dir(tree_p current_dir) {
	time_t t = time(NULL);
	struct tm* p = localtime(&t);
	char s[1000] = { 0 };

	if (NULL == current_dir->children) {
		current_dir->children = (tree_p)malloc(sizeof(tree));
		
		if (current_dir->children == NULL) {
			perror("Error while allocating memory!\n");
			return 1;
		}

		scanf("%s", &current_dir->children->directory);

		current_dir->children->siblings = NULL;
		current_dir->children->children = NULL;

		strftime(s, 1000, "%d/%m/%Y  %H:%M:%S", p);
		strcpy(current_dir->children->time, s);


	}
	else {

		tree_p new_dir = (tree_p)malloc(sizeof(tree_p));
		tree_p sub_dir = current_dir->children;

		if (new_dir == NULL) {
			perror("Error while allocating memory!\n");
			return 1;
		}

		scanf("%s", &new_dir->directory);
		new_dir->children = NULL;
		new_dir->siblings = NULL;
		
	

		/*sorted input*/
		if (strcmp(current_dir->children->directory, new_dir->directory) > 0) {
			insert_before(new_dir, current_dir);
			strftime(s, 1000, "%d/%m/%Y  %H:%M:%S", p);
			strcpy(new_dir->time, s);
		}
		else {
			while (sub_dir->siblings != NULL && strcmp(new_dir->directory, sub_dir->siblings->directory) > 0) {

				if (strcmp(new_dir->directory, sub_dir->directory) == 0) {
					printf("A subdirectory or file %s already exists.\n", new_dir->directory);	//problem kod duplikata, sub_dir->siblings se zanemari kad je jedan element
					free(new_dir);
					return 1;
				}
				
			sub_dir = sub_dir->siblings;
			}


		insert_after(new_dir, sub_dir);
		strftime(s, 1000, "%d/%m/%Y  %H:%M:%S", p);
		strcpy(new_dir->time, s);
		}
	}

	

	return 0;
}

int print_directories(tree_p current_dir) {
	tree_p temp = current_dir->children;
	
	if (temp == NULL && strcmp(current_dir->directory, "C:\\") == 0) {
		printf("Directory of %s\n\n", current_dir->directory);
		printf("***Empty***\n\n");
	}
	else if (temp != NULL && strcmp(current_dir->directory, "C:\\") == 0) {
		printf("Directory of %s\n\n", current_dir->directory);
		while (temp != NULL) {
			printf("%s		<DIR>		%s\n", temp->time, temp->directory);
			temp = temp->siblings;
		}
		printf("\n");

	}
	else{
		printf("Directory of %s\n\n", current_dir->directory);
		printf("%s		<DIR>		.\n", current_dir->time); 
		printf("%s		<DIR>		..\n", current_dir->time);
		while (temp != NULL) {
			printf("%s		<DIR>		%s\n", temp->time, temp->directory);
			temp = temp->siblings;
		}
		printf("\n");
	}
	return 0;
}

tree_p change_dir(tree_p current_dir, position head, tree_p root_address) {

	tree_p temp = current_dir->children;
	char wanted_dir[MAX_FILE_NAME] = { 0 };
	scanf("%s", &wanted_dir);


	while (temp != NULL && strcmp(temp->directory, wanted_dir) != 0)
		temp = temp->siblings;

	if (temp == NULL || strcmp(temp->directory, wanted_dir) != 0) { 
		printf("The system cannot find the path specified. Please check if the file %s exists.\n", wanted_dir);
		return current_dir;
	}
	else
	{
		push(current_dir, head);
		
		/*current_dir = temp;*/ //nije tilo prominit pokazivac u cijelom programu, pa je meni krivo radia
	}

	return temp;
}

tree_p delete(tree_p current) {

	if (current == NULL) {
		return NULL;
	}

	delete(current->siblings);
	delete(current->children);
	free(current);
	
	return NULL;
}