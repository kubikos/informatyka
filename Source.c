#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <time.h>
#include <stdbool.h>

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

void deleteAll(pacjent* element)
{
	if (element == NULL)
	{
		first = NULL;
		last = NULL;
		return;
	}
	deleteAll(element->next);
	free(element);
	return;
}

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


void deleteOne(pacjent*element,int b)
{
	b--;
	if (b == 0)
	{
		if (element->next == NULL && element->prev != NULL)
		{
			element->prev->next = NULL;
			last = element->prev;
		}
		else if (element->prev == NULL && element->next != NULL)
		{
			element->next->prev = NULL;
			first = element->next;
		}
		else if (element->prev == NULL && element->next == NULL)
		{
			last = NULL;
			first = NULL;
		}
		else if(element->next != NULL && element->prev != NULL)
		{
			element->next->prev = element->prev;
			element->prev->next = element->next;
		}
		free(element);
		return;
	}
	
	deleteOne(element->next, b);
}

void swapElements(pacjent* A, pacjent* B)
{
	if (A->prev != NULL)
		A->prev->next = B;
	else
		first = B;

	if (B->next != NULL)
		B->next->prev = A;
	else
		last = A;

	A->next = B->next;
	B->prev = A->prev;
	A->prev = B;
	B->next = A;
}

int length(char* word)
{
	int c = 0;
	while (word[c] != '\0')
	{
		c++;
	}

	c++;
	return c;
}

char* upper_string(char* s) {
	int c = 0;
	char* out = (char*)malloc(length(s) * sizeof(char));
	while (s[c] != '\0') {
		if (s[c] >= 'a' && s[c] <= 'z') {
			out[c] = s[c] - 32;
		}
		c++;
	}

	out[c] = '\0';

	return out;
}


bool sort(pacjent* element, bool swap,int parameter, bool incr)
{
	if (element->next == NULL)
		return swap;

	switch (parameter)
	{
	case 1:
		if (incr)
		{
			if (strcmp(upper_string(element->imie),upper_string(element->next->imie)) > 0)
			{
				swap = true;
				swapElements(element, element->next);
				return sort(element, swap, parameter, incr);
			}
		}
		else
		{
			if (strcmp(upper_string(element->imie), upper_string(element->next->imie)) < 0)
			{
				swap = true;
				swapElements(element, element->next);
				return sort(element, swap, parameter, incr);
			}
		}
		break;
	case 2:
		if (incr)
		{
			if (strcmp(upper_string(element->nazwisko), upper_string(element->next->nazwisko)) > 0)
			{
				swap = true;
				swapElements(element, element->next);
				return sort(element, swap, parameter, incr);
			}
		}
		else
		{
			if (strcmp(upper_string(element->nazwisko), upper_string(element->next->nazwisko)) < 0)
			{
				swap = true;
				swapElements(element, element->next);
				return sort(element, swap, parameter, incr);
			}
		}
		break;
	case 3:
		if (incr)
		{
			if (element->wiek > element->next->wiek)
			{
				swap = true;
				swapElements(element, element->next);
				return sort(element, swap, parameter, incr);
			}
		}
		else
		{
			if (element->wiek < element->next->wiek)
			{
				swap = true;
				swapElements(element, element->next);
				return sort(element, swap, parameter, incr);
			}
		}
		break;
	case 4:
		if (incr)
		{
			if (strcmp(upper_string(element->objawa), upper_string(element->next->objawa)) > 0)
			{
				swap = true;
				swapElements(element, element->next);
				return sort(element, swap, parameter, incr);
			}
		}
		else
		{
			if (strcmp(upper_string(element->objawa), upper_string(element->next->objawa)) < 0)
			{
				swap = true;
				swapElements(element, element->next);
				return sort(element, swap, parameter, incr);
			}
		}
		break;
	default:
		return swap;
		break;
	}

	return sort(element->next, swap, parameter, incr);
}

void sortAsk()
{
	int a,tmp;
	bool incr;
	printf("Po czym chcesz sortowac? \n>Imie - 1\n>Nazwisko - 2\n>Wiek - 3\n>Objawa - 4\n");
	scanf("%d", &a);
	printf("Rosnaca - 1\n Malejaca - 0\n");
	scanf("%d", &tmp);
	incr = tmp;
	while(sort(first, false, a, incr))
	{
		
	}
}



/*
void initialize()
{
	first = (pacjent*)malloc(sizeof(pacjent));
	last = (pacjent*)malloc(sizeof(pacjent));

}*/




int main()
{
	int a = 1;
	while (a != 0)
	{
		printf("\n..........................\n>Dodaj pacjenta - 1\n>Wyswietl wszystko - 2 \n>Wyswietl zakres - 3 \n>Wyswietl pojedynczy i nastepny lub poprzedni - 4\n>Usun wszystkie elementy - 5\n>Usun wybrany element - 6\n>Posortuj - 7\n>Wyjdz - 0\n");
		scanf("%d", &a);
		system("cls");
		switch (a)
		{
			int start, end,b;
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
				printf("podaj zakres \n>poczatek\n");
				scanf("%d", &start);
				printf(">koniec\n");
				scanf("%d", &end);
				if (rangePrint(first, start, end) != 0)
					printf("Error!\n");
				break;
			case 4:
				printf("Ktory element wyswietlic? \n");
				scanf(" %d", &start);
				singlePrint(start);
				break;
			case 5:
				deleteAll(first);
				break;
			case 6:
				printf("Ktory element chcesz usunac? \n");
				scanf("%d", &b);
				deleteOne(first, b);
				break;
			case 7:
				sortAsk();
				break;
			default:
				a = 0;
				break;
		}

	}
	return 0;
}




