#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAX_NAME 1024
#define MAX_SIZE 100

struct stack;
typedef struct stack* position;

typedef struct stack
{

    float number;
    position next;

}stack;

int Print(position p)
{
    position q = p->next;

    while (q != NULL)
    {
        printf("|%f|\n", q->number); //to look like stack
        printf("----------\n");
        q = q->next;
    }
    printf("\n");

    return EXIT_SUCCESS;
}

int Delete(position p)
{

    position q = NULL;
    q = p->next;
    p->next = q->next;
    free(q);

    return EXIT_SUCCESS;
}

int Operator(char z, position p, int* count)
{
    float result = 0;
    position q = p->next;

    switch (z)
    {
    case '+':
        if ((*count) >= 2)
        {
            result = q->next->number + p->next->number;
            Delete(p);
            p->next->number = result;
            (*count)--;
            Print(p);
        }

        else
            printf("\nYou need atleast 2 elements to sum them!\n");

        break;

    case '*':
        if ((*count) >= 2)
        {
            result = q->next->number * p->next->number;
            Delete(p);
            p->next->number = result;
            (*count)--;
            Print(p);
        }

        else
            printf("\nYou need atleast 2 elements to multiply them!\n");

        break;

    case '-':
        if ((*count) >= 2)
        {
            result = q->next->number - p->next->number;
            Delete(p);
            p->next->number = result;
            (*count)--;
            Print(p);
        }

        else
            printf("\nYou need atleast 2 elements to substract them!\n");

        break;

    case '/':
        if ((*count) >= 2)
        {
            result = q->next->number / p->next->number;
            Delete(p);
            p->next->number = result;
            (*count)--;
            Print(p);
        }

        else
            printf("\nYou need atleast 2 elements to divide them!\n");

        break;

    default:
        printf("\nThat operation does not exist!\n");

    }

    return EXIT_SUCCESS;

}



int Input(position p, char* z)
{
    position q = NULL;
    int gaps = 0, count = 0;
    float f_number = 0; //floaing point number
    char character = 0;
   
    while (strlen(z) > 0) //while not at the end
    {   
         if (sscanf(z, "%f %n", &f_number, &gaps) == 1)  //%n will read white-space
         {
            q = (position)malloc(sizeof(stack));

            q->number = f_number;

            q->next = p->next;
            p->next = q;

            count++; //counts elements in stack
            Print(p);
        }
        else
        {
            sscanf(z, "%c %n", &character, &gaps);
            Operator(character, p, &count);
        }
        z += 2;
    }

    if (count != 1)
    {
        printf("\nNije zadovoljen uvjet da ostane jedan element u stogu.\n");
    }

    return EXIT_SUCCESS;
}



int main()
{
    stack head = { .number = 0, .next = NULL };
    position p = &head;
    FILE* fp = NULL;
    char filename[MAX_NAME] = { 0 };
    char buffer[MAX_SIZE] = { 0 };  //saves line of text from file
    char* p_buffer = NULL; 

    printf("Enter the file name: ");

    scanf("%s", filename);
    printf("\n");

    fp = fopen(filename, "r");
   

    if (fp == NULL)
    {
        printf("\nError!\n");
        return EXIT_FAILURE;
    }

    fgets(buffer, MAX_SIZE, fp); //takes the string from file using file pointer
    p_buffer = buffer;
    Input(p, p_buffer);

    return 0;
}
