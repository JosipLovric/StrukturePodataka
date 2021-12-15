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
	


	izbornik(&root, &head);
	


	return 0;
}
