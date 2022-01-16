#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX_LINE 1024

struct _listb;
typedef struct _listb* pozb;
struct _stablob;
typedef struct _stablob* poz_dlb;

typedef struct _listb {
	char grad[MAX_LINE];
	int populacija;


	pozb next;

}listb;


typedef struct _stablob {

	char drzava[MAX_LINE];
	char filename[MAX_LINE];

	pozb head;

	poz_dlb desno;
	poz_dlb livo;

}stablob;

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
poz citanje_dat_a();
poz_dl ucitavanje_grad_a(char* filename);
int put_into_list_a(poz q,poz head);
poz_dl put_into_root_a(poz_dl root, char* grad, int populacija);
int del_stablo(poz_dl root, poz_dl poc);
int delete_list(poz head);
poz find_drzava(poz head);
int ispisi(poz_dl root);
int print_stablo_inorder(poz_dl root, int x);
int dio_a();;
//dio b

poz_dlb create_stablo_element_b(char* drzava, char* filename);
pozb create_head();
poz_dlb citanje_dat_b();
poz_dlb put_into_root_b(poz_dlb root, char* drzava, char* filename);
int put_into_list_b(pozb head, pozb q);
pozb citanje_grad_b(char* filename, pozb head);
pozb create_list_element_b(char* grad, int pop);
poz_dlb nadi_al(poz_dlb root, char* drzava);
int ispisi_b(poz_dlb q, int x);
int unos_b(poz_dlb root);
int del_stablo_b(poz_dlb root, poz_dlb poc);
int delete_list_b(pozb head);
int dio_b();


int main() {

	char c;
	int test=0;

	while (!test) {
		printf("\n1-dio_a(drzave u vezanoj listi)\n2-dio_b(drzave u stablu)\n");
		scanf(" %c", &c);
		if (c == '1') {
			test = 1;
			dio_a();
		}
		else if (c == '2') {

			test = 1;
			dio_b();

		}
		else
			printf("\nPogresan unos");
	}


	return 0;
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

	strcpy(q->drzava,"");
	strcpy(q->filename,"");

	q->root = NULL;
	q->next = NULL;

	return q;

}

int put_into_list_a(poz q,poz head) {

	poz p = NULL;

	p = head;

	if (head->next==NULL) {
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

poz citanje_dat_a(poz head) {

	int test = 0;
	
	poz q = NULL;
	char filename[MAX_LINE];
	char drzava[MAX_LINE];
	FILE* dat = NULL;



	printf("\n Upisite ime datoteke drzava:");
	scanf(" %s", filename);

	dat = fopen(filename, "r");

		if (dat == NULL) {
			printf("Pogresno unos(datoteka ne postoji)\n");
			return NULL;
		}

		
		
	while (!feof(dat)) {

		test=fscanf(dat, " %s %s", drzava, filename);
		if(test==2)
			{

			q = create_list_element_a(drzava, filename);
			put_into_list_a(q, head);
		}
	}

	fclose(dat);

	return head;

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
		
		if (br == 0 && test==2) {
			root = create_stablo_a(grad,populacija);
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
		strcpy(root->grad,"");
		root->populacija = 0;
		root->desno = NULL;
		root->livo = NULL;
	}

	return 0;
}
int delete_list(poz head) {

	poz q = NULL;
	while (head->next != NULL)
	{
		q = head->next;
		head->next = q->next;
		free(q);
	}

	if (head->next == NULL) {
		return EXIT_SUCCESS;
	}
	else
		return EXIT_FAILURE;
}
poz find_drzava(poz head) {
	char x[MAX_LINE];
	printf("\nUpisi ime drzave:");
	scanf(" %s", x);

	while (head->next != NULL) {

		if (strcmp(head->next->drzava, x) == 0) {
			return head->next;
		}
		else
		head = head->next;

	}
	if (head->next == NULL && strcmp(head->drzava, x) != 0)
	{
		printf("\nNema te drzave");
		return NULL;
	}
	
	return NULL;
}
int ispisi(poz_dl root) {

	int x;
	printf("\nUnesi broj:");
	scanf("%d", &x);

	print_stablo_inorder(root, x);



}
int print_stablo_inorder(poz_dl root,int x) {

	if (root == NULL) {

		return 0;
	}
	
	print_stablo_inorder(root->livo,x);
	if(root->populacija>=x)
	printf("\ngrad:%s -- populacija:%d\n ",root->grad, root->populacija);
	print_stablo_inorder(root->desno,x);

	return 0;
}


poz_dlb create_stablo_element_b(char* drzava, char* filename) {

	poz_dlb q = NULL;
	q = (poz_dlb)malloc(sizeof(stablob));
	if (!q) {
		printf("\nGreska create stablo element");
		return NULL;
	}
	q->desno = NULL;
	q->livo = NULL;
	strcpy(q->drzava, drzava);
	strcpy(q->filename, filename);

	q->head = create_head();
	q->head = citanje_grad_b(q->filename,q->head);
	

	return q;
}
pozb create_head() {

	pozb q = NULL;
	
	q = (pozb)malloc(sizeof(listb));

	if (!q) {
		printf("\nGreska create head");
		return NULL;
	}

	q->next = NULL;
	strcpy(q->grad, "");
	q->populacija = 0;

	return q;

}

poz_dlb citanje_dat_b() {

	int test = 0;
	poz_dlb root = NULL;
	char filename[MAX_LINE];
	char dato[MAX_LINE];
	char drzava[MAX_LINE];
	FILE* dat = NULL;
	int con = 0;
	poz_dlb q = NULL;



	printf("\n Upisite ime datoteke drzava:");
	scanf(" %s", dato);

	dat = fopen(dato, "r");

	if (dat == NULL) {
		printf("Pogresno otvaranje dat\n");
		return NULL;
	}

	while (!feof(dat)) {

		test = fscanf(dat, " %s %s", drzava, filename);
		if (test == 2)
		{
			if (con == 0) {
				root = create_stablo_element_b(drzava, filename);
				con = 1;
				q = root;
			}
			else{

				put_into_root_b(q, drzava, filename);
			
			}

		}
	}

	fclose(dat);

	return root;

}
poz_dlb put_into_root_b(poz_dlb root, char* drzava, char* filename) {


	if (root == NULL) {
		root = create_stablo_element_b(drzava, filename);
		return root;
	}


	if (strcmp(root->drzava, drzava) >= 0)
		root->livo = put_into_root_b(root->livo, drzava, filename);
	else if (strcmp(root->drzava, drzava) < 0)
		root->desno = put_into_root_b(root->desno, drzava, filename);

	return root;

}
int put_into_list_b(pozb head, pozb q) {

	pozb poc = NULL;

	poc = head;

	while (head->next != NULL && head->next->populacija > q->populacija) {
		head = head->next;
	}
	if (head->next == NULL && head->populacija < q->populacija) {
		q->next = head->next;
		head->next = q;
		return 0;
	}
	else {
		q->next = head->next;
		head->next = q;
	}

	return poc;

}
pozb citanje_grad_b(char* filename,pozb head) {

	int test = 0;
	pozb q = NULL;
	char grad[MAX_LINE];
	int pop = 0;
	FILE* dat = NULL;

	dat = fopen(filename, "r");

	if (dat == NULL) {
		printf("neuspjelo otvaranje datoteke %s\n", filename);
		return NULL;
	}
	while (!feof(dat)) {

		test = fscanf(dat, " %s %d", grad, &pop);

		if (test == 2) {
			q = create_list_element_b(grad, pop);
			put_into_list_b(head, q);
		}

	}
	fclose(dat);


	return head;

}
pozb create_list_element_b(char* grad, int pop) {

		pozb q = NULL;

		q = (pozb)malloc(sizeof(listb));

		if (q == NULL) {
			printf("Greska pri alociranju liste!\n");
			return NULL;
		}

		strcpy(q->grad, grad);
		q->populacija = pop;
		
		q->next = NULL;
		return q;

	}
poz_dlb nadi_al(poz_dlb root,char* drzava) {

	if (root == NULL) {

		return root;
	}

	if (strcmp(root->drzava, drzava) > 0)
		root->livo = nadi_al(root->livo, drzava);
	else if (strcmp(root->drzava, drzava) < 0)
		root->desno = nadi_al(root->desno, drzava);
	else
		return root;



}
int ispisi_b(poz_dlb q, int x) {

	pozb head = NULL;
	head = q->head;
	if (head == NULL)
	{
		printf("\ngreska ispis_b");
		return 1;
	}

	while (head->next != NULL) {
		head = head->next;
		if (head->populacija > x)
			printf("\n Grad:%s --------- Populacija:%d", head->grad, head->populacija);

	}

	return 0;

}
int unos_b(poz_dlb root) {


	int x=0;
	char ime[MAX_LINE] = { 0 };
	poz_dlb q = NULL;


	printf("\nUpisi ime drzave:");
	scanf("%s", ime);
	printf("\nUnesi broj:");
	scanf("%d",&x);

	q = nadi_al(root, ime);
	if (!q)
		return 1;
	ispisi_b(q, x);

	return 0;
	

}
int dio_a() {

	poz head = NULL;
	poz poc = NULL;
	int i = 1;
	poz q = NULL;

	head = create_head_list_a();

	if (head == NULL) {
		printf("Pogreska pri kreiranju liste!");
		return NULL;
	}
	poc = head;
	while (i) {

		head = citanje_dat_a(head);

		if (head != NULL) {

			i = 0;
		}
		else {
			free(poc);
			head = create_head_list_a();

			if (head == NULL) {
				printf("Pogreska pri kreiranju liste!");
				return NULL;
			}
			poc = head;
		}
			

	}

	

	while (head->next != NULL) {
		head = head->next;
		head->root = ucitavanje_grad_a(head->filename);
	}


	
	

	while(q == NULL) {
		q = find_drzava(poc);
		if(!q)
		printf("ponovno unesite:");
		
	}
	ispisi(q->root);

	while (head->next != NULL) {
		head = head->next;
		del_stablo(poc, poc);
	}
	delete_list(poc);


	return 0;
}
int dio_b() {

	poz_dlb root = NULL;
	poz_dlb poc = NULL;

	root = citanje_dat_b();
	poc = root;
	unos_b(root);

	



}
int del_stablo_b(poz_dlb root, poz_dlb poc) {

	if (root == NULL)
		return 0;

	del_stablo(root->livo, poc);
	del_stablo(root->desno, poc);
	if (root != poc) {
		delete_list_b(root->head);
		free(root);

	}
	else if (root == poc) {
		delete_list_b(root->head);
		free(root);
	}

	return 0;
}
int delete_list_b(pozb head) {

	poz q = NULL;
	while (head->next != NULL)
	{
		q = head->next;
		head->next = q->next;
		free(q);
	}

	if (head->next == NULL) {
		free(head);
		return EXIT_SUCCESS;
	}
	else
		return EXIT_FAILURE;
}

