#ifndef DEKLARACIJA_H
#define DEKLARACIJA_H

struct _Stablo;
typedef struct _Stablo* Position;
typedef struct _Stablo {

	int Number;
	Position Right;
	Position Left;
}Stablo;

 
int izbornik(Position root);
                              
Position nadi_element(int x, Position S);                  
Position dodaj_element(int X, Position S);                
int PrintInorder(Position S);                                  			
int PrintPostorder(Position S);
int PrintPreorder(Position S);                                 
Position brisi_element(int X, Position S);
Position nadi_min(Position S);
int postavi_root(int X, Position S);



 
#endif // !DEKLARACIJA_H
