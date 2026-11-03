#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>



typedef struct _Cvor* Position;

struct _Cvor
{
    int Koeficijent;
    int Exponent;
    Position Next;
};

void ReadPolynom(Position P);
void PrintPolynom(Position P);
void SumPolynom(Position P, Position Q, Position S);
void MulPolynom(Position P, Position Q, Position M);

int main(void)
{
    struct _Cvor P, Q, S, M;

    P.Next = NULL;
    Q.Next = NULL;
    S.Next = NULL;
    M.Next = NULL;

    ReadPolynom(&P);
    ReadPolynom(&Q);

    printf("\nP(x) = ");
    PrintPolynom(P.Next);

    printf("\nQ(x) = ");
    PrintPolynom(Q.Next);

    SumPolynom(P.Next, Q.Next, &S);

    printf("\nS(x) = P(x) + Q(x) = ");
    PrintPolynom(S.Next);

    MulPolynom(P.Next, Q.Next, &M);

    printf("\nM(x) = P(x) * Q(x) = ");
    PrintPolynom(M.Next);

    return 0;
}

void ReadPolynom(Position P)
{
    char ime_dat[1024];
    FILE* stream;
    Position q, i;

    printf("\nUnesite ime datoteke za citanje polinoma: ");
    scanf("%1023s", ime_dat);

    stream = fopen(ime_dat, "r");

    if (stream == NULL)
    {
        printf("\nGreska! Datoteka %s nije otvorena.", ime_dat);
        return;
    }

    while (1)
    {
        q = (Position)malloc(sizeof(struct _Cvor));

        if (q == NULL)
            break;

        if (fscanf(stream, "%d %d",
            &q->Koeficijent, &q->Exponent) != 2)
        {
            free(q);
            break;
        }

        if (q->Koeficijent == 0)
        {
            free(q);
            continue;
        }

        i = P;

        while (i->Next != NULL &&
            i->Next->Exponent > q->Exponent)
        {
            i = i->Next;
        }

        if (i->Next != NULL &&
            i->Next->Exponent == q->Exponent)
        {
            i->Next->Koeficijent += q->Koeficijent;
            free(q);

            if (i->Next->Koeficijent == 0)
            {
                q = i->Next;
                i->Next = q->Next;
                free(q);
            }
        }
        else
        {
            q->Next = i->Next;
            i->Next = q;
        }
    }

    fclose(stream);
}

void PrintPolynom(Position P)
{
    int prvi = 1;

    if (P == NULL)
    {
        printf("0\n");
        return;
    }

    while (P != NULL)
    {
        if (P->Koeficijent != 0)
        {
            if (prvi)
            {
                if (P->Koeficijent < 0)
                    printf("-");

                prvi = 0;
            }
            else
            {
                if (P->Koeficijent > 0)
                    printf(" + ");
                else
                    printf(" - ");
            }

            if (P->Exponent == 0)
            {
                printf("%d", abs(P->Koeficijent));
            }
            else
            {
                if (abs(P->Koeficijent) != 1)
                    printf("%d", abs(P->Koeficijent));

                printf("x");

                if (P->Exponent != 1)
                    printf("^%d", P->Exponent);
            }
        }

        P = P->Next;
    }

    if (prvi)
        printf("0");

    printf("\n");
}

void SumPolynom(Position P, Position Q, Position S)
{
    Position q;

    while (P != NULL || Q != NULL)
    {
        q = (Position)malloc(sizeof(struct _Cvor));

        if (q == NULL)
            return;

        if (P != NULL && (Q == NULL ||
            P->Exponent > Q->Exponent))
        {
            q->Exponent = P->Exponent;
            q->Koeficijent = P->Koeficijent;
            P = P->Next;
        }
        else if (Q != NULL && (P == NULL ||
            P->Exponent < Q->Exponent))
        {
            q->Exponent = Q->Exponent;
            q->Koeficijent = Q->Koeficijent;
            Q = Q->Next;
        }
        else
        {
            q->Exponent = P->Exponent;
            q->Koeficijent =
                P->Koeficijent + Q->Koeficijent;

            P = P->Next;
            Q = Q->Next;
        }

        if (q->Koeficijent == 0)
        {
            free(q);
            continue;
        }

        q->Next = NULL;
        S->Next = q;
        S = q;
    }
}

void MulPolynom(Position P, Position Q, Position M)
{
    Position q, i, j, tmp;

    i = P;

    while (i != NULL)
    {
        j = Q;

        while (j != NULL)
        {
            q = (Position)malloc(sizeof(struct _Cvor));

            if (q == NULL)
                return;

            q->Exponent = i->Exponent + j->Exponent;
            q->Koeficijent =
                i->Koeficijent * j->Koeficijent;

            tmp = M;

            while (tmp->Next != NULL &&
                tmp->Next->Exponent > q->Exponent)
            {
                tmp = tmp->Next;
            }

            if (tmp->Next != NULL &&
                tmp->Next->Exponent == q->Exponent)
            {
                tmp->Next->Koeficijent += q->Koeficijent;
                free(q);

                if (tmp->Next->Koeficijent == 0)
                {
                    q = tmp->Next;
                    tmp->Next = q->Next;
                    free(q);
                }
            }
            else if (q->Koeficijent != 0)
            {
                q->Next = tmp->Next;
                tmp->Next = q;
            }
            else
            {
                free(q);
            }

            j = j->Next;
        }

        i = i->Next;
    }
}
