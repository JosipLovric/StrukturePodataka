#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include<string.h>

 struct _osoba;
 typedef struct _osoba* pozicija;

 typedef struct _osoba {
	 char ime[50];
	 char prez[50];
	 int god;
	 pozicija next;

 }osoba;
 //------DIO A----------
 int noviEl_P(pozicija p);
 //------DIO B----------
 int ispisListe(pozicija p);
 //------DIO C----------
 int noviEl_K(pozicija p);
 //------DIO D----------
 pozicija traziPrez(pozicija p);
 //------DIO E----------
 int brisi(pozicija p);
 //---POMOCNA FUNKCIJA ZA D-------vraca adresu prethodnog elementa
 pozicija trazi_P(pozicija p);
 //---IZBORNIK----
 pozicija odabir(pozicija p);
 
 int main() {
	 osoba head;
	 head.next = NULL;
	 pozicija p;
	

	 while (odabir(&head) != NULL) {
		 odabir(&head);
	 }


	 return 0;

 }
 
 int noviEL_P(pozicija p) {
	 pozicija q;
	 
	 if (p == NULL) {
		 printf("\nGRESKA!!");
		 return 0;
	 }
	
	 q= (pozicija)malloc(sizeof(osoba));
	 
	 if (q == NULL) {
		 printf("Greska\n");
		 return -1;
	 }

	 q->next = p->next;
	 p->next = q;
	 
	 printf("Unesite ime:\n");
	 scanf(" %s", q->ime);
	 printf("Unesite prezime:\n");
	 scanf(" %s", q->prez);
	 printf("Unesite godinju rodenja:\n");
	 scanf(" %d", &(q->god));

	
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
		 
		 printf("\n\n%d\n ime:%s\n prez:%s\n god:%d",b+1, p->next->ime, p->next->prez, p->next->god);
		 p = p->next;
		 
		 b++;

	 }
	 
	 return 0;
 }
 
 int noviEl_K(pozicija p) {
	 
	 pozicija q = NULL;
	
	 if (p == NULL) {
		 printf("\nGRESKA!!");
		 return 0;
	  }
	
	 q = (pozicija)malloc(sizeof(osoba));
	
	 if (q == NULL) {
		 printf("Greska!\n");
		 return -1;
	 }
	 
	 while (p->next != NULL) {
		  
		 p = p->next;
		
	 }

	 p->next = q;
	 q->next = NULL;
	 
	 printf("Unesite ime:\n");
	 scanf(" %s", q->ime);
	 printf("Unesite prezime:\n");
	 scanf(" %s", q->prez);
	 printf("Unesite godinju rodenja:\n");
	 scanf(" %d", &(q->god));
	 
	 
	 return 0;
 }
 
 pozicija traziPrez(pozicija p) {
	
	 char prez[50] = { 0 };
	 
	 if (p == NULL) {
		 printf("\nGRESKA!!");
		 return NULL;
	 }
	 
	 printf("\nUnesi prezime:");
	 scanf(" %s", &prez);
	 
	 while (p->next != NULL && strcmp(prez,p->prez)!=0) {
		 p = p->next;
	
	 }
	 
	 if (!strcmp(prez, p->prez))
		 printf("\n-------ISPIS TARZI--------\n ime:%s\n prez:%s\n god:%d", p->ime, p->prez, p->god);
	 else
		 printf("\n-----NEMA TOG ELEMENTA NA LISTI-----");
	
	 return NULL;

 }

 pozicija trazi_P(pozicija p) {

	 char prez[50] = { 0 };
	 
	 if (p == NULL) {
		 printf("\nGRESKA!!");
		 return NULL;
	 }



	 printf("\nPREZIME ZA BRISANJE:");
	 scanf(" %s", &prez);

	 while (p->next->next != NULL && strcmp(prez, p->next->prez) != 0) {
		 p = p->next;

	 }
	 if (!strcmp(prez, p->next->prez))
		 return p;
	 else
		 return NULL;
 }

 int brisi(pozicija p) {
	 
	 pozicija temp = NULL;
	 
	 if (p == NULL) {
		 printf("\nGRESKA!!");
		 return 0;
	 }
	
	// printf("\nPREZIME ZA BRISANJE:");
	 temp = trazi_P(p);
	 
	 if (temp == NULL) {
		 printf("\n-----NEPOSTOJI OSOBA S TIM PREZIMENOM");
		 return 0;
	 
	 }
	 
	 p = temp->next;
	 temp->next = p->next;

	 free(p);
	 
	 

	 return 0;
 }
 pozicija odabir(pozicija p) {
	 int br = 0;
	 pozicija temp = NULL;
	 
	 if (p == NULL) {
		 printf("\n*******GRESKA********");
		 return NULL;
	 }
	
	 temp = p;
	 
	 printf("\n\n 1.------DODAJ ELEMENT NA POCETAK LISTE-------");
	 printf("\n 2.------DODAJ ELEMENT NA KRAJ LISTE----------");
	 printf("\n 3.------TRAZI ELEMENT U LISTI(PO PREZIMENU)--");
	 printf("\n 4.------BRISI ELEMENT U LISTI(PREZIME)-------");
	 printf("\n 5.-------------//ISPIS LISTE//---------------\n");
	 printf("\n 0.-------------**IZLAZ**---------------\n");
	 printf("******UNESI KOMANDU******");
	 
	 scanf("%d", &br);

	
	 switch (br) {
	 
	//IZLAZ IZ PROGRAMA

	 case 0: {
		
		 printf("\n..............BOK..............");
		
		 return NULL;
	 }
			//-----dodaj novi elemnt
	 case 1: {
		 
		 noviEL_P(temp);
		 
		 temp = p;
		 
		 return odabir(temp);
	 }
		   //DODAJ ELEMENT NA KRAJ LISTE
	 case 2: {
		 noviEl_K(temp);

		 temp = p;

		 return odabir(temp);
	 }

		   //TRAZI ELEMENT U LISTI(PO PREZIMENU)
	 case 3: {
		 traziPrez(temp->next);

		 temp = p;

		 return odabir(temp);
	 }
		// BRISI ELEMENT U LISTI(PREZIME)
	 case 4: {
		 brisi(temp);

		 temp = p;

		 return odabir(temp);
	 }
		   //ISPIS LISTE

	 case 5: {
		 ispisListe(temp);

		 temp = p;

		 return odabir(temp);
	 }
	 default: {

		 printf("\n\n******POGRESAN UNOS*********\n\n");
		 return odabir(temp);
	 }

		 
		


	 

	 }




 }

