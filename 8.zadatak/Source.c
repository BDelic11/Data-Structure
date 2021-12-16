#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

struct _Stablo;
typedef struct _Stablo* Position;
typedef struct _Stablo
{
	int number;
	Position left;
	Position right;
} Stablo;

void IspisMenija();
void UmetniBroj(int* number);
Position UmetniElement(Position root, int number);
Position StvoriElement(int number);
int InOrderIspis(Position root);
int PostOrderPrint(Position root);
int PreOrderIspis(Position root);
Position ObrisiElement(Position root, int number);
Position PronadiMinimum(Position root);
Position PronadiElement(Position root, int number);

int main()
{
	Position root = NULL, TrazeniElement = NULL;
	int choice = 0, Broj = 0;

	do
	{
		IspisMenija();

		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			UmetniBroj(&Broj);
			root = UmetniElement(root, Broj);
			break;

		case 2:
			printf("Inorder ispis:\n");
			InOrderIspis(root);
			break;

		case 3:
			printf("Preorder ispis:\n");
			PreOrderIspis(root);
			break;

		case 4:
			printf("Postorder ispis:\n");
			PostOrderPrint(root);
			break;


		case 6:
			UmetniBroj(&Broj);
			printf("Koji element zelite obrisati:");
			root = ObrisiElement(root, Broj);
			break;

		case 7:
			UmetniBroj(&Broj);
			TrazeniElement = PronadiElement(root, Broj);
			if (TrazeniElement)
				printf("Postoji broj na adresi %p\n", TrazeniElement);
			break;

		case 8:
			printf("Kraj programa.");
			break;

		default:
			printf("Pogresan unos.\n");
			break;
		}
	} while (choice != 8);

	return 0;
}

void IspisMenija()
{
	printf("Odaberi radnju:\n"
		"1 - unos novog elementa\n"
		"2 - ispis inorder\n"
		"3 - ispis preorder\n"
		"4 - ispis postorder\n"
		"5 - ispis level order\n"
		"6 - brisanje elmenta\n"
		"7 - pronalazenje elmenta\n");
}

void UmetniBroj(int* Broj)
{
	printf("Unesi broj koji zelis unijeti u binarno stablo: ");
	scanf("%d", Broj);
}

Position UmetniElement(Position root, int Broj)
{
	if (!root)
		return StvoriElement(Broj);
	else if (Broj < root->number)
		root->left = UmetniElement(root->left, Broj);
	else if (Broj > root->number)
		root->right = UmetniElement(root->right, Broj);

	return root;
}

Position StvoriElement(int Broj)
{
	Position newElement = (Position)malloc(sizeof(Stablo));

	if (!newElement)
	{
		perror("Tree element memory allocation");
		return NULL;
	}

	newElement->number = Broj;
	newElement->right = NULL;
	newElement->left = NULL;

	return newElement;
}

int InOrderIspis(Position root)
{
	if (root)
	{
		InOrderIspis(root->left);
		printf("%d\n", root->number);
		InOrderIspis(root->right);
	}

	return 0;
}

int PostOrderPrint(Position root)
{
	if (root)
	{
		PostOrderPrint(root->left);
		PostOrderPrint(root->right);
		printf("%d\n", root->number);
	}

	return 0;
}

int PreOrderIspis(Position root)
{
	if (root)
	{
		printf("%d\n", root->number);
		PreOrderIspis(root->left);
		PreOrderIspis(root->right);
	}

	return 0;
}

Position ObrisiElement(Position root, int number)
{
	Position tempElement = NULL;

	if (!root)
		return root;
	else if (number < root->number)
		root->left = ObrisiElement(root->left, number);
	else if (number > root->number)
		root->right = ObrisiElement(root->right, number);
	else
	{
		if (root->left && root->right)
		{
			tempElement = PronadiMinimum(root->right);
			root->number = tempElement->number;
			root->right = ObrisiElement(root->right, tempElement->number);
		}
		else
		{
			tempElement = root;
			if (!root->left)
				root = root->right;
			else if (!root->right)
				root = root->left;
			free(tempElement);
		}
	}
}

Position PronadiMinimum(Position root)
{
	while (root->left)
		root = root->left;
	return root;
}

Position PronadiElement(Position root, int number)
{
	if (!root)
		return root;
	else if (number < root->number)
		return PronadiElement(root->left, number);
	else if (number > root->number)
		return PronadiElement(root->right, number);
	return root;
}