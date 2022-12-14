#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stog.h"
#include "stablo.h"
#include "menu.h"


int main()
{
	position head = (position)malloc(sizeof(stack));
	tree_p current_dir = make_root();	//is root here
	tree_p root_address = current_dir;
	create_root(head, root_address);

	if (NULL == head) {
		perror("Error while allocating memory!\n");
		return 1;
	}

	printf("HIPPO Windows [Version 1.69]\n(c) Hippopotamus Corporation. No rights whatsoever.\n\n");

	menu(head, current_dir, root_address);

	return 0;
}
