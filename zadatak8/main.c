#define _CRT_SECURE_NO_WARNINGS

#include "deklaracija.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main() {

    Stablo root = { .Number = 0, .Right = NULL, .Left = NULL };
    int numb = 0;

   
    root.Number = postavi_root(numb, &root);

   //numb= Menu(numb,&root);
    izbornik(&root);
    

    return 0;
}