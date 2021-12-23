#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include < string.h>
#define MIN (10)
#define MAX (90)


struct _Stablo;
typedef struct _Stablo* Position;
typedef struct _Stablo
{
	int element;
	Position Left;
	Position Right;

}Stablo;

Position UnesiElement(int element, Position position);
Position StvoriElement(int element);
int UpisiUDat(Position root, FILE* fp);
int Zamjeni(Position root);
int PronadiRandom();

int main()
{
	Position root = NULL;
	FILE* fp = fopen("Dat.txt", "w");
	if (!fp)
	{
		printf("File nije otvoren!\n");

	}
	int num = 0;



	printf("Zelite li raditi sa brojevima iz zadatka ili random brojevima?\nIzaberite:\n");
	printf("1 -->Brojevi iz zadatka\n");
	printf("2 --> Random brojevi\n");
	printf("0 --> Exit\n");


	scanf("%d", &num);

	do {
		switch (num)
		{
		case 1:
			root = UnesiElement(2, root);
			root = UnesiElement(5, root);
			root = UnesiElement(7, root);
			root = UnesiElement(8, root);
			root = UnesiElement(11, root);
			root = UnesiElement(1, root);
			root = UnesiElement(4, root);
			root = UnesiElement(2, root);
			root = UnesiElement(3, root);
			root = UnesiElement(7, root);

			fprintf(fp, "Brojevi iz zadatka:\n");
			UpisiUDat(root, fp);
			fprintf(fp, "\n");
			Zamjeni(root);
			UpisiUDat(root, fp);
			fprintf(fp, "\n");

			break;

		case 2:
			root = UnesiElement(PronadiRandom(), root);
			root = UnesiElement(PronadiRandom(), root);
			root = UnesiElement(PronadiRandom(), root);
			root = UnesiElement(PronadiRandom(), root);
			root = UnesiElement(PronadiRandom(), root);
			root = UnesiElement(PronadiRandom(), root);
			root = UnesiElement(PronadiRandom(), root);
			root = UnesiElement(PronadiRandom(), root);
			root = UnesiElement(PronadiRandom(), root);
			root = UnesiElement(PronadiRandom(), root);

			fprintf(fp, "\nRandom brojevi:\n");
			UpisiUDat(root, fp);
			fprintf(fp, "\n");
			Zamjeni(root);
			UpisiUDat(root, fp);
			fprintf(fp, "\n");
			break;

		default:
			printf("Krivi unos !\nPokusajte ponovo!\n");
		}
		scanf("%d", &num);
	} while (num);

	fclose(fp);
	return EXIT_SUCCESS;

}

Position UnesiElement(int element, Position position)
{
	Position temp = NULL;
	Position NewElement = NULL;
	temp = position;

	if (temp == NULL)
	{
		NewElement = StvoriElement(element);
		return NewElement;
	}
	else if (element < temp->element)
		temp->Right = UnesiElement(element, temp->Right);
	else if (element >= temp->element)
		temp->Left = UnesiElement(element, temp->Left);


	return temp;


}

Position StvoriElement(int element)
{
	Position NewElement = NULL;
	NewElement = (Position)malloc(sizeof(Stablo));

	if (!NewElement)
	{
		perror("Pogreska u alokaciji memorije!\n");
		return NULL;
	}

	NewElement->element = element;
	NewElement->Left = NULL;
	NewElement->Right = NULL;

	return NewElement;
}

int UpisiUDat(Position root, FILE* fp)
{
	Position current = NULL;
	current = root;

	if (current != NULL)
	{
		UpisiUDat(current->Left, fp);
		fprintf(fp, "%d ", current->element);
		UpisiUDat(current->Right, fp);


	}


	return EXIT_SUCCESS;
}


int Zamjeni(Position root)
{
	Position current = NULL;
	current = root;
	int sum = 0, value = 0;

	if (current->Left == NULL && current->Right == NULL)
	{
		sum = current->element;
		current->element = 0;
		return sum;

	}
	else if (current->Left != NULL && current->Right == NULL)
	{

		sum = Zamjeni(current->Left);
		value = current->element + sum;
		current->element = sum;
		return value;

	}
	else if (current->Left == NULL && current->Right != NULL)
	{

		sum = Zamjeni(current->Right);
		value = current->element + sum;
		current->element = sum;
		return value;

	}
	else
	{
		sum = Zamjeni(current->Left) + Zamjeni(current->Right);
		value = current->element + sum;
		current->element = sum;
		return value;
	}

	return EXIT_SUCCESS;

}

int PronadiRandom()
{
	int num = 0;
	num = MIN + (rand() % (MAX - MIN + 1));
	return num;
}