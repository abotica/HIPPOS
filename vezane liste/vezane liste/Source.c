#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct osoba
{
	char ime[50];
	char prezime[50];
	int godina;

	struct osoba* next;

}osoba;

osoba* NapraviPrvi(osoba*);
osoba* DodajNaPocetak(osoba*);
void DodajNaKraj(osoba*);
void PronadiOsobu(osoba*, char[]);
void IzbrisiOsobu(osoba*, char[], char[], int);
void Ispis(osoba*);
void Odabir(osoba*);
int ProvjeraDaNe(char[]);


int main()
{
	osoba* head = NULL;
	

	head = NapraviPrvi(head);

	Odabir(head);

		
	


	return 0;
}

osoba* NapraviPrvi(osoba* head)
{
	osoba* temp = malloc(sizeof(osoba));
	temp->next = NULL;

	printf("Unesite ime >>");
	fgets(temp->ime, 50, stdin);
	printf("Unesite prezime >>");
	fgets(temp->prezime, 50, stdin);
	printf("Unesite godinu >>");
	scanf("%d", &temp->godina);

	head = temp;
	temp = NULL;

	return head;
}

osoba* DodajNaPocetak(osoba* head)
{
	osoba* temp = malloc(sizeof(osoba));
	temp->next = NULL;

	printf("Unesite ime >>");
	scanf("%s", &temp->ime);
	printf("Unesite prezime >>");
	scanf("%s", &temp->prezime);
	printf("Unesite godinu >>");
	scanf("%d", &temp->godina);

	temp->next = head;
	head = temp;
	temp = NULL;

	return head;
}

void DodajNaKraj(osoba* head)
{
	osoba* temp = malloc(sizeof(osoba));
	osoba* pom = head;

	temp->next = NULL;

	printf("Unesite ime >>");
	scanf("%s", &temp->ime);
	printf("Unesite prezime >>");
	scanf("%s", &temp->prezime);
	printf("Unesite godinu >>");
	scanf("%d", &temp->godina);

	while (pom->next != NULL)
	{
		pom = pom->next;
		
	}
	pom->next = temp;
	temp = NULL;

}

void PronadiOsobu(osoba* head, char prez[50])
{
	osoba* lokacija = head;
	
	
	for (int i = 0; lokacija != NULL; i++)
	{
		if (strcmp(lokacija->prezime, prez) == NULL)
		{
			printf("Pronadena je osoba \"%s %s %d\" na %d. mjestu na listi.\n", lokacija->ime, lokacija->prezime, lokacija->godina, i+1);
		}
		lokacija = lokacija->next;
	}

}

void IzbrisiOsobu(osoba* head, char i[50], char prez[50], int god)
{
	osoba* pom = head;
	osoba* pom2 = head;
	
	while (strcmp(pom->ime, i) || strcmp(pom->prezime, prez) || (pom->godina) != god)
	{
		pom2 = pom;
		pom = pom->next;
	}

	if (pom->next == NULL)
	{
		pom2->next = NULL;
	}
	else
	{
		pom2->next = pom->next;
	}

	free(pom);

}

void Ispis(osoba* head)
{
	osoba* pom = head;

	while (pom != NULL)
	{
		puts(pom->ime);
		puts(pom->prezime);
		printf("%d\n", pom->godina);
		printf("-------------\n");

		pom = pom->next;
	}

}



void Odabir(osoba* head)
{
	int do_while_uvjet = 0;

	do
	{
		char c, trazeno_prez[50] = { NULL }, izbrisi_ime[50] = { NULL }, izbrisi_prezime[50] = { NULL }, rijec[10] = { NULL };
		int izbrisi_god = 0;

		printf("\nOdaberite sto zelite nadalje raditi s Vasom listom:\n");
		printf("a)Ispisati listu\nb)Dodati osobu na pocetak liste\nc)Dodati osobu na kraj liste\nd)Pronaci osobu po prezimenu\ne)Izbrisati osobu\n");
		scanf(" %c", &c);

		switch (c)
		{
		case 'a':
			printf("Odabrali ste ispisati listu\n");
			printf("Vasa lista je:\n\n-------------\n");
			Ispis(head);
			break;

		case 'b':
			printf("Odabrali ste dodati osobu na pocetak liste\n");
			head = DodajNaPocetak(head);
			break;

		case 'c':
			printf("Odabrali ste dodati osobu na kraj liste\n");
			DodajNaKraj(head);
			break;

		case 'd':
			printf("Odabrali ste pronaci osobu po prezimenu\n");
			printf("Upisite prezime koje trazite >>");
			scanf("%s", trazeno_prez);
			PronadiOsobu(head, trazeno_prez);
			break;

		case 'e':
			printf("Odabrali ste izbrisati osobu!!!\n");
			printf("Unesite ime osobe koju zelite izbrisati >>");
			scanf("%s", izbrisi_ime);
			printf("Koje je prezime osobe \"%s\" koju zelite izbrisati ? >> ", izbrisi_ime);
			scanf("%s", izbrisi_prezime);
			printf("Unesite godinu osobe \"%s %s\" koju zelite izbrisati >>", izbrisi_ime, izbrisi_prezime);
			scanf("%d", &izbrisi_god);

			IzbrisiOsobu(head, izbrisi_ime, izbrisi_prezime, izbrisi_god);
			break;

		default:
			break;
		}

		fputs("Biste li htjeli obaviti jos neku od prethodno ponudenih operacija? >>", stdout);
		scanf("%s", rijec);

		do_while_uvjet = ProvjeraDaNe(rijec);

	} while (do_while_uvjet != 0);

	
}

int ProvjeraDaNe(char rijec[3])
{
	int uvjet = 0;

	
	do {

		if (strcmp(rijec, "da") == NULL || strcmp(rijec, "DA") == NULL)
		{
			uvjet = 1;
		}
		else if (strcmp(rijec, "d") == NULL || strcmp(rijec, "D") == NULL)
		{
			uvjet = 1;
		}
		else if (strcmp(rijec, "ne") == NULL || strcmp(rijec, "NE") == NULL)
		{
			uvjet = 0;
		}
		else if (strcmp(rijec, "n") == NULL || strcmp(rijec, "N") == NULL)
		{
			uvjet = 0;
		}
		else
		{
			uvjet = 2;
			printf("Niste upisali valjanu rijec, upisite ponovno >>");
			fgets(rijec, 10, stdin);
		}

	} while (uvjet == 2);
	

	return uvjet;
}