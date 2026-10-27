#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct _student;
typedef struct _student* Position;
struct _student
{
	char ime[128];
	char prezime[128];
	int godina_rodenja;
	Position Next;
};

void Insert(Position);
void PrintList(Position);
void InsertEnd(Position);
Position FindPrez(Position);
void DeletePrez(Position);
void InsertPrev(Position);
Position FindPrevPrez(Position);
void InsertBefore(Position);
void PrintListToFile(Position);
void ReadListFromFile(Position);
void SortList(Position);

void main(void)
{
	struct _student head;
	Position studentF = NULL;
	char izbor = 0;

	head.Next = NULL;

	while (izbor != 'K' && izbor != 'k')
	{
		printf("****************************************\r\n");
		printf("***   VJEZBA BR. 02  -  Vezane liste ***\r\n");
		printf("****************************************\r\n");
		printf("\r\n\r\n");
		printf("\t1. Unos\r\n");
		printf("\t2. Ispis\r\n");
		printf("\t3. Unos na kraj\r\n");
		printf("\t4. Pronadji po prezimenu\r\n");
		printf("\t5. Izbrisi po prezimenu\r\n");
		printf("\t6. Dodaj nakon\r\n");
		printf("\t7. Dodaj prije\r\n");
		printf("\t8. Ispisi u datoteku\r\n");
		printf("\t9. Ucitaj datoteku\r\n");
		printf("\tA. Sortiraj\r\n");
		printf("\tK. Izlaz iz programa\r\n");
		printf("\r\n\tIzbor : ");

		scanf_s(" %c", &izbor, 1);

		switch (izbor)
		{
		case '1':
			Insert(&head);
			break;
		case '2':
			PrintList(head.Next);
			break;
		case '3':
			InsertEnd(&head);
			break;
		case '4':
			studentF = FindPrez(head.Next);
			if (studentF != NULL)
				printf("\r\nTrazeni student je :\r\n%s %s %d\r\n", studentF->ime, studentF->prezime, studentF->godina_rodenja);
			else
				printf("\r\nStudent s trazenim prezimenom nije pronaden\r\n");
			break;
		case '5':
			DeletePrez(&head);
			PrintList(head.Next);
			break;
		case '6':
			InsertPrev(&head);
			break;
		case '7':
			InsertBefore(&head);
			break;
		case '8':
			PrintListToFile(&head);
			break;
		case '9':
			ReadListFromFile(&head);
			break;
		case 'A':
			SortList(&head);
			PrintList(head.Next);
			break;
		case 'k':
		case 'K':
			break;
		default:
			printf("\r\nPogresan izbor <%c>.\r\nPokusajte ponovno.\r\n", izbor);
			break;
		}
	}
}

void Insert(Position P)
{
	Position q;

	q = (Position)malloc(sizeof(struct _student));
	if (q == NULL)
		printf("\r\nGRESKA!\r\nAlokacija memorije neuspjela.\r\n");
	else
	{
		printf("Unesite ime, prezime i godinu rodenja studenta :\r\n");
		scanf_s(" %s %s %d", q->ime, 128, q->prezime, 128, &q->godina_rodenja);

		q->Next = P->Next;
		P->Next = q;
	}
}

void PrintList(Position P)
{
	if (P == NULL)
		printf("\r\nLista je prazna!\r\n");
	else
	{
		printf("\r\n\r\nU listi se nalaze : \r\n");
		while (P != NULL)
		{
			printf("\t%s %s %d\r\n", P->ime, P->prezime, P->godina_rodenja);
			P = P->Next;
		}
	}
	printf("\r\n\r\n");
}

void InsertEnd(Position P)
{
	while (P->Next != NULL)
		P = P->Next;

	Insert(P);
}

Position FindPrez(Position P)
{
	char prez[128];

	printf("\r\nUnesite prezime koje trazite : ");
	scanf_s(" %s", prez, 128);
	while (P != NULL & _strcmpi(P->prezime, prez) != 0)
		P = P->Next;

	return P;
}
void DeletePrez(Position P)
{
	Position tmp;
	char prez[128];

	printf("\r\nUnesite prezime koje zelite izbrisatie : ");
	scanf_s(" %s", prez, 128);
	while (P->Next != NULL & _strcmpi(P->Next->prezime, prez) != 0)
		P = P->Next;

	tmp = P->Next;
	if (tmp != NULL)
	{
		P->Next = tmp->Next;
		printf("\r\nIz liste se brise : %s %s %d", tmp->ime, tmp->prezime, tmp->godina_rodenja);
		free(tmp);
	}
}

void InsertPrev(Position P)
{
	Position tmp;

	tmp = FindPrez(P);
	if (tmp == NULL)
		printf("\r\nStudent nije pronaden!");
	else
		Insert(tmp);
}

Position FindPrevPrez(Position P)
{
	char prez[128];

	printf("\r\nUnesite prezime koje trazite : ");
	scanf_s(" %s", prez, 128);
	while (P->Next != NULL & _strcmpi(P->Next->prezime, prez) != 0)
		P = P->Next;

	if (P->Next == NULL)
		P = NULL;
	return P;
}
void InsertBefore(Position P)
{
	Position prev;

	prev = FindPrevPrez(P);
	if (prev == NULL)
		printf("\r\nStudent nije pronaden!");
	else
		Insert(prev);
}

void PrintListToFile(Position P)
{
	FILE* stream;
	char ime_dat[128];

	printf("\r\nUnesite ime datoteke : ");
	scanf_s(" %s", ime_dat, 128);

	fopen_s(&stream, ime_dat, "w+");
	//stream=fopen(ime_dat, "w+");
	if (stream == NULL)
		printf("\r\nDatoteka %s nije otvorena za pisanje.", ime_dat);
	else
	{
		while (P != NULL)
		{
			fprintf(stream, "%s %s %d\r\n", P->ime, P->prezime, P->godina_rodenja);
			P = P->Next;
		}
		fclose(stream);
	}
}

void ReadListFromFile(Position P)
{
	FILE* stream;
	char ime_dat[128];
	Position q;

	printf("\r\nUnesite ime datoteke : ");
	scanf_s(" %s", ime_dat, 128);

	fopen_s(&stream, ime_dat, "r");
	//stream=fopen(ime_dat, "w+");
	if (stream == NULL)
		printf("\r\nDatoteka %s nije otvorena za pisanje.", ime_dat);
	else
	{
		while (!feof(stream))
		{
			q = (Position)malloc(sizeof(struct _student));
			if (q == NULL)
				printf("\r\nGRESKA!\r\nAlokacija memorije neuspjela.\r\n");
			else
			{
				fscanf_s(stream, " %s %s %d", q->ime, 128, q->prezime, 128, &q->godina_rodenja);

				q->Next = P->Next;
				P->Next = q;
			}
		}
		fclose(stream);
	}
}

void SortList(Position P)
{
	Position end = NULL, i, j, prev_j, tmp;

	while (P->Next != end)
	{
		i = P;
		prev_j = i->Next;
		j = prev_j->Next;

		while (j != end)
		{
			if (_strcmpi(prev_j->prezime, j->prezime) < 0)
			{
				prev_j->Next = j->Next;
				i->Next = j;
				j->Next = prev_j;
			}
			else
				i = prev_j;
			prev_j = j;
			j = j->Next;
		}
		end = prev_j;
	}
}