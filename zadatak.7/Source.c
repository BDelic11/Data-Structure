#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX (1024)

struct _Direktorij;
typedef struct _Direktorij* Position;

typedef struct _Direktorij {

	char Ime[MAX];
	Position sibling;
	Position child;

} Direktorij;

struct _Stack;
typedef struct _Stack* StackPosition;

typedef struct _Stack {

	Position direktorij;
	StackPosition next;

} Stack;


Position UmetniDirektorij(Position current, Position newElement);
Position StvoriDirektorij(char* Ime);
StackPosition StvoriStackElement(Position direktorij);
int PushStack(StackPosition head, StackPosition newStackElement);
Position PopStack(StackPosition head, Position current);
int IspisiDirektorij(Position current);
Position Move(Position current, char* ImeOdredista, StackPosition stack);
int Free(Position root);
int UpisKorisnika();

int main()
{
	Direktorij Root = { .Ime = "root", .sibling = NULL, .child = NULL };
	Position root = &Root;
	Position current = root;

	Stack Head = { .direktorij = NULL, .next = NULL };
	StackPosition head = &Head;

	int choice = 0;
	char ImeDirektorija[MAX] = { 0 };

	printf("Unesite vas izbor: \n");

	printf("1 - md (Stvori Direktorij) \n");
	printf("2 - cd dir (Pomakni u drugi direktorij) \n");
	printf("3 - cd .. (Pomakni u parent) \n");
	printf("4 - dir (Ispisi sto se nalazi u trenutnom direktoriju)\n");
	printf("5 - exit \n");

	choice = UpisKorisnika();

	while (choice != 5)
	{

		switch (choice)
		{
		case 1:
		{
			printf("Unesite ime novog Direktorija: ");
			scanf(" %s", ImeDirektorija);
			Position NoviDirektorij = StvoriDirektorij(ImeDirektorija);
			current->child = UmetniDirektorij(current->child, NoviDirektorij);
			break;
		}

		case 2:
		{
			printf("Unesite ime Direktorija koje ste odredili: ");
			scanf(" %s", ImeDirektorija);
			current = Move(current, ImeDirektorija, head);
			break;
		}
		case 3:
		{
			current = PopStack(head, current);
			break;
		}
		case 4:
		{
			printf("/%s: \n", current->Ime);
			IspisiDirektorij(current);
			break;
		}
		default:
		{
			if (choice != 5)
			{
				printf("Unijeli ste krivu naredbu. Molimo pokusajte ponovo.\n\n");
				break;
			}
		}
		}
		puts("\n");

		printf("1 - md (Stvori Direktorij) \n");
		printf("2 - cd dir (Pomakni u drugi direktorij) \n");
		printf("3 - cd .. (Pomakni u parent) \n");
		printf("4 - dir (Ispisi sto se nalazi u trenutnom direktoriju)\n");
		printf("5 - exit \n");

		choice = UpisKorisnika();

	}

	Free(root->child);

	return EXIT_SUCCESS;
}

Position UmetniDirektorij(Position current, Position NoviElement)
{
	if (!current)
		return NoviElement;

	if (strcmp(current->Ime, NoviElement->Ime) < 0)
		current->sibling = UmetniDirektorij(current->sibling, NoviElement);

	else if (strcmp(current->Ime, NoviElement->Ime) > 0)
	{
		NoviElement->sibling = current;
		return NoviElement;
	}
	return current;
}

Position StvoriDirektorij(char* Ime)
{
	Position NoviElement = NULL;
	NoviElement = (Position)malloc(sizeof(Direktorij));

	if (!NoviElement)
	{
		perror("Could not allocate memory!");
		return NULL;
	}

	strcpy(NoviElement->Ime, Ime);
	NoviElement->sibling = NULL;
	NoviElement->child = NULL;

	return NoviElement;
}

StackPosition StvoriStackElement(Position current)
{
	StackPosition NoviElement = NULL;
	NoviElement = (StackPosition)malloc(sizeof(Stack));

	if (!NoviElement)
	{
		perror("Could not allocate memory!");
		return NULL;
	}

	NoviElement->direktorij = current;
	NoviElement->next = NULL;

	return NoviElement;
}


int PushStack(StackPosition head, StackPosition NoviElement)
{
	NoviElement->next = head->next;
	head->next = NoviElement;

	return EXIT_SUCCESS;
}

Position PopStack(StackPosition head, Position current)
{
	StackPosition first = NULL;
	first = head->next;

	Position temp = NULL;

	if (!first)
	{
		printf("This directory does not have a parent");
		return current;
	}
	temp = first->direktorij;

	head->next = first->next;
	free(first);

	return temp;
}

int IspisiDirektorij(Position current)
{
	Position temp = current->child;

	while (temp)
	{
		printf(" -%s \n", temp->Ime);
		temp = temp->sibling;
	}

	return EXIT_SUCCESS;
}

Position Move(Position current, char* Ime, StackPosition stack)
{
	Position temp = current->child;
	while (temp && strcmp(temp->Ime, Ime))
		temp = temp->sibling;

	if (temp == NULL)
	{
		printf("There is no subdirectory with name: %s ", Ime);
		return current;
	}
	else
	{
		StackPosition newEl = StvoriStackElement(current);
		PushStack(stack, newEl);
		return temp;
	}
	return temp;
}

int UpisKorisnika()
{
	char Unos[MAX] = { 0 };
	int num = 0;
	int status = 0;
	do {

		scanf("%s", Unos);

		for (int i = 0; i < strlen(Unos); i++)
		{
			status = 0;

			if (!isdigit(Unos[i]))
			{
				status = 1;
				printf("Wrong input, please enter a number \n");
				break;
			}
		}

	} while (status == 1);

	num = atoi(Unos);

	return num;
}

int Free(Position current)
{
	if (current && current->sibling)
		Free(current->sibling);

	if (current && current->child)
		Free(current->child);

	free(current);

	return EXIT_SUCCESS;
}