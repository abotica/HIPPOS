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

osoba* DodajNaPocetak(osoba*);
int DodajNaKraj(osoba*);
int PronadiOsobu(osoba*, char[]);
int IzbrisiOsobu(osoba*, char[], char[], int);
int Ispis(osoba*);
int Odabir(osoba*);
int ProvjeraDaNe(char[]);
int DodajIza(osoba*, char[], char[], char[], int);
int DodajIspred(char[], char[], int god, char[], char[], int, osoba*);
int Sortiraj(osoba*);
int UpisUDatoteku(osoba*, char[]);
int UcitajIzDatoteke(osoba*, char datoteka[]);
osoba* Trazi_Iza(char[], osoba*);
osoba* Napravi_osobu(char[], char[], int);
osoba* Trazi_Prethodnika(osoba*, char[], char[], int);

int main()
{
	osoba* head = NULL;
	

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
int DodajNaKraj(osoba* head)
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
	
	return 0;
}
int PronadiOsobu(osoba* head, char prez[50])
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

	return 0;
}
int IzbrisiOsobu(osoba* head, char i[50], char prez[50], int god)
{
	osoba* pom = head;
	osoba* pom2 = head;
	int br = 0;

	while (strcmp(pom->ime, i) || strcmp(pom->prezime, prez) || (pom->godina) != god)
	{
		pom2 = pom;
		pom = pom->next;
		br++;
	}

	if (br == 0)
	{
		head = head->next;			/*zanemari trenutno*/
		free(pom);
		pom = NULL;

	}
	else if (pom->next == NULL)
	{
		pom2->next = NULL;
		free(pom);
	}
	else
	{
		pom2->next = pom->next;
		free(pom);
	}

	
	return 0;
}
int Ispis(osoba* head)
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
	return 0;
}
int Odabir(osoba* head)
{
	int do_while_uvjet = 0;
	osoba* oslobodi = NULL;

	do
	{
		char c=0, trazeno_prez[50] = { NULL }, izbrisi_ime[50] = { NULL }, izbrisi_prezime[50] = { NULL }, rijec[10] = { NULL }, datoteka[50] = {NULL}, dodano_prez[50] = { NULL }, dodano_ime[50] = { NULL }, prezime[50]= {NULL}, ime[50] = {NULL}, novo_ime[50] = {NULL}, novo_prezime[50] = {NULL};
		int izbrisi_god = 0, dodana_god = 0, nova_god = 0, god = 0;
		


		printf("\nOdaberite sto zelite nadalje raditi s Vasom listom:\n");
		printf("a)Ispisati listu\nb)Dodati osobu na pocetak liste\nc)Dodati osobu na kraj liste\nd)Pronaci osobu po prezimenu\ne)Izbrisati osobu\nf)Dodaj iza elementa\ng)Dodaj ispred elementa\nh)Sortiraj po prezimenu\ni)Upisati u datoteku\nj)Ucitaj iz datoteke\n");
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
		case 'f':
			printf("Odabrali ste dodati osobu iza elementa liste.");
			printf("Unesite prezime osoba iza koje zelite dodati novu osobu:");
			scanf("%s", prezime);
			printf("Unesite ime, prezime i godinu nove osobe:");
			scanf("%s %s %d", dodano_ime, dodano_prez, dodana_god);
			DodajIza(head, prezime, dodano_prez, dodano_ime, dodana_god);
			break;
		case 'g':
			printf("Odabrali ste dodati osobu ispred elementa liste.");
			DodajIspred(ime,prezime,god,novo_ime,novo_prezime,nova_god,head);
			break;
		case 'h':
			printf("Odabrali ste sortirati listu po preezimenu.");
			Sortiraj(head);
			break;
		case 'i':
			printf("Odabrali ste upisati listu u datoteku. Kako se zove datoteka?");
			scanf("%s", datoteka);
			UpisUDatoteku(head, datoteka);
			break;
		case 'j':
			printf("Odabrali ste ispisati listu iz datoteke. Unesite ime datoteke:");
			scanf("%s", datoteka);
			UcitajIzDatoteke(head, datoteka);
			break;

		default:
			break;
		}

		fputs("Biste li htjeli obaviti jos neku od prethodno ponudenih operacija? >>", stdout);
		scanf("%s", rijec);

		do_while_uvjet = ProvjeraDaNe(rijec);

	} while (do_while_uvjet != 0);


	oslobodi = head;

	while (oslobodi != NULL)
	{
		free(oslobodi);
		oslobodi = oslobodi->next;

	}

	return 0;
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
int DodajIza(osoba* head, char prezime[], char dodano_prez[], char dodano_ime[], int dodana_god)
{
	osoba* pom = NULL;
	head = Trazi_Iza(prezime, head);

	while ((head != NULL) && (strcmp(head->prezime, prezime)))
	{
		head = head->next;
	}

	if (head == NULL)
	{
		printf("\nGreska!");
		return 0;
	}

	else
	{

		head = Napravi_osobu(dodano_ime, dodano_prez, dodana_god);
		head->next = head->next;
		head->next = head;
	}


	return 0;
}
int DodajIspred(char ime[], char prezime[], int god, char novo_ime[], char novo_prezime[], int nova_god, osoba* head)
{
	osoba* pom = NULL;
	head = Trazi_Prethodnika(head, ime, prezime, god);

	while ((head != NULL) && (strcmp(head->next->prezime, prezime)))
	{
		head = head->next;
	}

	if (head == NULL)
	{
		printf("\nGreska!");
		return 0;
	}

	else
	{
		pom = Napravi_osobu(novo_ime, novo_prezime, nova_god);
		pom->next = head->next;
		head->next = pom;
	}
	

	return 0;
}
int Sortiraj(osoba* head)
{
	osoba* pom = NULL;
	osoba* preth_pom = NULL;
	osoba* temp = NULL;
	osoba* kraj = NULL;
    kraj = NULL;

  
    while (head->next != kraj)
    {
        preth_pom = head;
        pom = head->next;
        while (pom->next != kraj)
        {
            if (strncmp(pom->prezime, pom->next->prezime, 1) > 0)
            {
                temp = pom->next;
                preth_pom->next = temp;
                pom->next = temp->next;
                temp->next = pom;

                pom = temp;
            }
            else if (strncmp(pom->prezime, pom->next->prezime, 1) == 0)
            {
                if (strncmp(pom->prezime, pom->next->prezime, 2) > 0)
                {
                    temp = pom->next;
                    preth_pom->next = temp;
                    pom->next = temp->next;
                    temp->next = pom;

                    pom = temp;
                }
            }

            preth_pom = pom;
            pom = pom->next;
        }
        kraj = pom;
    }
    return 0;

}
int UpisUDatoteku(osoba* head, char datoteka[])
{
	FILE* fp = fopen(datoteka, "w");
	osoba* pom = head;

	if (fp == NULL)
	{
		printf("Greska pri otvaranju datoteke!!!");
						 
		return 1; 

	}

	while (pom != NULL)
	{
		fprintf(fp, "%s %s %d", pom->ime, pom->prezime, pom->godina);
		pom = pom->next;
	}

	


	fclose(fp);
	return 0;
}
int UcitajIzDatoteke(osoba* head, char datoteka[])
{
	FILE* fp = fopen(datoteka, "r");
	osoba* pom = head;
	char ime[50] = {NULL}, prezime[50] = {NULL};
	int god = 0;

	if (fp == NULL)
	{
		printf("Greska pri otvaranju datoteke!!!");

		return 1;

	}

	while (!feof(fp))
	{
		
		fscanf(fp, "%s %s %d", ime, prezime, &god);
		Napravi_osobu(ime, prezime, god);
		Sortiraj(head);
		pom = pom->next;
		
	}

	fclose(fp);
	return 0;
}
osoba* Trazi_Iza(char prezime, osoba* head)
{
	while ((head != NULL) && strcmp(prezime, head->prezime))
	{
		head = head->next;
	}

	if (head == NULL)
	{
		printf("\nNema trazene osobe.\n");
	}

	return head;
}
osoba* Napravi_osobu(char ime[], char prezime[], int god)
{
	osoba* nova_osoba = NULL;
	nova_osoba = malloc(sizeof(osoba));

	if (nova_osoba == NULL)
	{
		printf("Greska!");
		return 0;
	}

	else
	{
		strcpy(nova_osoba->ime, ime);
		strcpy(nova_osoba->prezime, prezime);
		nova_osoba->godina = god;
		nova_osoba->next = NULL;
	}

	return nova_osoba;

}
osoba* Trazi_Prethodnika(osoba* head, char ime[], char prezime[], int god)
{
	osoba* Prethodnik = NULL;
	Prethodnik = head;
	head = head->next;
	while ((head != NULL) && ((strcmp(ime, head->ime)) || strcmp(prezime, head->prezime) || (god != head->godina)))
	{
		Prethodnik = Prethodnik->next;
		head = head->next;
	}
	return Prethodnik;
}