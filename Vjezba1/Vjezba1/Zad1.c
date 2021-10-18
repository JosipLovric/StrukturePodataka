#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (128)
#define MAX_LINE (1024)

typedef struct _student
{
	char ime[MAX_SIZE];
	char prezime[MAX_SIZE];
	int bod;

}Student;

int brRed(char* f);
Student* alokacija(int br, char* f);
int Ispis(Student* stud, int br);

int main()
{
	int br=0;
	Student* studenti = NULL;

	br = brRed("Popis.txt");
	studenti = alokacija(br,"Popis.txt");

	Ispis(studenti, br);

	return 0;
}

int brRed(char* f)
{
	int b=0;
	FILE* dat = NULL;
	char buffer[MAX_LINE] = { 0 };
	
	dat = fopen(f, "r");
	if (dat == NULL)
	{
		printf("Nije ucitana datoteka!!\n");
		return -1;
	}
	
	while (feof(dat) != 1)
	{
		fgets(buffer, MAX_LINE, dat);
		b++;
	}
	fclose(dat);

	return b;
}

Student* alokacija(int br, char* f)
{
	Student* pok = NULL;
	FILE* dat = NULL;
	int i = 0;

	pok = (Student*)malloc(br * sizeof(Student));
	if (pok == NULL)
	{
		printf("Greska!\n");
		return NULL;
	}

	dat = fopen(f, "r");
	if (dat == NULL)
	{
		printf("Nije ucitana datoteka!!\n");
		return NULL;
	}

	while (feof(dat) != 1)
	{
		fscanf(dat," %s %s %d",pok[i].ime,pok[i].prezime,&pok[i].bod);
		i++;
	}
	fclose(dat);

	return pok;
}

int Ispis(Student* stud, int br)
{
	int MAX = 0;
	int i = 0;
	
	for (i = 0; i < br; i++)
	{
		if (MAX < stud[i].bod)
			MAX = stud[i].bod;
	}
	for (i = 0; i < br; i++)
	{
		printf(" %s %s %d %.2f\n", stud[i].ime, stud[i].prezime, stud[i].bod,(((float)stud[i].bod / MAX) * 100));
	}


	return 0;
}
