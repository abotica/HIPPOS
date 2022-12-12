#define _CRT_SECURE_NO_WARNINGS

#include "stog.h"
#include "stablo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int create_head() {
	position head = (position)malloc(sizeof(stack));

	if (NULL == head) {
		perror("Error while allocating memory!\n");
		return 1;
	}

	head->dir_address = NULL;
	head->next = NULL;

	return 0;
}

int push(tree_p added_dir_ad, position head) {
	position q = (position)malloc(sizeof(stack));
	if (NULL == q) {
		perror("Error while allocating memory!\n");
		return 1;
	}

	q->dir_address = added_dir_ad;	/*added_dir_ad is address of added element of tree*/

	q->next = head->next;
	head->next = q;

	return 0;
}

tree_p pop(position head) {

	tree_p address = NULL;
	position temp = head->next;

	if (temp != NULL)	address = temp->dir_address;

	head->next = temp->next;

	free(temp);

	return address;
}