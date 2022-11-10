#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>

#define M 50
#define MAX 1024

struct _pol;
typedef struct _pol* Position;
typedef struct _pol
{
    int koef;
    int exp;
    Position next;

} Pol;

int read_from_file(Position p1, Position p2);
int input_list(Position head, char* row);
int sort_list(Position head);
int print_pol(Position first);
int sum_pol(Position head1, Position head2, Position headsum);
int el_w_same_exp(Position first, Position head);
Position find_prev(Position head, int eksp);
int multiply_pol(Position head1, Position head2, Position headM);

int main()
{
    Pol head1 = { .koef = 0, .exp = 0, .next = NULL };
    Pol head2 = { .koef = 0, .exp = 0, .next = NULL };
    Pol headSum = { .koef = 0, .exp = 0, .next = NULL };
    Pol headMultiply = { .koef = 0, .exp = 0, .next = NULL };
    Position p1 = &head1;
    Position p2 = &head2;
    Position p_sum = &headSum;
    Position p_M = &headMultiply;
    int a = 0;

    a = read_from_file(p1, p2);

    if (a == EXIT_FAILURE)
    {
        return 0;
    }

    sort_list(p1);
    el_w_same_exp(p1->next, p1);
    sort_list(p2);
    el_w_same_exp(p2->next, p2);
    printf("\nFirst polynomial: \n");
    print_pol(p1->next);
    printf("\nSecond polynomial: \n");
    print_pol(p2->next);
    sum_pol(p1, p2, p_sum);
    sort_list(p_sum);
    el_w_same_exp(p_sum->next, p_sum);
    printf("\nPolynomials sum: \n");
    print_pol(p_sum->next);
    multiply_pol(p1, p2, p_M);
    sort_list(p_M);
    el_w_same_exp(p_M->next, p_M);
    printf("\nProduct of two polynomials: \n");
    print_pol(p_M->next);

    return EXIT_SUCCESS;
}

int read_from_file(Position p1, Position p2)
{
    FILE* fp = NULL;
    char dat[M] = { 0 };
    char row[MAX] = { 0 };
    int status = 0;

    printf("\nFile name: \n");
    scanf(" %s", dat);

    fp = fopen(dat, "r");

    if (fp == NULL)
    {
        printf("\nUnable to open file %s !\n", dat);
        return EXIT_FAILURE;
    }
    
    fgets(row, MAX, fp); //UPISIVANJE U PRVU LISTU
    status = input_list(p1, row);
    
    if (status != EXIT_SUCCESS)
    {
        printf("\nError --> first polynomial list input! \n\n");
        return -5;
    }
    
    fgets(row, MAX, fp); //UPISIVANJE U DRUGU LISTU
    status = input_list(p2, row);
    
    if (status != EXIT_SUCCESS)
    {
        printf("\nError --> second polynomial list input! \n\n");
        return -5;
    }
    
    fclose(fp);

    return EXIT_SUCCESS;
}

int input_list(Position head, char* row)
{
    int koef_temp = 0;
    int ekspo_temp = 0;
    int bytes = 0;
    int status = 2;
    char* H = row;
    Position new_el = NULL;
    
    while (strlen(H) > 0)
    {
        status = sscanf(H, " %d %d %n", &koef_temp, &ekspo_temp, &bytes);
        if (status != 2)
        {
            return EXIT_FAILURE;
        }
        
        new_el = (Position)malloc(sizeof(Pol));
        
        if (!new_el)
        {
            perror("\nMemory allocation failed!\n");
            return EXIT_FAILURE;
        }
        
        new_el->exp = ekspo_temp;
        new_el->koef = koef_temp;
        new_el->next = head->next;
        head->next = new_el;
        H += bytes;
    }

    return EXIT_SUCCESS;
}

int sort_list(Position head)
{
    Position i = NULL, j = NULL, prev_j = NULL, H = NULL, end = NULL;
    i = head;
    
    while (i->next != end)
    {
        prev_j = i;
        j = i->next;
        while (j->next != end)
        {
            if (j->exp > j->next->exp)
            {
                H = j->next;
                prev_j->next = H;
                j->next = H->next;
                H->next = j;
                j = H;
            }
            prev_j = j;
            j = j->next;
        }
        end = j;
    }

    return EXIT_SUCCESS;
}

int print_pol(Position first)
{
    Position H = NULL;
    H = first;
    int counter = 0;
    
    do
    {
        if (counter != 0)
        {
            if (H->koef >= 0)
            {
                printf("  +  ");
            }
            else
            {
                printf("  -  ");
            }
        }
        if (H->exp >= 0)
        {
            printf("%dx^%d", abs(H->koef), H->exp);
        }
        else
        {
            printf("%dx^(%d)", abs(H->koef), H->exp);
        }
        
        H = H->next;
        counter++;
    } while (H != NULL);
    printf("\n");

    return EXIT_SUCCESS;
}
int sum_pol(Position head1, Position head2, Position headsum)
{
    Position temp1 = NULL;
    Position temp2 = NULL;
    Position new_el = NULL;
    for (temp1 = head1->next; temp1 != NULL; temp1 = temp1->next)
    {
        new_el = (Position)malloc(sizeof(Pol));
        if (!new_el)
        {
            perror("\nMemory allocation failed!\n");
            return EXIT_FAILURE;
        }
        new_el->exp = temp1->exp;
        new_el->koef = temp1->koef;
        new_el->next = headsum->next;
        headsum->next = new_el;
    }
    for (temp2 = head2->next; temp2 != NULL; temp2 = temp2->next)
    {
        new_el = (Position)malloc(sizeof(Pol));
        if (!new_el)
        {
            perror("\nMemory allocation failed!\n");
            return EXIT_FAILURE;
        }
        new_el->exp = temp2->exp;
        new_el->koef = temp2->koef;
        new_el->next = headsum->next;
        headsum->next = new_el;
    }

    return EXIT_SUCCESS;
}

int el_w_same_exp(Position first, Position head)
{
    Position H = NULL;
    Position Prev = NULL;
    Position new_el = NULL;
    for (H = first; H->next != NULL; H = H->next)
    {
        if (H->exp == H->next->exp)
        {
            new_el = (Position)malloc(sizeof(Pol));
            if (!new_el)
            {
                perror("\nMemory allocation failed!\n");
                return EXIT_FAILURE;
            }
            Prev = find_prev(head, H->exp);
            new_el->exp = H->exp;
            new_el->koef = H->koef + H->next->koef;
            new_el->next = H->next->next;
            Prev->next = new_el;
        }
    }

    return EXIT_SUCCESS;
}

Position find_prev(Position head, int exp)
{
    Position prev = NULL, current = NULL;
    prev = head;
    current = prev->next;
    while (current != NULL && current->exp != exp)
    {
        prev = current;
        current = prev->next;
    }
    if (current == NULL)
    {
        return NULL;
    }

    return prev;
}

int multiply_pol(Position head1, Position head2, Position headM)
{
    Position temp1 = NULL;
    Position temp2 = NULL;
    Position new_el = NULL;
    for (temp1 = head1->next; temp1 != NULL; temp1 = temp1->next)
    {
        for (temp2 = head2->next; temp2 != NULL; temp2 = temp2->next)
        {
            new_el = (Position)malloc(sizeof(Pol));
            if (!new_el)
            {
                perror("\nMemory allocation failed!\n");
                return EXIT_FAILURE;
            }
            new_el->exp = temp1->exp + temp2->exp;
            new_el->koef = temp1->koef * temp2->koef;
            new_el->next = headM->next;
            headM->next = new_el;
        }
    }

    return EXIT_SUCCESS;
}
