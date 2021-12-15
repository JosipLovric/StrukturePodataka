#ifndef DEKLARACIJA_H
#define DEKLARACIJA_H



struct _direktorij;
typedef struct _direktorij* poz;
typedef struct _direktorij {
	
	char ime[100];
	poz brat;
	poz dite;

}dir;

struct _stog;
typedef struct _stog* pos_stog;
typedef struct _stog {
	poz _dir;
	pos_stog next;
}stog;


poz umetni(poz tren, poz q);
poz napravi_dir(const char* name);
int ispis(pos_stog head,pos_stog temp);
poz cd_nar(poz root,char* ime,pos_stog head);
int dir_nar(poz q);
int izbornik(poz root,pos_stog head);
int push(pos_stog head, pos_stog q);
pos_stog napravi_stog_element(poz dir);
poz pop(pos_stog head);
poz cd_pret(poz root,pos_stog head);
int brisi_stog(pos_stog head);
int brisi_dir(poz root);



#endif // !1
