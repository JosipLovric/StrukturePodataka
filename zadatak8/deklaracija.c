#define _CRT_SECURE_NO_WARNINGS

#include "deklaracija.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int izbornik(Position root) {
       
    int key;
    int ispis;
    Position temp = NULL;
    temp = (Position)malloc(sizeof(Stablo));
    if (!temp) {
        printf("\nGreska pri alokaciji");
        return -1;
    }

    printf("Menu:\n");
    printf("1-Ispis\n2-Pretrazivanje\n3-Unos novog elemanta\n4-Brisanje\n0-Izlaz\n\n");
    scanf("%d", &key);

    switch (key)
    {
    case 1:
    {

        printf("Kakav ispis zelite?\n");
        printf("1-Inorder\n2-Postorder\n3-Preorder\n\n");
        scanf("%d", &ispis);

        switch (ispis)
        {

        case 1:
        {
            PrintInorder(root);
            puts("");
            return izbornik(root);
        }
        case 2:
        {

            PrintPostorder(root);
            puts(" ");
            return izbornik(root);
        }
        case 3:
        {
            PrintPreorder(root);
            puts("");
            return izbornik(root);
        }

        }
    }

    case 2:
    {

        printf("Unesite vrijednost koju zelite naci:");
        scanf("%d", &ispis);

        temp = nadi_element(ispis, root);

        if (temp == NULL)
            printf("Element ne postoji u stablu!\n\n");

        else
            printf("Element %d postoji u stablu!\n\n", temp->Number);
        return izbornik(root);
    }
    case 3: 
    {
        printf("Unesite element koji zelite unjeti:\n");
        scanf("%d", &ispis);

        temp = nadi_element(ispis, root);

        if (temp != NULL) {

            printf("Element vec postoji!\n\n");
            free(temp);
        }

        else {

            temp = dodaj_element(ispis, root);
            printf("Element %d je dodan u stablo!\n\n", ispis);
        }

        return izbornik(root);

    }
    case 4:
    {
        printf("Unesite element za brisanje:\n");
        scanf("%d", &ispis);

        temp = nadi_element(ispis, root);

        if (temp == NULL) {

            printf("Elementa nema unutar stabla!\n");
            free(temp);
        }

        else {

            temp = brisi_element(ispis, root);

            if (temp != NULL)
                printf("Emlement %d je izbrisan iz stabla!\n\n", ispis);
        }
    }

    default:
    {
        printf("\nPogresan unos.");
        return izbornik(root);
    }
    case 0:
    {
        printf("\nZAVRSETAK PROGRAMA");
        return 0;
    }
    
    }
    free (temp);
    return 0;
}

int PrintInorder(Position S) {

    if (S == NULL)
        return 0;

    PrintInorder(S->Left);
    printf("%d ", S->Number);
    PrintInorder(S->Right);

    return 0;
}

int PrintPostorder(Position S) {

    if (S == NULL)
        return 0;

    PrintPostorder(S->Left);
    PrintPostorder(S->Right);
    printf("%d ", S->Number);

    return 0;
}

int PrintPreorder(Position S) {

    if (S == NULL)
        return 0;

    printf("%d ", S->Number);
    PrintPreorder(S->Left);
    PrintPreorder(S->Right);

    return 0;
}

Position dodaj_element(int X, Position S) {

    if (S == NULL) {

        S = (Position)malloc(sizeof(Stablo));

        if (!S)
            return NULL;

        S->Number = X;
        S->Left = NULL;
        S->Right = NULL;
    }

    else if (S->Number > X)
        S->Left = dodaj_element(X, S->Left);


    else
        S->Right = dodaj_element(X, S->Right);

    return S;
}

Position brisi_element(int X, Position S) {

    Position temp = NULL;

    if (S == NULL)
        printf("nema tog elementa\n");

    else if (S->Number > X)
        S->Left = brisi_element(X, S->Left);

    else if (S->Number < X)
        S->Right = brisi_element(X, S->Right);

    else if (S->Left != NULL && S->Right != NULL) {

        temp = nadi_min(S->Right);
        S->Number = temp->Number;
        S->Right = brisi_element(S->Number, S->Right);
    }

    else {

        temp = S;

        if (S->Left == NULL)
            S = S->Right;

        else
            S = S->Left;

        free(temp);
    }

    return S;
}

Position nadi_element(int x, Position S) {

    int i = 0;

    for (i = 0; i < 1; i++) {

        if (S == NULL)
            return NULL;

        else if (S->Number > x)
            return nadi_element(x, S->Left);

        else if (S->Number < x)
            return nadi_element(x, S->Right);

        else
            return S;
    }

    return S;
}

Position nadi_min(Position S) {

    if (S == NULL)
        return NULL;

    else if (S->Left == NULL)
        return S;

    else
        return nadi_min(S->Left);
}

int postavi_root(int X, Position S) {

    X = 1;

    while (X != 0) {  

        printf("Unesite korijen stabla: ");
        scanf("%d", &X);

        puts("");

        if (X != 0)
            return X;
    }

    return X;
}

