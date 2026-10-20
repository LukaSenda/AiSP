#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h> 
#include<time.h> 

struct _student;
typedef struct _student* Position;

struct _student
{
	char ime[128];
	char prezime[128];
	int godina_rodenja;
	Position Next;
};

void Insert(Position P);
void PrintList(Position P);
void InsertEnd(Position P);
Position FindPrez(Position P);
void DeletePrez(Position P);

int main()
{
	struct _student head;
	Position studentF = NULL;
	char izbor = 0;

	head.Next = NULL;

	while (izbor != 'K' && izbor != 'k')
	{
		
		printf("\t1. Unos na pocetak\n");
		printf("\t2. Ispis liste\n");
		printf("\t3. Unos na kraj\n");
		printf("\t4. Pronadji po prezimenu\n");
		printf("\t5. Izbrisi po prezimenu\n");
		printf("\tK. Izlaz iz programa\n");
		printf("\n\tIzbor: ");

		scanf(" %c", &izbor);

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
				printf("\nPronadjeni student: %s %s %d\n",
					studentF->ime,
					studentF->prezime,
					studentF->godina_rodenja);
			else
				printf("\nStudent nije pronadjen.\n");
			break;

		case '5':
			DeletePrez(&head);
			break;

		case 'k':
		case 'K':
			break;

		default:
			printf("\nPogresan izbor!\n");
			break;
		}
	}


	while (head.Next != NULL)
	{
		Position tmp = head.Next;
		head.Next = tmp->Next;
		free(tmp);
	}

	return 0;
}

void Insert(Position P)
{
	Position q;

	q = (Position)malloc(sizeof(struct _student));

	if (q == NULL)
	{
		printf("\nGreska pri alokaciji memorije.\n");
		return;
	}

	printf("Unesite ime, prezime i godinu rodjenja: ");

	scanf("%127s %127s %d",
		q->ime,
		q->prezime,
		&q->godina_rodenja);

	q->Next = P->Next;
	P->Next = q;
}


void PrintList(Position P)
{
	if (P == NULL)
	{
		printf("\nLista je prazna!\n");
		return;
	}

	printf("\nStudenti u listi:\n");

	while (P != NULL)
	{
		printf("%s %s %d\n",
			P->ime,
			P->prezime,
			P->godina_rodenja);

		P = P->Next;
	}
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

	printf("\nUnesite prezime koje trazite: ");
	scanf("%127s", prez);

	while (P != NULL &&
		_stricmp(P->prezime, prez) != 0)
	{
		P = P->Next;
	}

	return P;
}

void DeletePrez(Position P)
{
	Position tmp;
	char prez[128];

	printf("\nUnesite prezime koje zelite izbrisati: ");
	scanf("%127s", prez);

	while (P->Next != NULL &&
		_stricmp(P->Next->prezime, prez) != 0)
	{
		P = P->Next;
	}

	tmp = P->Next;

	if (tmp != NULL)
	{
		P->Next = tmp->Next;

		printf("\nIz liste se brise: %s %s %d\n",
			tmp->ime,
			tmp->prezime,
			tmp->godina_rodenja);

		free(tmp);
	}
	else
	{
		printf("\nStudent s trazenim prezimenom nije pronadjen.\n");
	}
}