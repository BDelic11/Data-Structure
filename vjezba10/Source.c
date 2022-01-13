#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define MAX (256)



struct _Stablo;
typedef struct _Stablo* Tposition;
typedef struct _Stablo
{
	char grad[MAX];
	int populacija;
	Tposition Left;
	Tposition Right;


}Tree;

struct _Lista;
typedef struct _Lista* Lposition;
typedef struct _Lista
{
	char Drzava[MAX];
	Tposition Stablo;
	Lposition next;

} lista;

int ReadCountryFromFile(Lposition Head, Tposition root, char* FileName);
Tposition CitajGrad(Tposition root, char* FileName);
Lposition UnesiSort(Lposition Head, char* CountryName);
Lposition StvoruElemLista(char* CountryName);
Lposition PronadiPrethodni(Lposition Head, Lposition element);
int UmetniPoslije(Lposition position, Lposition element);
int PrintList(Lposition head);
Tposition CreateTreeElement(char* CityName, int pop);
Tposition UmetniUStablo(Tposition root, char* CityName, int pop);
int PrintInOrder(Tposition root);
int SearchList(Lposition Head, Tposition root, char* choice);
int Pretrazi(Tposition root, int pop);

int main()
{
	lista List = { .Drzava = '\0', .next = NULL, .Stablo = NULL };
	Lposition Head = NULL;
	Head = &List;
	Tposition root = NULL;;

	ReadCountryFromFile(Head, root, "datoteka.txt");

	char choice[MAX];
	int pop;
	printf("\nEnter a country!\n");
	scanf("%s", choice);

	strcat(choice, ".txt");

	SearchList(Head, root, choice);

	return EXIT_SUCCESS;
}


int ReadCountryFromFile(Lposition Head, Tposition root, char* ImeFile)
{
	char buffer[MAX];
	FILE* fp = NULL;
	fp = fopen(ImeFile, "r");
	if (!fp)
	{
		printf("GRESKA U OTVARANJU!\n");
		return -1;
	}

	Lposition temp = NULL;

	printf("Drzave:");
	while (!feof(fp))
	{
		fscanf(fp, "%s", buffer);

		temp = UnesiSort(Head, buffer);
		root = CitajGrad(root, buffer);
		temp->Stablo = root;
		root = NULL;

	}

	PrintList(Head);




	fclose(fp);

	return EXIT_SUCCESS;

}

Tposition CitajGrad(Tposition root, char* FileName)
{
	char buffer[MAX];
	int pop;
	FILE* fp = NULL;
	fp = fopen(FileName, "r");
	if (!fp)
	{
		printf("Greska u otvaranju!\n");
		return NULL;
	}

	while (!feof(fp))
	{
		fscanf(fp, "%s %d", buffer, &pop);
		root = UmetniUStablo(root, buffer, pop);

	}

	fclose(fp);



	return root;

}


Lposition UnesiSort(Lposition Head, char* ImeDrzave)
{
	Lposition temp = NULL;
	temp = Head->next;
	Lposition NoviEl = NULL;
	NoviEl = StvoruElemLista(ImeDrzave);

	Lposition Prosli = NULL;
	if (!NoviEl)
		return NULL;

	if (!temp)
	{
		UmetniPoslije(Head, NoviEl);
		return Head->next;
	}
	else
	{
		while (temp && strcmp(ImeDrzave, temp->Drzava))
			temp = temp->next;

		Prosli = PronadiPrethodni(Head, temp);
		UmetniPoslije(Prosli, NoviEl);
	}

	return Prosli->next;
}

Lposition StvoruElemLista(char* ImeDrzave)
{
	Lposition NoviEl = NULL;
	NoviEl = (Lposition)malloc(sizeof(lista));
	if (!NoviEl)
	{
		perror("Can't allocate memory!\n");
		return NULL;
	}

	strcpy(NoviEl->Drzava, ImeDrzave);
	NoviEl->next = NULL;
	NoviEl->Stablo = NULL;

	return NoviEl;

}

Lposition PronadiPrethodni(Lposition Head, Lposition element)
{
	Lposition temp = Head;

	while (temp->next != element)
		temp = temp->next;

	return temp;
}

int UmetniPoslije(Lposition position, Lposition element)
{
	element->next = position->next;
	position->next = element;

	return EXIT_SUCCESS;
}

int PrintList(Lposition head)
{
	Lposition temp = NULL;
	temp = head->next;

	while (temp->next)
	{
		printf("\n%s\n", temp->Drzava);
		PrintInOrder(temp->Stablo);
		temp = temp->next;
	}




	return EXIT_SUCCESS;
}

Tposition CreateTreeElement(char* ImeGrad, int pop)
{
	Tposition NoviElem = NULL;
	NoviElem = (Tposition)malloc(sizeof(Tree));
	if (!NoviElem)
	{
		perror("Greskka u alokaciji memorije!\n");
		return NULL;
	}

	strcpy(NoviElem->grad, ImeGrad);
	NoviElem->populacija = pop;
	NoviElem->Left = NULL;
	NoviElem->Right = NULL;

	return NoviElem;

}

Tposition UmetniUStablo(Tposition root, char* ImeGrad, int pop)
{
	Tposition current = NULL;
	current = root;

	Tposition NoviElem = NULL;


	if (current == NULL)
	{
		NoviElem = CreateTreeElement(ImeGrad, pop);
		return NoviElem;
	}
	else if (pop < current->populacija)
		current->Left = UmetniUStablo(current->Left, ImeGrad, pop);
	else if (pop > current->populacija)
		current->Right = UmetniUStablo(current->Right, ImeGrad, pop);
	else if (pop == current->populacija && strcmp(current->grad, ImeGrad) < 0)
		current->Right = UmetniUStablo(current->Right, ImeGrad, pop);
	else if (pop == current->populacija && strcmp(current->grad, ImeGrad) > 0)
		current->Left = UmetniUStablo(current->Left, ImeGrad, pop);
	else
		free(NoviElem);

	return current;
}

int PrintInOrder(Tposition root)
{
	Tposition current = root;
	current = root;

	if (current != NULL)
	{
		PrintInOrder(current->Left);
		printf("%d -> %s \n", current->populacija, current->grad);
		PrintInOrder(current->Right);
	}


	return EXIT_SUCCESS;
}


int SearchList(Lposition Head, Tposition root, char* choice)
{
	Lposition temp = NULL;
	temp = Head->next;
	int pop;

	while (temp->next)
	{

		if (strcmp(temp->Drzava, choice) == 0)
		{
			printf("Enter a number of population: ");
			scanf("%d", &pop);
			Pretrazi(temp->Stablo, pop);
			return EXIT_SUCCESS;
		}


		temp = temp->next;

	}

	printf("Ne postoji ta drzava u datoteci!");

}

int Pretrazi(Tposition root, int pop)
{
	Tposition current = NULL;
	current = root;
	int br = 0;

	if (current != NULL)
	{
		if (current->populacija > pop)
		{
			Pretrazi(current->Left, pop);
			printf("%d -> %s \n", current->populacija, current->grad);
			Pretrazi(current->Right, pop);
		}
		else
		{
			Pretrazi(current->Right, pop);

		}
	}



	return EXIT_SUCCESS;


}