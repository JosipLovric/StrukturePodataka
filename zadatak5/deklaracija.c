#define _CRT_SECURE_NO_WARNINGS

#include "deklaracija.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



pozicija stvori_element(double br) {

	pozicija adr = NULL;
	adr = (pozicija)malloc(sizeof(element));
	if(adr==NULL){
		printf("\nNeuspjelo alociranje memorije!!");
		return NULL;
	}
	adr->broj = br;
	adr->next = NULL;

	return adr;

}

int umetni_nakon(pozicija poz, pozicija novi_el) {

	novi_el->next = poz->next;
	poz->next = novi_el;

	return EXIT_SUCCESS;

}
int izbrisi_nakon(pozicija poz) {

	pozicija temp = NULL;

	temp = poz->next;

	if (!temp) {

		return EXIT_SUCCESS;

	}

	poz->next = temp->next;
	free(temp);

	return EXIT_SUCCESS;

}
int brisi_sve(pozicija head) {

	while (head->next != NULL) {
		izbrisi_nakon(head);
	}

	if (head->next == NULL) {

		return EXIT_SUCCESS;

	}
	else {
		printf("Greska pribrisanju!\n");
		return -1;
	}

}

	char* citanje_datoteke(char* naziv) {

		FILE* dat = NULL;
		int velicina_dat = 0;
		char* buffer = NULL;

		dat = fopen(naziv, "rb");
		if (dat == NULL) {
			printf("\nNeuspjelo otvaranje datoteke!");
			return NULL;
		}

		fseek(dat, 0, SEEK_END);
		
		velicina_dat = ftell(dat);

		buffer = (char*)calloc(velicina_dat + 1, sizeof(char));
		if (!buffer)
		{
			printf("Can't allocate memory!\n");
			return NULL;
		}

		rewind(dat);
		fread(buffer, sizeof(char), velicina_dat, dat);
		printf("|%s|\n", buffer);
		fclose(dat);

		return buffer;

	}
	int operacija(pozicija head, char operand, double* rezultat) {
		double pribrojnik1 = 0.0;
		double pribrojnik2 = 0.0;
		int status = 0;

		

		status = pop(head, rezultat);
		if (status != 0) {
			return EXIT_FAILURE;
		}
		pribrojnik1 = *rezultat;
		
		status = pop(head, rezultat);
		if (status != 0) {
			return EXIT_FAILURE;
		}
		pribrojnik2 = *rezultat;
		



		switch (operand) {
		case '+':
		{
			*rezultat = pribrojnik2 + pribrojnik1;
		
			
			return EXIT_SUCCESS;
		}
		case '-':
		{
			*rezultat = pribrojnik2 - pribrojnik1;
		
			return EXIT_SUCCESS;
		}
		case '*':
		{
			*rezultat = pribrojnik2 * pribrojnik1;
			
			return EXIT_SUCCESS;
		}
		case '/':
		{
			*rezultat = pribrojnik2 / pribrojnik1;
		
			return EXIT_SUCCESS;
		}
		default:
			printf("\nKrivi operator!!!!!");
			return EXIT_FAILURE;

		}

	}

	int provjera_operatora(char op) {
		
		switch (op) {

		case '+': {

			return 1;
		}
		case '-': {

			return 1;
		}
		case '*': {

			return 1;
		}
		case '/': {

			return 1;
		}
		default:
			return -1;

		}
	}

	int pop(pozicija head,double* rezultat) {
		
		pozicija temp = NULL;

		if (!head->next) {
			printf("\nPrazan stack**");
			return EXIT_FAILURE;
		}
		temp = head->next;

		*rezultat = temp->broj;

		izbrisi_nakon(head);


		return EXIT_SUCCESS;


	}
	int provjeri_rezultat(pozicija head,double* rezultat) {
		
		int status = EXIT_SUCCESS;
		
		status= pop(head, rezultat);

		if (status!= EXIT_SUCCESS) {
			printf("\nGreska");
			return status;
		}
		if (head->next != NULL) {
			printf("\nGreska.neispravna datoteka");
			return EXIT_FAILURE;
		}


		return EXIT_SUCCESS;


	}

	int ubacivanje_u_stog(char* buffer, double* rezultat) {

		element head_stack = { .broj = 0, .next = NULL };
		char* tr_buffer = buffer;
		int pomak = 0;
		int status = 0;
		char operator;
		double broj = 0.0;
		pozicija novi_el = NULL;


		while (strlen(tr_buffer) > 0) {

			status=sscanf(tr_buffer," %lf %n",&broj,&pomak);
			if (status != 1) {
				
				status = sscanf(tr_buffer, " %c %n", &operator, &pomak);
				status = provjera_operatora(operator);
				
					if (status != 1) {
						printf("\nNeispravna dototeka(krivi operator)= %c ",operator);
						brisi_sve(&head_stack);
						return -1;
					}

					else {
						
						status= operacija(&head_stack,operator,rezultat);
						
						if (status != EXIT_SUCCESS) {
							
							printf("\nNeispravna dototeka");
							return EXIT_FAILURE;
							
						}
						
					}
					broj = *rezultat;
			}

			novi_el = stvori_element(broj);
			if (novi_el == NULL) {
				return -2;
			}

			tr_buffer += pomak;
			printf("|%s| <-->", tr_buffer);

			
			umetni_nakon(&head_stack, novi_el);


		}
	
		status = provjeri_rezultat(&head_stack, rezultat);
		if (status == EXIT_SUCCESS) {
			printf("\n\nREZULTAT== %lf", *rezultat);
			return EXIT_SUCCESS;
		}
		else {
			return EXIT_FAILURE;

		}
		
	

	}



