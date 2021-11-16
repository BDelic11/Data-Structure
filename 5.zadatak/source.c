#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (50)
#define MAX_LENGTH (1024)

struct _Element;

typedef struct _Element* Position;

typedef struct _Element
{
	double number;
	Position next;

} Element;

char* UnesiImeDat(void);
Position StvoriElement(double number); 
int PushElement(Position head, double number); 
int IzbrisiNakon(Position position); 
int PopElement(double* value, Position head); 
int IzracunajPostfix(Position head, char operation); 
int ProcitajRedak(Position head, char* buffer); 
int CitajDat(Position head, char* fileName); 
int Ispisi(double op1, double op2, double result, char operation);
int PonovoUpisiImeDat(Position head); 

int main(int argc, char** argv)
{
	Element stack = { .next = NULL, .number = 0.0 };
	Position s1 = &stack;

	char* fileName = NULL;
	int odabir = 0;

	printf("\t\tPROGRAM ZA RACUNANJE POSTFIKSA IZ DATOTEKE:\n\n");

	fileName = UnesiImeDat();

	if (CitajDat(s1, fileName) == EXIT_FAILURE)
		PonovoUpisiImeDat(s1); 

	return EXIT_SUCCESS;
}

char* UnesiImeDat(void)
{
	char* str = NULL;
	str = malloc(sizeof(char) * MAX_SIZE);
	printf("\nUNESITE NAZIV DATOTEKE:\n\t> ");
	scanf(" %s", str);
	return str;
}

Position StvoriElement(double number)
{
	Position newElement = NULL;

	newElement = (Position)malloc(sizeof(Element));

	if (!newElement)
	{
		perror("Ne moze se alocirati memorija!\n");
		system("pause > nul");
		return -1;
	}

	newElement->number = number;
	newElement->next = NULL;

	return newElement;
}

int InsertAfter(Position position, Position newElement)
{
	newElement->next = position->next;
	position->next = newElement;

	return EXIT_SUCCESS;
}

int IzbrisiNakon(Position position)
{
	Position top = position->next;

	if (!top)
	{
		return EXIT_SUCCESS; 
	}

	position->next = top->next;
	free(top);

	return EXIT_SUCCESS;
}

int PushElement(Position head, double number)
{
	Position newElement = NULL;

	newElement = StvoriElement(number);

	if (!newElement)
	{
		perror("Ne moze se alocirati memorija!\n");
		system("pause > nul");
		return -1;
	}

	InsertAfter(head, newElement);

	return EXIT_SUCCESS;
}

int PopElement(double* value, Position head)
{
	Position top = head->next;

	if (!top)
	{
		perror("Postfiks nije valjan. . .\n");
		system("pause > nul");
		return EXIT_FAILURE;
	}

	*value = top->number; 

	IzbrisiNakon(head);

	return EXIT_SUCCESS;
}

int IzracunajPostfix(Position head, char operation)
{
	double result = 0.0;
	double top = 0.0;
	double top_prev = 0.0;

	if (PopElement(&top, head) != EXIT_SUCCESS)
	{

		return EXIT_FAILURE;
	}

	if (PopElement(&top_prev, head) != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	switch (operation)
	{
	case '+':
		result = top_prev + top;
		Ispisi(top_prev, top, result, operation);
		break;

	case '-':
		result = top_prev - top;
		Ispisi(top_prev, top, result, operation);
		break;

	case '*':
		result = top_prev * top;
		Ispisi(top_prev, top, result, operation);
		break;

	case '/':
		if (top == 0)
		{
			printf("Ne smije se dijeliti nulom. . . \n");
			break;
		}
		result = top_prev / top;
		Ispisi(top_prev, top, result, operation);
		break;

	default:
		
		printf("\nPOGRESKA! Ova verzija programa sadrzava samo osnovne operacije. . .\nPokusajte s nekom drugom datotekom.\n");
		system("pause > nul");
		PonovoUpisiImeDat(head);
		break;
	}

	PushElement(head, result);

	return EXIT_SUCCESS;
}

int ProcitajRedak(Position head, char* buffer)
{
	double value = 0.0; 
	char operation = '\0'; 
	char* currentBuffer = NULL;  
	int readLine = 0; 
	int byteNumber = 0; 
	int status = 0; 

	currentBuffer = buffer;

	while (strlen(currentBuffer) > 0)
	{
		readLine = sscanf(currentBuffer, " %lf %n", &value, &byteNumber);

		if (readLine == 1) 
		{
			status = PushElement(head, value);

			if (status != EXIT_SUCCESS) 
			{
				free(buffer);
				return -3;
			}
			currentBuffer += byteNumber; 
		}

		else
		{
			sscanf(currentBuffer, " %c %n", &operation, &byteNumber);

			status = IzracunajPostfix(head, operation);

			if (status != EXIT_SUCCESS)
			{
				free(buffer);
				return -3;
			}
			currentBuffer += byteNumber;
		}
	}
	return EXIT_SUCCESS;
}

int CitajDat(Position head, char* fileName)
{
	int fileLength = 0;
	char* buffer = '\0';

	FILE* fp = NULL;
	fp = fopen(fileName, "rb"); 

	if (!fp)
	{
	
		perror("Pogreska pri ucitavanju datoteke. . .\n");
		system("pause > nul");
		return EXIT_FAILURE;
	}

	fseek(fp, 0, SEEK_END); 
	fileLength = ftell(fp);

	buffer = (char*)calloc(fileLength + 1, sizeof(char)); 

	if (!buffer)
	{
		
		perror("Ne moze se alocirati memorija!\n");
		system("pause > nul");
		return -1;
	}

	rewind(fp); 

	printf("\nPodatci uspjesno upisani iz datoteke %s!\n\n", fileName);

	fread(buffer, sizeof(char), fileLength, fp); 
	printf("\nPOSTFIKS IZGLEDA OVAKO:\n\n\t %s\n", buffer);
	printf("\n~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
	printf("\nREDOSLIJED RACUNSKIH OPERACIJA:\n");

	fclose(fp);

	ProcitajRedak(head, buffer);

	free(buffer);

	return EXIT_SUCCESS;
}

int Ispisi(double op1, double op2, double result, char operation)
{
	
	printf("\n\t%.2lf", op1); printf(" %c ", operation); printf("%.2lf = %.2lf\n", op2, result);

	return EXIT_SUCCESS;
}

int DeallocateStack(Position head)
{
	Position current = head;
	Position temp = NULL;

	while (current->next != NULL)
	{
		temp = current->next;
		current->next = temp->next;
		free(temp);
	}
	return EXIT_SUCCESS;
}

int PonovoUpisiImeDat(Position head)
{
	char* fileName = NULL;
	int odabir = 1;

	while (odabir != 0)
	{
		system("cls"); 
		printf("Zelite li pokusati unijeti naziv datoteke jos jednom? [0 ili 1]:\n\n");
		printf("\t0 -NE\n");
		printf("\t1 -DA\n");
		puts("");
		printf("VAS ODABIR:\n\t> ");
		scanf(" %d", &odabir);

		switch (odabir)
		{
		default:
			
			printf("Pogresan unos. . .\n");
			break;

		case 0:
			
			break;

		case 1:
			fileName = UnesiImeDat();
			if (CitajDat(head, fileName) == EXIT_SUCCESS)
			{
				return EXIT_SUCCESS;
				break;
			}
		}
	}
	return EXIT_SUCCESS;
}