#define _CRT_SECURE_NO_WARNINGS

#include "deklaracija.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {
	char naziv[50];
	double rez = 0.0;
	char* buffer=NULL;
	double* rezultat = &rez;

	printf("\nUnesite datoteku za ucitat: ");
	scanf(" %s", naziv);
	buffer=citanje_datoteke(naziv);
	if (buffer == NULL) {
		return -1;
	}
	ubacivanje_u_stog(buffer, rezultat);



}
