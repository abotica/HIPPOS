#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_NAME 256
#define MAX_LINE_LENGHT 1024
#define FILE_ERROR -1
#define REROUTE 2


int OpenStudentFolder(char[]);	/*Opening student folder*/
int FileNameCheck(char[]);	/*Checking if file name is properly typed in*/

typedef struct 
{
	char name[30];
	char surename[30];
	int points;

}student;



int main()
{
	student* pt = NULL;
	char filename[MAX_FILE_NAME] = { 0 };
	char y_n_word[MAX_LINE_LENGHT] = { 0 };	/*A word typed in by user*/
	int condition, st_num, i, max_points=50; /*condition is integer returned based on yes/no word typed in by user*/  
								  /*st_num tells us if file was openned properly based on returned value of function OpenStudentFolder*/
	FILE* fp = NULL;

	

	type_fname: /*Typing file name again*/
	printf("Please type in file name to open it >>\t");
	gets(filename);
	word_again: /*Typing yes/no word again*/
	printf("\n\nYou've entered \'%s\'. Is that okay? >>\t", filename);
	gets(y_n_word);

	condition = FileNameCheck(y_n_word); /*Call function to return condition based on yes/no word typed*/
	
	if (condition == 1)
	{
		goto type_fname; 
	}
	else if (condition == REROUTE)
	{
		goto word_again;
	}

	
	st_num = OpenStudentFolder(filename);

	
	if (st_num == FILE_ERROR)	/*If functioned returned error code st_num will store it and program ends*/
	{
		printf("\n\nClosing program...");

	}
	else /*If st_num stored any integer value it will be treated as number of students*/
	{
		printf("\nThere are %d students in file \'%s\'.\n", st_num, filename);
		pt = (student*)calloc(st_num, sizeof(student));
		fp = fopen(filename, "r");


		for (i = 0; i < st_num; i++)
		{
			fscanf(fp, "%s %s %d",&(pt+i)->name, &(pt+i)->surename, &(pt+i)->points);
			printf("\n%s %s %d\n", (pt + i)->name, (pt + i)->surename, (pt + i)->points);
			
		}
		printf("\nResults in percentages (max points=50):\n");
		for (i = 0; i < st_num; i++)
		{
			
			printf("\n%s %s %d %.2f%%\n", (pt + i)->name, (pt + i)->surename, (pt + i)->points, (float)((pt + i)->points)/max_points*100);

		}


		fclose(fp);

		free(pt);
	}



	return 0;
}

int OpenStudentFolder(char filename[MAX_FILE_NAME])
{
	int snum = 0;	/*Student number*/
	FILE* fp = NULL;	
	char buffer[MAX_LINE_LENGHT] = { 0 };
	char temp[MAX_LINE_LENGHT] = { 0 };
	int i;

	fp = fopen(filename, "r");

	if (fp == NULL)	/*This is cheking if file is opened properly if not returns -1*/
	{
		printf("\nFile \'%s\' is not opened properly or doesn't exist!", filename);
		
		return FILE_ERROR;
	}
	else
	{
		printf("\n\nFile \'%s\' is opened successfully!\n", filename);

	}


	while (!feof(fp))	/*While not found end of file*/
	{
		fgets(buffer, MAX_LINE_LENGHT, fp);
		
		if (strcmp("\n", buffer) != 0)
		{
			snum++;
		}
		
	}

	

	fclose(fp);
	return snum;
}

int FileNameCheck(char word[4])
{

	if ((strcmp(word, "yes") == NULL) || (strcmp(word, "y") == NULL))
	{
		return 0;

	}
	else if ((strcmp(word, "YES") == NULL) || (strcmp(word, "Y") == NULL))
	{
		return 0;


	}
	else if ((strcmp(word, "no") == NULL) || (strcmp(word, "n") == NULL))
	{
		return 1;

	}
	else if ((strcmp(word, "NO") == NULL) || (strcmp(word, "N") == NULL))
	{
		return 1;

	}
	else
	{
		printf("Please type in yes/y or no/n (CAPS LOCK has no effect)!");
		
		return REROUTE;

	}
	
}


