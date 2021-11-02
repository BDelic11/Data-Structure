
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define MAX_L (128)
#define MAX_S (50)

struct lista;
typedef struct lista* position;

typedef struct lista {

	char Ime[MAX_S];
	char Prezime[MAX_S];
	int GodRod;
	position next;

} Osoba;



int DinamickiUnosNaPoc(position head);
void UnosPodataka(position p);
int Ispis(position First);
int DinamickiUnosNaKraj(position head);
position PronadiPosljednji(position head);
int Umetni(position p);
position PronadiOsobu(char* prezime, position p);
int ObrisiOsobu(position p, char* Brisi);
position PronadiPrethodni(position p, char* Brisi);
int DinUmetniNakon(char* prezime, position p);
int DinUmetniPrije(char* prezime, position p);
int SortirajPoPrezimenu(position head);
int IspisiUDat(position head, char* fileName);
int PrebaciIzDat(position head, char* fileName);


int main()
{

	char prez[MAX_S] = { 0 };
	char* prezime = prez;
	
	
	char fileName[MAX_S] = { 0 };

	char BrisiOsobu[MAX_S] = { 0 };
	char* Brisi = prez;

	position head = NULL;
	position TrazenaOsoba = NULL;

	head = (position)malloc(sizeof(Osoba));
	TrazenaOsoba = (position)malloc(sizeof(Osoba));
	head->next = NULL;



	DinamickiUnosNaPoc(head);
	Ispis(head->next);
	DinamickiUnosNaKraj(head);

	printf("Unesite prezime koje trazite:\n");      //trazenje po prezimenu
	scanf(" %s", prezime);

	TrazenaOsoba = PronadiOsobu(prezime, head->next);

	printf("\nIME: %s\nPREZIME: %s\nGodina Rodenja: %d\n\n", TrazenaOsoba->Ime, TrazenaOsoba->Prezime, TrazenaOsoba->GodRod);       //Ispis trazene osobe

	printf("Unesite prezime osobe koju zelite obrisati:\n");            //Brisanje osobe
	scanf(" %s", Brisi);

	ObrisiOsobu(head->next, Brisi);

	printf("\nProvjera brisanja...\n");                     //Provjera brisanja ponovnim trazenjem
	printf("Unesite prezime koje trazite:\n");
	scanf(" %s", prezime);

	TrazenaOsoba = PronadiOsobu(prezime, head->next);

	printf("Unesite prezime nakon kojega zelite umetnuti osobu:\n");    
	scanf(" %s", prezime);
    DinUmetniNakon(prezime, head->next);

    printf("Unesite prezime prije kojega zelite umetnuti osobu:\n");      
	scanf(" %s", prezime);
    DinUmetniPrije(prezime, head->next);

	SortirajPoPrezimenu(head);
	
	printf("Unesite ime datoteke koju zelite koristiti:\n");      
	scanf(" %s", fileName);
	IspisiUDat(head, fileName);
	PrebaciIzDat(head, fileName);


	return EXIT_SUCCESS;
}

int DinamickiUnosNaPoc(position head) {

	Umetni(head);

	return EXIT_SUCCESS;
}

void UnosPodataka(position p)
{
	printf("\nUnesite ime osobe:\n");
	scanf(" %s", p->Ime);

	printf("Unesite prezime osobe\n");
	scanf(" %s", p->Prezime);

	printf("Unesite datum rodenja osobe:\n");
	scanf("%d", &(p->GodRod));


}

int Ispis(position First)
{
	position temp = First;

	if (First == NULL)
	{
		printf("U listi nema elemenata!\n");
		return -1;
	}

	else {
		while (temp != NULL)
		{
			printf("IME: %s\nPREZIME: %s\nDatum Rodenja: %d\n\n", temp->Ime, temp->Prezime, temp->GodRod);
			temp = temp->next;
		}


	}


	return EXIT_SUCCESS;
}

int DinamickiUnosNaKraj(position head)
{
	position last = NULL;
	last = (position)malloc(sizeof(Osoba));
	if (!last)
	{
		printf("Greska u alokaciji memorije\n");
		return -1;
	}

	last = PronadiPosljednji(head);

	if (last == NULL)
	{
		printf("Greska u pronalazenju posljednjeg\n");
		return -1;
	}

	Umetni(last);


	return EXIT_SUCCESS;
}

position PronadiPosljednji(position p)
{
	while (p->next != NULL)
	{
		p = p->next;
		return p;
	}


	return EXIT_SUCCESS;
}

int Umetni(position p)
{
	position NovaOsoba = NULL;
	NovaOsoba = (position)malloc(sizeof(Osoba));

	if (!NovaOsoba)
	{
		perror("Greska u alokaciji memorije!\n");
		return -1;
	}

	UnosPodataka(NovaOsoba);

	NovaOsoba->next = p->next;
	p->next = NovaOsoba;

	if (NovaOsoba == 0)
	{
		perror("Greska u unosu podataka!\n");
		return -1;
	}

	return EXIT_SUCCESS;

}

position PronadiOsobu(char* prezime, position p)
{

	position temp = p;

	if (temp == NULL)
	{
		printf("Nije ucitana osoba.\n");
	}

	while (temp)
	{
		if (strcmp(temp->Prezime, prezime) == 0)
		{
			return temp;
		}

		temp = temp->next;
	}
	if (temp == NULL)
	{
		printf("Ne postoji osoba.\n");
	}

	return temp;

}


int ObrisiOsobu(position p, char* Brisi)
{
	position temp = p;


	position prev = NULL;
	position curr = NULL;

	prev = PronadiPrethodni(p, Brisi);

	if (prev == NULL)
		return -1;

	curr = prev->next;
	prev->next = prev->next->next;

	free(curr);

	return EXIT_SUCCESS;
}

position PronadiPrethodni(position p, char* Brisi)
{
	position prev = NULL, curr = NULL;

	prev = p;
	curr = prev->next;

	while (curr != NULL && strcmp(curr->Prezime, Brisi) != 0)
	{
		prev = curr;
		curr = prev->next;
	}

	if (curr == NULL)
	{
		printf("Nije pronaden nijedan element.\n");
		return NULL;
	}
	return prev;


}

int DinUmetniNakon(char* prezime, position p)
{
    position prev = NULL;

    prev = PronadiOsobu(prezime, p); 

    
    if (prev == NULL)
    {
        printf("Nije pronaden element u listi.");
       return -1;
    }

    Umetni (prev);
    
    return EXIT_SUCCESS;
}

int DinUmetniPrije(char* prezime, position p)
{
    position prev = NULL;

    prev = PronadiPrethodni(p ,prezime); 

    
    if (prev == NULL)
    {
        printf("Nije pronaden element u listi.");
       return -1;
    }

    Umetni (prev);

    return EXIT_SUCCESS;
}

int SortirajPoPrezimenu(position head)
{
	position i = NULL;
	position j = NULL;
	position prevJ = NULL;
	position temp = NULL;
	position end = NULL;

	if (!head)
		return -1;

	if (!head->next)
		return 1;

	i = head;

	while (i->next != end)
	{
		prevJ = i;
		j = i->next;

		while (j->next != end)
		{
			if (strcmp(j->Prezime, j->next->Prezime) > 0)
			{
				temp = j->next;
				prevJ->next = temp;
				j->next = temp->next;
				temp->next = j;

				j = temp;
			}
			
			prevJ = j;
			j = j->next;
		}
		end = j;
	}

	printf("Lista je sortirana!\n");

	return EXIT_SUCCESS;
}

int IspisiUDat(position head, char* fileName)
{
	FILE* file = NULL;
	position temp = NULL;

	file = fopen(fileName, "w");

	if (!file || !head)
		return -1;

	fprintf(file, "Ime, prezime i godina rodenja :\n");

	for (temp = head->next; temp; temp = temp->next)
		fprintf(file, "%s %s %d\n", temp->Ime, temp->Prezime, temp->GodRod);

	fclose(file);

	printf("Podaci su uspjesno upisani u datoteku!\n");

	return EXIT_SUCCESS;
}

int PrebaciIzDat(position head, char* fileName)
{
	FILE* file = NULL;
    position newPerson = NULL;
	char buffer[MAX_S] = { 0 };
	char Ime[MAX_S] = { 0 };
	char Prezime[MAX_S] = { 0 };
	int GodRod = 0;
	int i = 0;
	int numberOfValues;

	file = fopen(fileName, "r");

	if (!file || !head)
		return -1;

	while (!feof(file))
	{
		fgets(buffer, MAX_S, file);
		numberOfValues = sscanf(buffer, " %s %s%d", Ime, Prezime, &GodRod);

	
		strcpy(buffer, "");
	}

	fclose(file);

	printf("Podaci su uspjesno ispisani iz datoteke i spremljeni u memoriju!\n");

	return EXIT_SUCCESS;
}
