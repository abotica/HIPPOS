#define _CRT_SECURE_NO_WARNINGS
#include "menu.h"

int menu(position head, tree_p current_dir, tree_p root_address) {
	int end = 1;
	char command[MAX_FILE_NAME] = { 0 };

	do {
		printf("%s>", current_dir->directory);
		scanf("%s", &command);

		
		if (strcmp(command, "md") == 0) {

			make_dir(current_dir);

		}
		else if (strcmp(command, "dir") == 0) {

			print_directories(current_dir);

		}
		else if (strcmp(command, "cd") == 0) {

			current_dir = change_dir(current_dir, head, root_address);

		}
		else if (strcmp(command, "cd..") == 0) {

			current_dir = pop(head, root_address);

		}
		else if (strcmp(command, "cd.") == 0)
		{
			

		}
		else if (strcmp(command, "exit") == 0) {
			end = 0;
		}
		else
		{
			printf("\'%s\' is not recognized as an internal or external command :).\n\n", command);

		}





	} while (end);








	return 0;
}