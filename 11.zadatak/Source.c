#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define MAX 256
#define HASH 11

struct _Stablo;
typedef struct _Stablo* TPosition;
typedef struct _Stablo
{
	char grad[MAX];
	int populacija;
	TPosition Left;
	TPosition Right;

}tree;

struct _lista;
typedef struct _lista* LPosition;
typedef struct _lista
{
	char drzava[MAX];
	TPosition StabloRoot;
	LPosition next;
}lista;

struct _table;
typedef struct _table* Hash;
typedef struct _table
{
	LPosition* HashList;

}table;


int ReadCountryFromFile(Hash H, char* FileName);
TPosition CitajGrad(TPosition root, char* CountryName);
int UnesiSort(LPosition Head, char* ImeDrzave);
TPosition CreateTreeElement(TPosition root, char* grad, int pop);
int PrintList(LPosition Head);
int PrintInOrder(TPosition root);
int Print(TPosition root, int num);
LPosition StvoriElemLista(LPosition position);
LPosition AlocirajElemLista();
LPosition PronadiDrzavu(Hash H, char* CountryName);
Hash Inicijalizacija();
int DodajHash(char* CountryName, Hash H);
int Copy(char* CountryName);


int main()
{
	LPosition  Head = NULL;
	Hash HashTab = NULL;
	char File[MAX] = "datoteka.txt", ImeDrzave[MAX] = { 0 };
	int broj = 0;

	HashTab = Inicijalizacija();
	Head = StvoriElemLista(Head);

	ReadCountryFromFile(HashTab, File);

	printf("Drzave: \n");
	PrintList(Head->next);

	printf("Izaberi drzavu: ");
	scanf(" %s", ImeDrzave);
	strcat(ImeDrzave, ".txt");
	Head = PronadiDrzavu(HashTab, ImeDrzave);
	if (!Head)
	{
		printf("Ne postoji takva drzava!");
		return EXIT_SUCCESS;
	}
	printf("\nUnesi populaciju: ");
	scanf("%d", &broj);
	Print(Head->StabloRoot, broj);

	return EXIT_SUCCESS;
}

Hash Inicijalizacija()
{
	Hash H = NULL;
	int i = 0;

	H = (Hash)malloc(sizeof(table));
	if (H == NULL)
	{
		printf("Error u inicijalizaciji!\n");
		return NULL;
	}

	H->HashList = (LPosition*)malloc(sizeof(LPosition) * HASH);
	if (H->HashList == NULL)
	{
		printf("Error u inicijalizaciji!\n");
		return NULL;
	}

	for (i = 0; i < HASH; i++)
		H->HashList[i] = AlocirajElemLista();

	return H;
}

int DodajHash(char* ImeDrzave, Hash H)
{
	int index = 0;
	index = Copy(ImeDrzave);

	UnesiSort(H->HashList[index], ImeDrzave);

	return EXIT_SUCCESS;
}

int Copy(char* ImeDrzave)
{
	int length = 0, leftover = 0, sum = 0, i = 0;
	length = strlen(ImeDrzave);

	for (i = 0; i < length || i < 5; i++)
		sum += ImeDrzave[i];

	leftover = sum % HASH;

	return leftover;
}

LPosition StvoriElemLista(LPosition position)
{
	position = (LPosition)malloc(sizeof(lista));
	if (position == NULL)
	{
		perror("Pogreska u alokaciji memorije!");
		return NULL;
	}
	strcpy(position->drzava, "");
	position->next = NULL;
	position->StabloRoot = NULL;

	return position;
}

LPosition AlocirajElemLista()
{
	LPosition NewEl = NULL;
	NewEl = (LPosition)malloc(sizeof(lista));
	if (NewEl == NULL)
	{
		perror("Pogreska u alokacijii!");
		return NULL;
	}
	strcpy(NewEl->drzava, "");
	NewEl->next = NULL;
	NewEl->StabloRoot = NULL;

	return NewEl;
}

int ReadCountryFromFile(Hash H, char* FileName)
{
	FILE* fp = NULL;
	char ImeDrzave[MAX] = { 0 };

	fp = fopen(FileName, "r");
	if (fp == NULL)
	{
		printf("Greska u otvaranju!\n");
		return -1;
	}

	while (!feof(fp))
	{
		fscanf(fp, "%s\n", ImeDrzave);
		DodajHash(ImeDrzave, H);
	}

	fclose(fp);
	return EXIT_SUCCESS;
}

int UnesiSort(LPosition Head, char* ImeDrzave)
{
	LPosition NoviElem = NULL;
	char pom[MAX] = { 0 };

	LPosition temp = NULL;
	temp = Head;

	NoviElem = (LPosition)malloc(sizeof(lista));
	if (NoviElem == NULL)
	{
		perror("Greska u alokaciji!");
		return -2;
	}

	strcpy(NoviElem->drzava, ImeDrzave);
	NoviElem->StabloRoot = NULL;
	NoviElem->StabloRoot = CitajGrad(NoviElem->StabloRoot, ImeDrzave);
	strcpy(pom, ImeDrzave);

	while (temp != NULL)
	{
		if (temp->next == NULL)
		{
			temp->next = NoviElem;
			NoviElem->next = NULL;
			break;
		}
		else if (strcmp(pom, temp->next->drzava) < 0)
		{
			NoviElem->next = temp->next;
			temp->next = NoviElem;
			break;
		}
		temp = temp->next;
	}
	return EXIT_SUCCESS;
}
TPosition CitajGrad(TPosition root, char* FileName)
{
	FILE* fp = NULL;
	char cty[MAX] = { 0 };
	int pop = 0;

	fp = fopen(FileName, "r");
	if (fp == NULL)
	{
		printf("Greska u otvaranju.");
		return NULL;
	}

	while (!feof(fp))
	{
		fscanf(fp, " %s %d\n", cty, &pop);
		root = CreateTreeElement(root, cty, pop);
	}
	fclose(fp);
	return root;
}
TPosition CreateTreeElement(TPosition root, char* CityName, int pop)
{
	TPosition current = NULL;
	current = root;

	if (current == NULL)
	{
		current = (TPosition)malloc(sizeof(tree));
		if (current == NULL)
		{
			printf("Greska pri alokaciji memorije");
			return NULL;
		}
		strcpy(current->grad, CityName);
		current->populacija = pop;
		current->Left = NULL;
		current->Right = NULL;
	}
	else if (pop == current->populacija)
	{
		if (strcmp(CityName, current->grad) < 0)
			current->Left = CreateTreeElement(current->Left, CityName, pop);
		else if (strcmp(CityName, current->grad) > 0)
			current->Right = CreateTreeElement(current->Right, CityName, pop);
	}
	else
	{
		if (pop < current->populacija)
			current->Left = CreateTreeElement(current->Left, CityName, pop);
		else if (pop > current->populacija)
			current->Right = CreateTreeElement(current->Right, CityName, pop);
	}
	return current;
}
int PrintList(LPosition Head)
{
	LPosition temp = NULL;
	temp = Head;

	while (temp != NULL)
	{
		printf("\n%s:\n", temp->drzava);
		PrintInOrder(temp->StabloRoot);
		temp = temp->next;
	}
	return EXIT_SUCCESS;
}
int PrintInOrder(TPosition root)
{
	TPosition current = NULL;
	current = root;
	if (current == NULL)
		return 0;

	PrintInOrder(current->Left);
	printf("%s -> %d\n", current->grad, current->populacija);
	PrintInOrder(current->Right);

	return EXIT_SUCCESS;
}
LPosition PronadiDrzavu(Hash H, char* CountryName)
{
	int index = 0;
	index = Copy(CountryName);
	LPosition temp = H->HashList[index];

	while (temp->next != NULL)
	{
		if (strcmp(CountryName, temp->next->drzava) == 0)
			return temp->next;
		else
			temp = temp->next;
	}
	return NULL;
}
int Print(TPosition root, int num)
{
	TPosition current = NULL;
	current = root;

	if (current == NULL)
		return 0;

	Print(current->Left, num);

	if (num < current->populacija)
		printf("%s %d\n", current->grad, current->populacija);

	Print(current->Right, num);

	return EXIT_SUCCESS;
}