#define _CRT_SECURE_NO_WARNINGS

#include "deklaracija.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

poz napravi_dir(const char* name) {
	
	poz temp = NULL;
	
	temp = (poz)malloc(sizeof(dir));
	
	if (temp == NULL) {
		printf("Greska pri alokaciji");
		return NULL;
	}

	strcpy(temp->ime,name);
	temp->brat = NULL;
	temp->dite = NULL;

	return temp;


}

//md naredba 

poz umetni(poz tren, poz q) {
	
	if (tren == NULL) {
		return q;
	}
	if (strcmp(tren->ime, q->ime) > 0)
	
	{
		q->brat = tren;
		return q;
	}
	else if (strcmp(tren->ime, q->ime) < 0) 
	
	{
		tren->brat = umetni(tren->brat, q);
	}
	else {
		free(q);
	}
	return tren;

}



int dir_nar(poz q) {
	
	if (q->dite == NULL) {
		printf("\n  <dir>   .\n  <dir>   ..");
		return 0;
		
	}
	q = q->dite;
	
	printf("\n  <dir>   .\n  <dir>   .. \n  <dir>   %s",q->ime);
	
	while (q->brat != NULL){
	    q = q->brat;
		printf("\n  <dir>   %s", q->ime);
	
	} 

		return 0;
}
poz cd_nar(poz root,char* name,pos_stog head) {
	pos_stog n_e;
	
	n_e = napravi_stog_element(root);
	
	root = root->dite;
	

	while(root->brat!=NULL &&(strcmp(root->ime, name) != 0)) {
	
		root = root->brat;

	}
	if (root->brat == NULL && (strcmp(root->ime, name) == 0)) {
		
		push(head, n_e);
		return root;
		
	}
	else if((strcmp(root->ime, name) != 0)) {
		printf("\n nema tog direktorija.");
		free(n_e);
		return NULL;
	}
	
	
		push(head, n_e);
		return root;
}
int izbornik(poz root,pos_stog head) {
	
	int unos = 0;
	int d=0;
	poz q=NULL;
	pos_stog el=NULL;
	char name[100];

	printf("\n **UNESITE KOMANDU**\n\n1.md\n2.cd <ime>\n3.cd ..\n4.dir\n5.izlaz\n");

	scanf("%d", &d);
	
	
		switch (d) {
		case 1:
		{
			printf("\n<md>Unesite ime direktorija:");
			scanf_s(" %s", &name, 100);

			printf("\n");
			

			q = napravi_dir(name);
			root->dite = umetni(root->dite, q);

			return izbornik(root, head);
		}
		case 2:
		{
			printf("\n<cd>Unesite ime direktorija:");
			scanf_s(" %s", &name, 100);
			q = cd_nar(root, name, head);

			if (q == NULL) {
				return izbornik(root, head);
			}
			
			return izbornik(q, head);
		}
		case 3:
		{
			printf("<cd ..>");
			q = cd_pret(root, head);
			if (q == NULL) {
				return izbornik(root, head);
			}
			else
				return izbornik(q, head);

		}
		case 4:
		{
			printf("\nIspis svih direktorija <%s>:\n", root->ime);
			dir_nar(root);
			return izbornik(root, head);
		}
		case 5:
		{
			printf("\nBOK");
			brisi_stog(head);
			if (brisi_dir(root->dite) == 0)
				printf("\ndirektorij uspjesno izbrisan");
			else
				printf("\nNeuspjelo brisanje direktorija");
			return 0;
		}
		default:
		{
			printf("\nPogresan unos!!!");
			return izbornik(root, head);
		}


		
	}
	return 0;
}
int push(pos_stog head, pos_stog q) {
	if (q == NULL) {
		printf("\nPush greska");
		return -1;
	}
	q->next = head->next;
	head->next = q;
	return 0;
}
poz pop(pos_stog head) {

	pos_stog temp;
	poz t;

	if (head->next == NULL) {
		
		return NULL;
	}

	temp = head->next;
	head->next = temp->next;

	t = temp->_dir;

	free(temp);

	return t;

}
pos_stog napravi_stog_element(poz dir) {

	pos_stog q = NULL;

	q = (pos_stog)malloc(sizeof(stog));

	if (q == NULL) {
		printf("\n greska na stogu");
		return NULL;
	}

	q->next = NULL;
	q->_dir = dir;

	return q;

}
poz cd_pret(poz root, pos_stog head) {
	poz q;
	q=pop(head);

	if (q == NULL) {
		printf("\nPogreska!(nema roditeljskog direktorija)");
		return NULL;
	}
	return q;
}

int brisi_stog(pos_stog head) {
	if (head->next == NULL) {
		printf("\nStog uspjesno izbrisan");
		return 0;
	}
	pos_stog temp;

	while (head->next != NULL) {

		temp = head->next;
		head = temp->next;
		free(temp);
	}
	return 0;
}

int brisi_dir(poz root) {

	if (root && root->brat == NULL) 
		brisi_dir(root->brat);
	if (root && root->dite)
		brisi_dir(root->dite);

	free(root);

	return 0;


}
