#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

#define MAXBOD (100)
#define MAX_S (128)
#define MAX_L (1024)

typedef struct {

	char ime[MAX_S];
	char prezime[MAX_S];
	double bodovi;

} student;

void ispis(student* stud, int br);
double MaxBrojBodova(student* stud, int br);
int CitanjeBrojaStud(char* ImeDat);
student* DinAlokMem(char* ImeDat, int br);

int main()
{
	char Dat[MAX_S];
	int br = 0;
	char* ImeDat = NULL;
	student* stud = NULL;

	printf("Unesite ime datoteke koju zelite koristiti:\n");
	scanf("%s", Dat);

	ImeDat = Dat;

	br = CitanjeBrojaStud(ImeDat);

	if (br <= 0)
	{
		printf("U datoteci nema podataka.\n");
		return -1;
	};

	stud = DinAlokMem(ImeDat, br);

	ispis(stud, br);

	return 0;
}


int CitanjeBrojaStud(char* ImeDat)
{
	int brojac = 0;
	FILE* fp = NULL;
	char buffer[MAX_L] = { 0 };


	fp = fopen(ImeDat, "r");

	if (!fp)
	{
		printf("Greska u otvaranju datoteke!\n");

		return -1;
	}

	while (!feof(fp))
	{
		fgets(buffer, MAX_L, fp);
		brojac++;
	}
	fclose(fp);

	return brojac;
}

student* DinAlokMem(char* ImeDat, int br)
{
	int brojac = 0;
	FILE* fp = NULL;
	student* stud = NULL;

	fp = fopen(ImeDat, "r");

	stud = (student*)malloc(br * sizeof(student));


	if (!fp)
	{
		printf("Greska u alokaciji memorije!\n");

		return NULL;

	}
	while (!feof(fp))
	{
		fscanf(fp, "%s %s %lf", stud[brojac].ime, stud[brojac].prezime, &stud[brojac].bodovi);
		brojac++;
	}
	fclose(fp);


	return stud;
}

double MaxBrojBodova(student* stud, int br)
{
	int i = 0;
	double MaxBod = 0;

	MaxBod = stud[0].bodovi;

	for (i = 0; i < br; i++)
		if (stud[i].bodovi > MaxBod)
			MaxBod = stud[i].bodovi;

	return MaxBod;

}

void ispis(student* stud, int br)
{
	double MaxBod = 0;

	MaxBod = MaxBrojBodova(stud, br);



	for (int i = 0; i < br; i++)
	{
		float relbod = stud[i].bodovi / MaxBod * 100;
		printf("ime: %s		prezime: %s		aps bodovi: %lf		relat bodovi: %lf\n", stud[i].ime, stud[i].prezime, stud[i].bodovi / MAXBOD * 100, relbod);
		relbod = 0;
	}

}



