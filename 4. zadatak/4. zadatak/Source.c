
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAX_SIZE (50)
#define MAX_L (1024)

struct _Polinom;

typedef struct _Polinom* Position;

typedef struct _Polinom
{
	int koef;
	int pot;
	Position next;

} Polinom;

char* UnesiImeDat(void);
Position NapraviPolinom(int coef, int exp);
int UmetniNakon(Position position, Position newPolynomial);
int UmetniSortirano(Position head, Position newPolynomial);
int Ispis(Position first);
int CitanjeRedka(Position head, char* buffer);
int CitanjeDokumenta(Position head1, Position head2, char* fileName);
int ObrisiNull(Position head);
int ZbrojiPolinome(Position head1, Position head2, Position headS);
int PomnoziPolinome(Position head1, Position head2, Position headP);



int main(int argc, char** argv)
{
	Polinom Head1 = { .next = NULL, .koef = 0, .pot = 0 };
	Polinom Head2 = { .next = NULL, .koef = 0, .pot = 0 };
	Polinom HeadS = { .next = NULL, .koef = 0, .pot = 0 };
	Polinom HeadP = { .next = NULL, .koef = 0, .pot = 0 };

	Position p1 = &Head1;
	Position p2 = &Head2;
	Position pS = &HeadS;
	Position pP = &HeadP;

	char* ImeDat = NULL;
	int odabir = 1;

	while (odabir != 0)
	{

		printf("Odaberite radnju :\n\n");
		printf("\t0- Izlaz iz programa\n");
		printf("\t1- Zbrajanje polinoma\n");
		printf("\t2- Mnozenje polinoma\n");
		puts("");
		printf("VAS ODABIR:\n\t ");
		scanf(" %d", &odabir);

		switch (odabir)
		{
		case 0:
			printf("\nIzasli ste iz programa!\n");
			break;

		case 1:
			ImeDat = UnesiImeDat();
			if (CitanjeDokumenta(p1, p2, ImeDat) != EXIT_SUCCESS) break;
			printf("\tPOLINOMI SU:\n\n");
			printf("Polinom 1:\n");
			Ispis(p1);
			printf("Polinom 2:\n");
			Ispis(p2);
			printf("SUMA POLINOMA:\n\n");
			ZbrojiPolinome(p1, p2, pS);
			Ispis(pS);

			break;

		case 2:
			ImeDat = UnesiImeDat();
			if (CitanjeDokumenta(p1, p2, ImeDat) != EXIT_SUCCESS) break;
			printf("\tPOLINOMI SU:\n\n");
			printf("Polinom 1:\n");
			Ispis(p1);
			printf("Polinom 2:\n");
			Ispis(p2);
			printf("PRODUKT POLINOMA:\n\n");
			PomnoziPolinome(p1, p2, pP);
			Ispis(pP);

			break;

		default:

			printf("Pogresno unesen broj..\n");
			break;
		}
	}

	return EXIT_SUCCESS;
}


char* UnesiImeDat(void)
{
	char* str = NULL;
	str = malloc(sizeof(char) * MAX_SIZE);
	printf("\nUNESITE NAZIV DATOTEKE:\n\t-> ");
	scanf(" %s", str);
	return str;
}

Position NapraviPolinom(int coef, int exp)
{
	Position NoviPolinom = NULL;

	NoviPolinom = (Position)malloc(sizeof(Polinom));

	if (!NoviPolinom)
	{

		printf("Ne moze se alocirati memorija!\n");

	}

	NoviPolinom->koef = coef;
	NoviPolinom->pot = exp;
	NoviPolinom->next = NULL;

	return NoviPolinom;
}

int UmetniNakon(Position position, Position newPolynomial)
{
	newPolynomial->next = position->next;
	position->next = newPolynomial;

	return EXIT_SUCCESS;
}

int UmetniSortirano(Position head, Position newPolynomial)
{
	Position current = head;
	Position added = newPolynomial;
	int result = 0;

	while (current->next != NULL && current->next->pot > added->pot)
		current = current->next;

	if (current->next != NULL && current->next->pot == added->pot)
	{
		current->next->koef += added->koef;
		result = current->koef;

		if (result == 0)
			ObrisiNull(current);
	}

	else
	{
		NapraviPolinom(added->koef, added->pot);
		UmetniNakon(current, added);
	}

	return EXIT_SUCCESS;
}

int Ispis(Position first)
{
	Position temp = first->next;

	while (temp)
	{
		printf("\t%dx(%d)\n", temp->koef, temp->pot);
		temp = temp->next;
	}

	puts("");
	return EXIT_SUCCESS;
}


int ObrisiNull(Position head)
{
	Position previous = head;
	Position temp = NULL;

	while (previous->next != NULL)
	{
		if (previous->next->koef == 0)
		{
			temp = previous->next;
			previous->next = temp->next;
			free(temp);
		}
		else
			previous = previous->next;
	}

	return EXIT_SUCCESS;
}

int CitanjeRedka(Position head, char* buffer)
{
	int coef = 0;
	int exp = 0;

	int CitajLiniju = 0;
	int n = 0;



	while (strlen(buffer) > 0)
	{

		CitajLiniju = sscanf(buffer, " %d %d %n", &coef, &exp, &n);

		if (CitajLiniju == 2 && coef != 0)
			UmetniSortirano(head, NapraviPolinom(coef, exp));

		buffer += n;
	}

	return EXIT_SUCCESS;
}

int CitanjeDokumenta(Position head1, Position head2, char* ImeDat)
{
	int coef = 0;
	int exp = 0;
	char buffer[MAX_L] = { 0 };

	FILE* fp = NULL;
	fp = fopen(ImeDat, "r");

	if (!fp)
	{
		printf("Pogreska pri ucitavanju datoteke. . .\n");
		return -1;
	}

	fgets(buffer, MAX_L, fp);
	CitanjeRedka(head1, buffer);
	ObrisiNull(head1);

	fgets(buffer, MAX_L, fp);
	CitanjeRedka(head2, buffer);
	ObrisiNull(head2);

	printf("\nPodatci uspjesno upisani iz datoteke %s!\n\n", ImeDat);

	fclose(fp);


	return EXIT_SUCCESS;
}


int ZbrojiPolinome(Position head1, Position head2, Position headS)
{
	Position p1 = head1->next;
	Position p2 = head2->next;
	Position pS = headS;
	Position temp = NULL;

	while (p1 != NULL && p2 != NULL)
	{
		if (p1->pot > p2->pot)
		{
			UmetniSortirano(pS, NapraviPolinom(p2->koef, p2->pot));
			p2 = p2->next;
		}

		else if (p1->pot == p2->pot)
		{
			UmetniSortirano(pS, NapraviPolinom(p1->koef + p2->koef, p1->pot));
			p1 = p1->next;
			p2 = p2->next;
		}

		else
		{
			UmetniSortirano(pS, NapraviPolinom(p1->koef, p1->pot));
			p1 = p1->next;
		}
	}

	if (p1 != NULL)
		temp = p1;
	else
		temp = p2;
	while (temp != NULL)
	{
		UmetniSortirano(pS, NapraviPolinom(temp->koef, temp->pot));
		temp = temp->next;
	}

	ObrisiNull(pS);

	return EXIT_SUCCESS;
}

int PomnoziPolinome(Position head1, Position head2, Position headP)
{
	Position p1 = head1->next;
	Position p2 = head2->next;
	Position pP = headP;
	Position start = head2;

	while (p1 != NULL)
	{
		p2 = start;
		while (p2 != NULL)
		{
			UmetniSortirano(pP, NapraviPolinom(p1->koef * p2->koef, p1->pot + p2->pot));
			p2 = p2->next;
		}
		p1 = p1->next;
	}

	ObrisiNull(pP);

	return EXIT_SUCCESS;
}

