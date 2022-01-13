#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define donja_gr (10)
#define gornja_gr (90)



struct _stablo;
typedef struct _stablo* poz;
typedef struct _stablo {

	int broj;

	poz left;
	poz right;

}stablo;

struct _List;
typedef struct _List* pos_;
typedef struct _List {

	int broj;
	pos_ next;

}list;

poz Insert1(poz root, int br);
poz add_into_stablo(poz r, int br);
poz create_stablo_element(int br);
int replace(poz root, pos_ head);
int zbroji(poz root);
int insert_into_list(int br, pos_ head);
pos_ create_list_element(int br);
int print_stablo_inorder(poz root);
int put_into_file(pos_ head, int x);
int delete_list(pos_ head);
int del_stablo(poz root, poz poc);
int gen_random();



int main() {

	srand(time(NULL));

	int A[10] = { 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 };
	int i = 0;
	int x = 0;
	int con = 1;
	poz root = NULL;
	poz pocetak = NULL;
	pos_ head_A = NULL;
	pos_ head_B = NULL;


	while (con) {

		printf("\nKako zelite kreirati stablo: \n\n "
				"1-preko niza  { 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 } "
			  "\n 2-slucajni brojavi rand()\n");
		scanf("%d", &x);

		if (x == 1) {

			con = 0;

			root = create_stablo_element(0);
			head_A = create_list_element(0);
			head_B = create_list_element(0);

			for (i = 0; i < 10; i++) {

				insert_into_list(A[i], head_A);
				root = Insert1(root, A[i]);
			}

			pocetak = root;
			printf("\n------------\n");
			printf("\nStablo glasi:");
			print_stablo_inorder(root);
			printf("\n------------\n");
			printf("\nNakon funkcije replace:");
			replace(root, head_B);
			print_stablo_inorder(root);
			printf("\n------------\n");

			put_into_file(head_A, 1);
			put_into_file(head_B, 2);

			del_stablo(root, pocetak);
			delete_list(head_A);
			delete_list(head_B);

		}
		else if(x==2){
			con = 0;
			gen_random();
		}
		else {
			printf("\nPogresan unos!");
		}

	}

	return 0;
}

poz Insert1(poz root, int br) {

	if (root == NULL) {
		printf("greska insert1");
		return NULL;
	}

	if (root->left == NULL && root->right==NULL && root->broj==0) {

		root->broj = br;
		return root;
	}
	if (root->broj <= br)
		root->left = add_into_stablo(root->left, br);
	else
		root->right = add_into_stablo(root->right, br);

	return root;

}


poz add_into_stablo(poz r, int br) {

	if (r == NULL) {
		r = create_stablo_element(br);
		return r;
	}
	else if (r->broj <= br) {
		r->left = add_into_stablo(r->left, br);
	}
	else
		r->right = add_into_stablo(r->right, br);

	return r;


}
poz create_stablo_element(int br) {

	poz q = NULL;

	q = (poz)malloc(sizeof(stablo));

	if (q == NULL) {
		printf("greska create_stablo_slement");
		return NULL;
	}
	q->broj = br;
	q->left = NULL;
	q->right = NULL;

	return q;

}

int replace(poz root,pos_ head) {

	if (root == NULL) {
		return 0;
	}

	root->broj = zbroji(root->left) + zbroji(root->right);

	insert_into_list(root->broj,head);

	replace(root->left,head);
	replace(root->right,head);

	return 0;

}



int zbroji(poz root){

	

	if (root == NULL) {
		return 0;
	}

	else
		return (root->broj + zbroji(root->left) + zbroji(root->right));


}

pos_ create_list_element(int br) {
	
	pos_ q = NULL;

	q = (pos_)malloc(sizeof(list));

	if (q == NULL) {
		printf("\nGreska create_list_element");
		return NULL;
	}

	q->broj = br;
	q->next = NULL;

	return q;


}

int insert_into_list(int br, pos_ head) {

	pos_ q = NULL;

	while (head->next != NULL && head->next->broj > br) {
		head = head->next;

	}

	q = create_list_element(br);

	if (!q)
		return -1;


	if (head->next == NULL && head->broj < br) {
		q->next = head->next;
		head->next = q;
	}
	else{
	q->next = head->next;
	head->next = q;
	}

	return 0;

}
int print_stablo_inorder(poz root) {

	if (root == NULL){

		return 0;
	}
	print_stablo_inorder(root->left);
	printf("%d ", root->broj);
	print_stablo_inorder(root->right);

	return 0;
}
int del_stablo(poz root,poz poc) {

	if (root == NULL)
		return 0;
	
	del_stablo(root->left,poc);
	del_stablo(root->right,poc);
	if(root!=poc){
	free(root);
	
	}
	else if (root == poc) {
		root->broj = 0;
		root->right = NULL;
		root->left = NULL;
	}

	return 0;
}

int gen_random() {
	
	int x;
	int i;
	int* polje;
	poz root1 = NULL;
	pos_ head1 = NULL;
	pos_ head2 = NULL;

	root1 = create_stablo_element(0);
	head1 = create_list_element(0);
	head2 = create_list_element(0);

	printf("\nUnesite koliko elemenata zelite generirati:");
	scanf("%d",&x);
	polje = (int*)malloc(sizeof(int) * x);
	root1 = create_stablo_element(0);
	head1 = create_list_element(0);
	head2 = create_list_element(0);

	for (i = 0; i < x; i++) {
		*(polje + i) = donja_gr + (rand() % (gornja_gr - donja_gr + 1));
	}


	for (i = 0; i < x; i++) {

		insert_into_list(*(polje+i),head1);
		root1 = Insert1(root1, *(polje + i));
	}
	printf("\n------------\n");
	printf("\nStablo glasi:");
	print_stablo_inorder(root1);
	replace(root1, head2);
	printf("\n------------\n");
	printf("\nNakon funkcije replace:");
	print_stablo_inorder(root1);
	printf("\n------------\n");

	put_into_file(head1, 1);
	put_into_file(head2, 2);


	delete_list(head1);
	delete_list(head2);
	del_stablo(root1,root1);

	return 0;

}
int put_into_file(pos_ head,int x) {

	FILE* dat = NULL;

	if (x == 1)
		dat = fopen("prvi_unos.txt", "w");
	else if (x == 2)
		dat = fopen("replace_unos.txt", "w");
	else 
		return 1;

	while (head->next != NULL) {
		head = head->next;
		fprintf(dat, " %d ", head->broj);
	}
	

	fclose(dat);
	return 0;

}
int delete_list(pos_ head) {

	pos_ q = NULL;
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