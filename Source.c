#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct pacjent
{
	char *imie;
	char *nazwisko;
	int wiek;
	char *objawa;
	struct pacjent *next;
	struct pacjent *prev;
}pacjent;

pacjent* last = NULL;
pacjent* first = NULL;


void forwardPrint(pacjent* element)
{
	if (element == NULL)
		return;

	printf("imie to: %s \n nazwisko to: %s \n wiek to: %d \n objawa to: %s \n", element->imie,element->nazwisko,element->wiek,element->objawa);
	printf("-------------------------\n");
	forwardPrint(element->next);
	
}

void backwardsPrint(pacjent* element)
{
	if (element == NULL)
		return;

	printf("imie to: %s \n nazwisko to: %s \n wiek to: %d \n objawa to: %s \n", element->imie, element->nazwisko, element->wiek, element->objawa);
	printf("-------------------------\n");
	backwardsPrint(element->prev);

}

int wyswietl()
{
	char a;
	printf("Od poczatku czy od konca? f/l \n");
	scanf(" %c", &a);
	if (a == 'f')
	{
		forwardPrint(first);
	}
	else
	{
		backwardsPrint(last);
	}
	return 0;
}



int rangePrint(pacjent* element,int start, int end)
{
	start--;
	end--;

	if (element == NULL)
		return 1;

	if (start <= 0)
	{
		printf("imie to: %s \n nazwisko to: %s \n wiek to: %d \n objawa to: %s \n", element->imie, element->nazwisko, element->wiek, element->objawa);
		printf("-------------------------\n");
	}
	if (end == 0)
		return 0;

	return rangePrint(element->next,start,end);

}
void singlePrint(int start)
{
	int a;
	rangePrint(first, start, start);
	printf("Co chcesz zrobic? \n Wyswietl nastepny -1 \n Wyswietl poprzedni -2\n Przejdz do menu -0 \n");
	scanf("%d", &a);
	if (a == 1)
	{
		if (rangePrint(first, start + 1, start + 1) != 0)
			printf("Error!");
	} else if (a == 2)
	{
		if (rangePrint(first, start - 1, start - 1) != 0)
			printf("Error!");
	}
}

int dodaj(char*imie, char*nazwisko, int wiek, char*objawa)
{
	pacjent *nowy;
	nowy = (pacjent*)malloc(sizeof(pacjent));
	nowy->imie = (char*)malloc(sizeof(imie));
	nowy->nazwisko = (char*)malloc(sizeof(nazwisko));
	nowy->objawa = (char*)malloc(sizeof(objawa));
	nowy->imie = imie;
	nowy->nazwisko = nazwisko;
	nowy->wiek = wiek;
	nowy->objawa = objawa;
	
	if (first == NULL)
	{
		nowy->next = NULL;
		nowy->prev = NULL;
		first = nowy;
		last = nowy;
	}
	else
	{
		last->next = nowy;
		nowy->prev = last;
		nowy->next = NULL;
		last = nowy; 
	}
	return 0;
}
/*
void initialize()
{
	first = (pacjent*)malloc(sizeof(pacjent));
	last = (pacjent*)malloc(sizeof(pacjent));

}*/

int main()
{
	int a=1;


	
	
	while (a != 0)
	{
		printf("\n..........................\n>Dodaj pacjenta - 1\n>Wyswietl wszystko - 2 \n>Wyswietl zakres - 3 \n>Wyswietl pojedynczy i nastepny lub poprzedni - 4\n>Wyjdz - 0\n");
		scanf("%d", &a);
		system("cls");
		switch (a)
		{
			int start, end;
			case 1:
			{
				pacjent tmp;
				tmp.imie = (char*)malloc(sizeof(char) * 20);
				tmp.nazwisko = (char*)malloc(sizeof(char) * 30);
				tmp.objawa = (char*)malloc(sizeof(char) * 30);

				printf("Podaj imie \n");
				scanf("%s", tmp.imie);
				printf("Podaj nazwisko \n");
				scanf("%s", tmp.nazwisko);
				printf("Podaj objawe \n");
				scanf("%s", tmp.objawa);
				printf("Podaj wiek \n");
				scanf("%d", &tmp.wiek);
				dodaj( tmp.imie, tmp.nazwisko, tmp.wiek, tmp.objawa);
				break;

			}
			case 2:
				wyswietl();
				break;
			case 3:
				printf("podaj zakres \n");
				scanf("%d %d", &start, &end);
				if (rangePrint(first, start, end) != 0)
					printf("Error!\n");
				break;
			case 4:
				printf("Ktory element wyswietlic? \n");
				scanf(" %d", &start);
				singlePrint(start);
				break;

		}

	}
	return 0;
}




