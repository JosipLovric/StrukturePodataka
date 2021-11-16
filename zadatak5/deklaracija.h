#define _CRT_SECURE_NO_WARNINGS

#ifndef DEKLARACIJA_H
#define DEKLARACIJA_H

struct _element;
typedef struct _element* pozicija;
typedef struct _element {

	double broj;
	pozicija next;

}element;

pozicija stvori_element(double br);
int umetni_nakon(pozicija poz, pozicija novi_el);
int izbrisi_nakon(pozicija poz);
int brisi_sve(pozicija head);
char* citanje_datoteke(char* naziv);
int ubacivanje_u_stog(char* buffer, double* rezultat);
int operacija(pozicija head, char operand, double* rezultat);
int provjera_operatora(char op);
int pop(pozicija head, double* rezultat);
int provjeri_rezultat(pozicija head, double* rezultat);


#endif 