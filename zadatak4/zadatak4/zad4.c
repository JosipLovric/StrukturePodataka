#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE	(1024)

// definicija strukture polinom(poli)
struct _polinom;
typedef struct _polinom* pozicija;
typedef struct _polinom {
	int koeficijent;
	int eksponent;
	pozicija next;
}poli;

//----funkcije za unos dva polinoma u datoteci-----
int citanje_dat(pozicija p1,pozicija p2);
int unos(int k,int e,pozicija p);
int ispis(pozicija p);
int zbrajanje(pozicija p1, pozicija p2,pozicija zbroj);
int mnozenje(pozicija p1, pozicija p2, pozicija mnoz);
int oslobodi(pozicija p);
int oslobodi_SVE(pozicija* p,int n);

//---------za bilo koju datoteku-------
int broji_poli(char* naziv);
pozicija* citanje_n_polinoma(char* naziv); // dinamicki alocira polinome
int ispis_sve(pozicija* p,int n);
pozicija* odabir(pozicija* p,int n);


// zakomentirani dio maina je staro rjesenje zadatka-ogranicen na samo dva polinoma
int main() {

	//poli head1 = { .eksponent = 0, .koeficijent = 0, .next = NULL };
	//poli head2 = { .eksponent = 0, .koeficijent = 0, .next = NULL };
	//poli zbroj_head= { .eksponent = 0, .koeficijent = 0, .next = NULL };
	//poli mnozenje_head = { .eksponent = 0, .koeficijent = 0, .next = NULL };


	//citanje_dat(&head1,&head2);

	//ispis(&head1);
	//ispis(&head2);

	
	//zbrajanje(&head1, &head2, &zbroj_head);
	//mnozenje(&head1, &head2, &mnozenje_head);
	
	//oslobodi_SVE(&head1, &head2, &zbroj_head, &mnozenje_head);

	odabir(NULL,0);				//-----omogucuje upis n polinoma te operacije nad njima 



	return 0;
}
//UCITAVANJE DATOTEKE (NA LAKSI NACIN)
int citanje_dat(pozicija p1,pozicija p2){

	if (p1 == NULL || p2 == NULL) {
		printf("\nGreska**(p=NULL)**");
		return -1;
	}

	char buffer[MAX_SIZE];
	char* pomak = NULL;
	int koef=0;
	int exp=0;
	int n = 0;
	int upis = 0;
	int i = 0;
	char naziv[50] = { " " };
	FILE* dat = NULL;

	printf("Unesi ime dat:\n");
	scanf(" %s", naziv);

	dat=fopen(naziv, "r");

	if (dat == NULL) {
		printf("\nGreska(NEUSPJELO OTVARANJE DATOTEKE)");
		return -1;
	}
	
	//UNOS PRVOG POLINOMA

	fgets(buffer, MAX_SIZE, dat);
	pomak = buffer;

	while (strlen(pomak) > 0) {

		upis = sscanf(pomak, " %d %d %n ", &koef, &exp, &n);
	

		if (upis == 2) {
			unos(koef, exp, p1);
			pomak = pomak + n;
		}
		else
			break;
		
	
	}

	//UNOS DRUGOG POLINOMA

	fgets(buffer, MAX_SIZE, dat);
	pomak = buffer;

	while (strlen(pomak) > 0) {

		upis = sscanf(pomak, " %d %d %n ", &koef, &exp, &n);


		if (upis == 2) {
			unos(koef, exp, p2);
			pomak = pomak + n;
		}
		else
			break;


	}

	fclose(dat);

	ispis(p1);
	ispis(p2);
	
	return 0;

}


int unos(int k,int e,pozicija p){
	
	pozicija q = NULL;
	pozicija temp = NULL;
	
	q = (pozicija)malloc(sizeof(poli));

	if (q == NULL) {
		printf("\nGreska(q==NULL)");
		return -1;
	}

	q->koeficijent = k;
	q->eksponent = e;

	while (p->next != NULL && p->next->eksponent > e) {
		p = p->next;
	}
	//ako je zadnji element 
		if (p->next == NULL && p->eksponent>e ) {
		
			q->next = p->next;
			p->next = q;

		}
	//ako su jednaki
		else if (p->next != NULL && p->next->eksponent == e) {
			p->next->koeficijent += k;
				
				if (p->next->koeficijent == 0) {
					temp=p->next;
					p->next = temp->next;
					free(temp);
				}
			free(q);
		}

		else {
			q->next = p->next;
			p->next = q;
		}
	
	

	return 0;
}


int ispis(pozicija p) {

	if (p == NULL) {
		printf("\nGreska!!");
		return -1;
	}

	if (p->next == NULL) {
		printf("\n*****Polinom je prazan!!");
		return 0;
	}

	printf(" polinom glasi:    ");
		while (p->next != NULL) {
			p = p->next;
			printf("%d x(%d) ", p->koeficijent, p->eksponent);
			
		}


	return 0;
}
int zbrajanje(pozicija p1, pozicija p2,pozicija zbroj) {

	if (p1 == NULL || p2 == NULL || zbroj == NULL) {
		printf("\nGreska!");
		return -1;
	}
	
	while (p1->next != NULL && p2->next != NULL) {
		
		p1 = p1->next;
		p2 = p2->next;
		unos(p1->koeficijent, p1->eksponent, zbroj);
		unos(p2->koeficijent, p2->eksponent, zbroj);
		
	}
		
	if (p1->next == NULL) {
			while (p2->next != NULL) {
				p2 = p2->next;
				unos(p2->koeficijent, p2->eksponent, zbroj);

			}
		}
	else {
		while (p1->next != NULL) {
			p1 = p1->next;
			unos(p1->koeficijent, p1->eksponent, zbroj);

		}
	}

	printf("\nZbroj ");
	ispis(zbroj);

	return 0;
}
int mnozenje(pozicija p1, pozicija p2, pozicija mnoz) {
	
	if (p1 == NULL || p2 == NULL || mnoz == NULL) {
		printf("\nGreska!");
		return -1;
	}

	pozicija temp = p2;

	while (p1->next != NULL) {
		
		p1 = p1->next;
		
		while (p2->next!= NULL) {
		
			p2 = p2 -> next;
			
			unos((p1->koeficijent) * (p2->koeficijent), (p1->eksponent) + (p2->eksponent), mnoz);
		}
		
		p2 = temp;
	}
	
	printf("\nProdukt");
	ispis(mnoz);


	return 0;
}

int oslobodi(pozicija p) {

	if (p == NULL ) {
		printf("\nGreska!");
		return -1;
	}

	pozicija head_liste = NULL;
	pozicija temp = NULL;

	head_liste = p;

	while (p->next != NULL) {
		temp = p->next;
		p->next = temp->next;
		free(temp);

	}

	if (head_liste->next == NULL) {
		
		printf("\n****MEMORIJA USPJESNO IZBRISANA****");
		return 0;
		
	}
	else {
		printf("\n****NEUSPJELO BRISANJE****\n--GRESKA--");
		return -1;
	}

	
}

int oslobodi_SVE(pozicija* p,int n) {
	
	if (p==NULL) {
		printf("\nGreska!");
		return -1;
	}

	int i = 0;

	for(i=0;i<4;i++){
		
		oslobodi(*(p+i));
	}


	
	return 0;
}

int broji_poli(char* naziv) {
	
	char buffer[MAX_SIZE];
	int br = 0;
	FILE* dat = NULL;

	

	

	dat = fopen(naziv, "r");

	if (dat == NULL) {
		
		printf("\nGreska pri otvaranju.");
		
		return -1;
	}

	while (!feof(dat)) {
		fgets(buffer, MAX_SIZE, dat);
		br++;
	}

	

	fclose(dat);

	return br;

}

pozicija* citanje_n_polinoma(char* naziv)
{
	char buffer[MAX_SIZE] = { 0 };
	char* pomak = NULL;

	int n = 0, i = 0, koef = 0, exp = 0, upis = 0, pom = 0;
	pozicija* polje_pol = NULL;
	FILE* dat = NULL;


	dat = fopen(naziv, "r");

	if (dat == NULL) {
		printf("\nGreska(NEUSPJELO OTVARANJE DATOTEKE)");
		return NULL;
	}

	n = broji_poli(naziv);
	
	
	polje_pol = (pozicija*)malloc(n * sizeof(*polje_pol));
	
	if (polje_pol == NULL) {
		
		printf("\nGreska");
		fclose(dat);
		return NULL;
	}


	
	//postavljanje head


	for (i = 0; i < n; i++) {
		*(polje_pol + i) = (pozicija)malloc(sizeof(poli));
		
			if (*(polje_pol + i) == NULL) {
				printf("\nGreska");
				return NULL;
			}

			(*(polje_pol + i))->next = NULL;
			(*(polje_pol + i))->koeficijent = 0;
			(*(polje_pol + i))->eksponent = 0;
	

		}
	
	for (i = 0; i < n; i++) {
		
		
		
		fgets(buffer, MAX_SIZE, dat);
		pomak = buffer;

		while (strlen(pomak) > 0) {

			upis = sscanf(pomak, " %d %d %n ", &koef, &exp, &pom);


			if (upis == 2) {
				unos(koef, exp,*(polje_pol + i ));
				pomak = pomak + pom;
			}
			else
				break;
		}
		


	}
	
	fclose(dat);
	
	return polje_pol;
}

int ispis_sve(pozicija* p,int n) {

	if (p == NULL) {
		printf("\nGreska!!");
		return -1;
	}
	int i=0;
	for (i = 0; i < n; i++) {
		printf("\n %d.",i + 1);
		ispis(*(p + i));
	}

	return 0;

}
pozicija* odabir(pozicija* p,int n) {
	
	int br = 0;
	int i = 0, j = 0;
	char naziv[50] = { " " };
	
	poli rezultat = { .eksponent = 0, .koeficijent = 0, .next = NULL };


	 
	printf("\n\n 1.------UCITAJ ZELJENU DATOTEKU-----------");
	printf("\n 2.--------ISPIS POLINOMA------------------");
	printf("\n 3.--------ZBRAJANJE POLINOMA (P1 + P2)----");
	printf("\n 4.--------MNOZENJE POLINOMA (P1 * P2)-----\n");
	printf("\n 0.-------------**IZLAZ**------------------\n");
	printf("**************************UNESI KOMANDU:");
	 
	scanf("%d", &br);

	
	 switch (br) {
	 
	//IZLAZ IZ PROGRAMA

	 case 0: {
		
		 if(n!=0){						
			oslobodi_SVE(p,n);
			free(p);
		 }
		
		 printf("\n..............BOK..............");
		
		 return EXIT_SUCCESS;
	 }
			//-----UCITAVANJE DAT
	 case 1: {
		 if (n != 0) {
			 oslobodi_SVE(p, n);
			 free(p);
		 }
		 printf("\nUnesi ime dat:\n");
		 scanf(" %s", naziv);
		 p = citanje_n_polinoma(naziv);
		 n = broji_poli(naziv);
		 return odabir(p,n);
	 }
		   //---ISPIS LISTE
	 case 2: {
		 if (n == 0) {                  
			 printf("\nNISTE UCITALI DATOTEKU");
			 return odabir(p, n);
		 }
		 
		 else {
			 ispis_sve(p, n);
			 return odabir(p, n);
		 }
		 
	 }

		   //---zbraja p1+p2
	 case 3: {
		 printf("\nUnesi 1.polinom:");
		 scanf("%d", &i);
		 printf("\nUnesi 2.polinom:");
		 scanf("%d", &j);

		 zbrajanje(*(p + i - 1), *(p + j - 1), &rezultat);

		 return odabir(p,n);
	 }
		// mnozi p1*p2
	 case 4: {
		 printf("\nUnesi 1.polinom:");
		 scanf("%d", &i);
		 printf("\nUnesi 2.polinom:");
		 scanf("%d", &j);

		 mnozenje(*(p + i - 1), *(p + j - 1), &rezultat);


		 return odabir(p,n);
	 }
		   
	 

	 default: {

		 printf("\n\n******POGRESAN UNOS*********\n\n");
		 return odabir(p,n);
		}
	 }

 }





