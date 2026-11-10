#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<stdlib.h>

struct _Cvor;
typedef struct _Cvor* Position;

struct _Cvor
{
	int Element;
	Position Next;
};


void ReadListFromFile(Position);
void PrintList(Position);
void Presjek(Position, Position, Position);
void Unija(Position, Position, Position);

void main(void)
{
	Position headL1, headL2, headP, headU;

	headL1 = (Position)malloc(sizeof(struct _Cvor));
	if (headL1 == NULL) return;
	headL1->Next = NULL;

	headL2 = (Position)malloc(sizeof(struct _Cvor));
	if (headL2 == NULL) return;
	headL2->Next = NULL;

	headP = (Position)malloc(sizeof(struct _Cvor));
	if (headP == NULL) return;
	headP->Next = NULL;

	headU = (Position)malloc(sizeof(struct _Cvor));
	if (headU == NULL) return;
	headU->Next = NULL;

	ReadListFromFile(headL1);
	ReadListFromFile(headL2);

	printf("\r\nLista L1 :");
	PrintList(headL1->Next);

	printf("\r\nLista L2 :");
	PrintList(headL2->Next);

	Presjek(headL1->Next, headL2->Next, headP);
	printf("\r\nPresijek L1 i L2 je :");
	PrintList(headP->Next);

	Unija(headL1->Next, headL2->Next, headU);
	printf("\r\nUnija L1 i L2 je :");
	PrintList(headU->Next);

	printf("\r\n");

	free(headL1);
	free(headL2);
	free(headP);
	free(headU);
}

void ReadListFromFile(Position P)
{
	FILE* stream;
	char ime_dat[1024];
	Position q, tmp;

	printf("\r\nUnesite ime datoteke za čitanje : ");
	scanf_s(" %s", ime_dat, 1024);

	fopen_s(&stream, ime_dat, "r");
	if (stream == NULL)
		printf("\r\nGreska!\r\nDatoteka: %s  nije otvorena.", ime_dat);
	else
	{
		while (!feof(stream))
		{
			q = (Position)malloc(sizeof(struct _Cvor));
			if (q == NULL)
				printf("\r\nGreska!\r\nMemorija nije alocirana.");
			else
			{
				fscanf_s(stream, " %d", &q->Element);

				tmp = P;

				while (tmp->Next != NULL && tmp->Next->Element > q->Element)
					tmp = tmp->Next;
				q->Next = tmp->Next;
				tmp->Next = q;
			}
		}
		fclose(stream);
	}
}

void PrintList(Position P)
{
	while (P != NULL)
	{
		printf(" %d", P->Element);
		P = P->Next;
	}
}

void Presjek(Position L1, Position L2, Position P)
{
	Position q;

	while (L1 != NULL && L2 != NULL)
	{
		if (L1->Element > L2->Element)
			L1 = L1->Next;
		else if (L1->Element < L2->Element)
			L2 = L2->Next;
		else
		{
			q = (Position)malloc(sizeof(struct _Cvor));
			if (q == NULL)
				printf("\r\nGreska!\r\nMemorija nije alocirana.");
			else
			{
				q->Element = L1->Element;

				q->Next = P->Next;
				P->Next = q;

				P = q;
			}
			L1 = L1->Next;
			L2 = L2->Next;
		}
	}

}
void Unija(Position L1, Position L2, Position U)
{
	Position q, tmp;
	int tmp_element = 0;

	while (L1 != NULL && L2 != NULL)
	{
		if (L1->Element > L2->Element)
		{
			tmp_element = L1->Element;
			L1 = L1->Next;
		}
		else if (L1->Element < L2->Element)
		{
			tmp_element = L2->Element;
			L2 = L2->Next;
		}
		else
		{
			tmp_element = L1->Element;
			L1 = L1->Next;
			L2 = L2->Next;
		}

		q = (Position)malloc(sizeof(struct _Cvor));
		if (q == NULL)
			printf("\r\nGreska!\r\nMemorija nije alocirana.");
		else
		{
			q->Element = tmp_element;

			q->Next = U->Next;
			U->Next = q;

			U = q;
		}
	}

	if (L1 == NULL)
		tmp = L2;
	else
		tmp = L1;

	while (tmp != NULL)
	{
		q = (Position)malloc(sizeof(struct _Cvor));
		if (q == NULL)
			printf("\r\nGreska!\r\nMemorija nije alocirana.");
		else
		{
			q->Element = tmp->Element;

			q->Next = U->Next;
			U->Next = q;

			U = q;
		}
		tmp = tmp->Next;
	}

}