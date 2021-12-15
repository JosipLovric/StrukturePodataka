#define _CRT_SECURE_NO_WARNINGS

#include "deklaracija.h"
#include <stdio.h>

int main() {


	stog head;
	dir root;

	strcpy(root.ime, "C:");
	root.brat = NULL;
	root.dite = NULL;
	
	head.next = NULL;
	head._dir = NULL;
	//push(&head, napravi_stog_element(&root));

	//root.dite =napravi_dir("jakov");
	//root.dite->brat = napravi_dir("josip");
	//q = napravi_dir("zarko");
	//root.dite = umetni(root.dite, q); //md
	//p = cd_nar(&root, "josip");

	//printf("\n\n ispis cd: %s", p->ime);
	//dir_nar(&root);

	izbornik(&root, &head);
	/*p = napravi_stog_element(q);

	push(&head, p);

	q = napravi_dir("jakov");
	p = napravi_stog_element(q);
	push(&head, p);
	r = pop(&head);

	printf("\n jao::::::: %s", r->ime);
*/


	return 0;
}