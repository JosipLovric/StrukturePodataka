#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _person;
typedef struct _person* pozicija;

typedef struct _person {
	char ime[50];
	char prezime[50];
	int god;
	pozicija next;
}person;

int dodaj_el(pozicija p);
int dodaj_el_iza(pozicija p);			//dio_A dodaje element iza odredenog elementa(odabir po prezimenu)
int ispisListe(pozicija p);
int dodaj_el_ispred(pozicija p);		//dio_B dodaje element iza odredenog elementa(odabir po prezimenu)
int sortiraj(pozicija p);				//dio_C sortiranje
int upis_dat(pozicija p,char* naziv);	//upis u datoteku
int ispis_dat(pozicija p, char* naziv); //ispis iz datoteke


int main() {
	person head;
	head.next = NULL;

	person head_2;
	head_2.next = NULL;
	
	
	printf("dodaje element na pocetak liste:\n\n");
	dodaj_el(&head);
	
	printf("dodaje element na ispred odredenog elementa:\n\n");
	dodaj_el_ispred(&head);
	
	printf("dodaje element na iza odredenog elementa:\n\n");
	dodaj_el_iza(head.next);
	
	printf("sortiranje liste:\n");
	sortiraj(&head);
	
	printf("upis u datoteku:\n");
	upis_dat(&head, "upis.txt");
	printf("******************ISPIS SORTIRANE LISTE*****************\n\n\n");
	ispisListe(&head);
	
	printf("\nispis iz datoteke:\n");
	ispis_dat(&head_2, "ispis.txt");
		
	
	
	printf("Ispis liste unesene preko datoteke:\n\n");
	ispisListe(&head_2);
	
	
	return 0;
}

int dodaj_el(pozicija p) {
	
	if (!p) {
		printf("***Greska!!\n");
		return -1;
	}
	
	pozicija q = NULL;
	q = (pozicija)malloc(sizeof(person));

	printf("\nUnesite ime:\n");
	scanf(" %s", q->ime);
	printf("Unesite prezime:\n");
	scanf(" %s", q->prezime);
	printf("Unesite godinju rodenja:\n");
	scanf(" %d", &(q->god));
	
	q->next = p->next;
	p->next = q;


	return 0;
}

int dodaj_el_iza(pozicija p) {
	
	if (!p) {
		printf("***Greska!!\n");
		return -1;
	}
	char prez[50];


	printf("\nUpisi prezime za dodati:");
	scanf("%s", prez);

	while (p->next != NULL && strcmp(p->prezime, prez)) {
		p = p->next;
	}
	if (strcmp(p->prezime, prez)) {
		printf("\nNepostoji taj element na listi");
		return 0;
	}
	dodaj_el(p);

	return 0;
}
int ispisListe(pozicija p) {

	int b = 0;

	if (p == NULL) {
		printf("\nGRESKA!!");
		return 0;
	}

	if (p->next == NULL) {
		printf("\n*******LISTA JE PRAZNA*******");
		return 0;
	}

	while (p->next != NULL) {

		printf("\n\n%d\n ime:%s\n prez:%s\n god:%d", b + 1, p->next->ime, p->next->prezime, p->next->god);
		p = p->next;

		b++;

	}

	return 0;
}

int dodaj_el_ispred(pozicija p) {

	if (!p) {
		printf("***Greska!!\n");
		return -1;
	}
	char prez[50];


	printf("\nUpisi prezime za dodati:");
	scanf("%s", prez);

	while (p->next != NULL && strcmp(p->next->prezime, prez)) {
		p = p->next;
	}
	if (p->next) {
		dodaj_el(p);
		return 0;
	}
	else {
	printf("\nNepostoji taj element na listi");
	return 0;
	}
	
	
}
int sortiraj(pozicija p) {

	if (!p) {
		printf("***Greska!!\n");
		return -1;
	}
	pozicija temp = NULL;
	pozicija i = NULL;
	pozicija j = NULL;
	pozicija end = NULL;
	
	
	while(p->next !=end){
		i = p;
		j = p->next;

		while (j->next != end) {
			
			
			
			if ((strcmp(j->prezime, j->next->prezime)) > 0) 
			{
				
				temp = j->next;
				i->next = temp;
				j->next = temp->next;
				temp->next = j;
				j = temp;
				
				
			}
			i = j;
			j = j->next;
			
			
			
		}
		end = j;
		
	}

	return 0;
}

int upis_dat(pozicija p, char* naziv) {
	
	if (!p) {
		printf("***Greska!!\n");
		return -1;
	}
	
	
	FILE* fp;
	fp = NULL;
	fp = fopen(naziv, "w");
	
	
	if (!fp) {
		printf("***Greska!!\n");
		return -1;
	}
	while (p->next != NULL) {
		p = p->next;
		fprintf(fp,"\nIme: %s Prezime: %s Godina rodenja: %d", p->ime, p->prezime, p->god);
		
	}
	fclose(fp);

	return 0;
}
int ispis_dat(pozicija p, char* naziv) {
	
	if (!p) {
		printf("***Greska!!\n");
		return -1;
	}
	pozicija q;
	char buffer[1024];

	FILE* fp;
	fp = NULL;
	fp = fopen(naziv, "r");
	
	while (!feof(fp)) {
		q = NULL;
		q = (pozicija)malloc(sizeof(person));
		fscanf(fp, " %s %s %d\n", q->ime, q->prezime,&(q->god));
		q->next = p->next;
		p->next = q;
		
	}
	fclose(fp);
	
	
	return 0;
}

