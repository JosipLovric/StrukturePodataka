#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX_LINE 1024


struct _list;
typedef struct _list* poz;
struct _stablo;
typedef struct _stablo* poz_dl;

typedef struct _list {
	char drzava[MAX_LINE];
	char filename[MAX_LINE];

	poz_dl root;

	poz next;

}list;


typedef struct _stablo {

	char grad[MAX_LINE];
	int populacija;

	poz_dl desno;
	poz_dl livo;

}stablo;

//dio a
poz create_list_element_a(char* drzava, char* datoteka);
poz create_head_list_a();
poz_dl create_stablo_a(char* grad, int populacija);
int citanje_dat_a(poz* hash);
int kljuc(char* drzava);
poz_dl ucitavanje_grad_a(char* filename);
int put_into_list_a(poz q, poz head);
poz_dl put_into_root_a(poz_dl root, char* grad, int populacija);
int del_stablo(poz_dl root, poz_dl poc);
int delete_list(poz head);
poz find_drzava(poz head,char* name);
int ispisi(poz_dl root);
int print_stablo_inorder(poz_dl root, int x);
poz unos(poz* hash);



int main() {

	int i = 0;
	int test = 1;
	
	poz HASH[11];
	poz q = NULL;
	poz* hash = NULL;

	hash = HASH;
	for (i = 0; i < 11; i++) {
		HASH[i] = create_head_list_a();
	}
	while (test != 0) {
		test=citanje_dat_a(hash);
	}

	while (q == NULL) {
		q = unos(HASH);
		if (q == NULL)
			printf("\nPogresan unos\n");
	}


	ispisi(q->root);
	
	for (i = 0; i < 11; i++) {
		delete_list(*(hash + i));
	}



	return 0;
}
poz unos(poz* hash) {
	int i = 0;
	char x[MAX_LINE];
	poz q = NULL;

	printf("\nUpisi ime drzave:");
	scanf(" %s", x);

	for (i = 0; i < 11; i++) {

		if (q != NULL) {

			return q;
		}
		q = find_drzava(*(hash+i), x);

	}
	return q;

}
poz create_list_element_a(char* drzava, char* datoteka) {

	poz q = NULL;
	q = (poz)malloc(sizeof(list));
	if (q == NULL) {
		printf("Greska pri alociranju liste!\n");
		return NULL;
	}
	strcpy(q->drzava, drzava);
	strcpy(q->filename, datoteka);

	q->root = NULL;
	q->next = NULL;
	return q;

}
poz_dl create_stablo_a(char* grad, int populacija) {

	poz_dl q = NULL;

	q = (poz_dl)malloc(sizeof(stablo));
	if (q == NULL) {
		printf("Greska pri alociranju stabla!\n");
		return NULL;
	}
	strcpy(q->grad, grad);

	q->populacija = populacija;

	q->desno = NULL;
	q->livo = NULL;

	return q;
}
poz create_head_list_a() {

	poz q = NULL;
	q = (poz)malloc(sizeof(list));
	if (q == NULL) {
		printf("Greska pri alociranju liste!\n");
		return NULL;
	}

	strcpy(q->drzava, "");
	strcpy(q->filename, "");

	q->root = NULL;
	q->next = NULL;

	return q;

}

int put_into_list_a(poz q, poz head) {

	poz p = NULL;

	p = head;

	if (head->next == NULL) {
		q->next = p->next;
		p->next = q;
		return 0;
	}


	while (p->next != NULL && (strcmp(p->next->drzava, q->drzava) <= 0)) {
		p = p->next;
	}
	if (p->next == NULL && (strcmp(p->drzava, q->drzava) < 0)) {
		q->next = p->next;
		p->next = q;
		return 0;
	}
	q->next = p->next;
	p->next = q;

	return 0;

}

int citanje_dat_a(poz * hash) {

	int test = 0;
	int k = 0;
	poz q = NULL;
	char filename[MAX_LINE];
	char drzava[MAX_LINE];
	FILE* dat = NULL;



	printf("\n Upisite ime datoteke drzava:");
	scanf(" %s", filename);

	dat = fopen(filename, "r");

	if (dat == NULL) {
		printf("Pogresno unos(datoteka ne postoji)\n");
		return 1;
	}



	while (!feof(dat)) {

		test = fscanf(dat, " %s %s", drzava, filename);
		if (test == 2)
		{
			k=kljuc(drzava);
			if((*(hash+k))->next==NULL)
			*(hash + k) = create_head_list_a();
			

			q = create_list_element_a(drzava, filename);
			q->root= ucitavanje_grad_a(filename);
			put_into_list_a(q,*(hash+k));
			
		}
	}

	fclose(dat);

	return 0;

}
poz_dl ucitavanje_grad_a(char* filename) {

	int br = 0;
	int test = 0;
	poz_dl q = NULL;
	poz_dl root = NULL;
	int populacija = 0;
	char grad[MAX_LINE];
	FILE* dat = NULL;

	dat = fopen(filename, "r");

	if (dat == NULL) {
		printf("neuspjelo otvaranje datoteke %s\n", filename);
		return NULL;
	}
	while (!feof(dat)) {

		test = fscanf(dat, " %s %d", grad, &populacija);

		if (br == 0 && test == 2) {
			root = create_stablo_a(grad, populacija);
			br = 1;
			q = root;
		}
		else if (test == 2) {
			put_into_root_a(q, grad, populacija);

		}

	}
	fclose(dat);


	return root;


}
poz_dl put_into_root_a(poz_dl root, char* grad, int populacija) {


	if (root == NULL) {
		root = create_stablo_a(grad, populacija);
		return root;
	}


	if (root->populacija >= populacija)
		root->livo = put_into_root_a(root->livo, grad, populacija);
	else if (root->populacija < populacija)
		root->desno = put_into_root_a(root->desno, grad, populacija);
	return root;

}
int del_stablo(poz_dl root, poz_dl poc) {

	if (root == NULL)
		return 0;

	del_stablo(root->livo, poc);
	del_stablo(root->desno, poc);
	if (root != poc) {
		free(root);

	}
	else if (root == poc) {
		strcpy(root->grad, "");
		root->populacija = 0;
		root->desno = NULL;
		root->livo = NULL;
		free(root);
	}

	return 0;
}
int delete_list(poz head) {

	poz q = NULL;
	while (head->next != NULL)
	{
		q = head->next;
		head->next = q->next;
		del_stablo(q->root, q->root);
		free(q);
	}

	if (head->next == NULL) {
		free(head);
		return EXIT_SUCCESS;
	}
	else
		return EXIT_FAILURE;
}
poz find_drzava(poz head,char* name) {
	

	while (head->next != NULL) {

		if (strcmp(head->next->drzava, name) == 0) {
			return head->next;
		}
		else
			head = head->next;

	}
	if (head->next == NULL && strcmp(head->drzava, name) == 0)
	{
		
		return head;
	}

	return NULL;
}
int ispisi(poz_dl root) {

	int x;
	printf("\nUnesi broj:");
	scanf("%d", &x);

	print_stablo_inorder(root, x);



}
int print_stablo_inorder(poz_dl root, int x) {

	if (root == NULL) {

		return 0;
	}

	print_stablo_inorder(root->livo, x);
	if (root->populacija >= x)
		printf("\ngrad:%s -- populacija:%d\n ", root->grad, root->populacija);
	print_stablo_inorder(root->desno, x);

	return 0;
}

int kljuc(char* drzava)
{
	int k = 0;
	int i = 0;
	for (i = 0; i < 5; i++) {
	if (*(drzava) == '\0')
		break;
	k = k + *(drzava + i);
}
	return k%11;

}