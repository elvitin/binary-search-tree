#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//#define COUNT 10

typedef struct tree
{
	int info;
	struct tree *esq;
	struct tree *dir;
} Tree;

#include "fila_abb.h"

void gotoxy(int x, int y)
{
	printf("%c[%d;%df", 0x1B, y, x);
}

void exibe(Tree *raiz, int x, int y, int dist)
{
	system("clear");
	if (raiz != NULL)
	{
		gotoxy(x, y);
		printf("%d ", raiz->info);

		if (raiz->esq != NULL)
		{
			gotoxy(x - dist / 2, y + 1);
			printf("/");
		}
		if (raiz->dir != NULL)
		{
			gotoxy(x + dist / 2, y + 1);
			printf("\\");
		}

		exibe(raiz->esq, x - dist, y + 2, dist / 2);
		exibe(raiz->dir, x + dist, y + 2, dist / 2);
	}
}

Tree *novoNo(int info)
{
	Tree *no = (Tree *)malloc(sizeof(Tree));
	no->esq = no->dir = NULL;
	no->info = info;
	return no;
}

void insere(struct tree **no, int info)
{
	if (*no == NULL)
		*no = novoNo(info);
	else
	{
		if (info < (*no)->info)
			insere(&(*no)->esq, info);
		else
			insere(&(*no)->dir, info);
	}
}

void buscaRecursiva(struct tree *raiz, int info, struct tree **aux)
{
	if (raiz != NULL)
	{
		if (info == raiz->info)
			*aux = raiz;
		else if (info < raiz->info)
			buscaRecursiva(raiz->esq, info, &*aux);
		else
			buscaRecursiva(raiz->esq, info, &*aux);
	}
	else
		*aux = NULL;
}

////////////////////////////////////////// BUSCA ITERATIVA
void busca(struct tree *raiz, int info, Tree **e, Tree **pai)
{
	*pai = raiz;
	while (raiz != NULL && info != raiz->info)
	{
		*pai = raiz;
		if (info < raiz->info)
			raiz = raiz->esq;
		else
			raiz = raiz->dir;
	}
	*e = raiz;
}

//exclusao(&*raiz, e, pai, 'e');
void exclusao(Tree **raiz, Tree *e, Tree *pai, char lado)
{
	if (e->esq == NULL && e->dir == NULL) //e->esq == e->dir
	{
		if (e != pai)
		{
			if (e->info < pai->info)
				pai->esq = NULL;
			else
				pai->dir = NULL;
		}
		else
			*raiz = NULL;
		free(e);
	}
	else if (e->esq == NULL || e->dir == NULL)
	{
		if (e != pai)
		{
			if (e->info < pai->info)
			{
				if (e->esq != NULL)
					pai->esq = e->esq;
				else
					pai->esq = e->dir;
			}
			else
			{
				if (e->esq != NULL)
					pai->dir = e->esq;
				else
					pai->dir = e->dir;
			}
		}
		else
		{
			if (e->esq != NULL)
				*raiz = e->esq;
			else
				*raiz = e->dir;
		}
		free(e);
	}
	else
	{
		int auxValor;
		Tree *sub;
		Tree *subPai;

		if (lado == 'e')
		{
			sub = e->esq;
			subPai = e;

			while (sub->dir != NULL)
			{
				subPai = sub;
				sub = sub->dir;
			}
		}
		else
		{
			sub = e->dir;
			subPai = e;

			while (sub->esq != NULL)
			{
				subPai = sub;
				sub = sub->esq;
			}
		}

		auxValor = sub->info;
		exclusao(&*raiz, sub, subPai, lado);
		e->info = auxValor;
	}
}

//quantNo(no->dir, &qdir)
void quantNo(Tree *no, int *qtde)
{
	if (no != NULL)
	{
		(*qtde)++;
		quantNo(no->esq, qtde);
		quantNo(no->dir, qtde);
	}
}

void balanceamento(struct tree **raiz)
{
	struct tree *no;
	struct tree *e;
	struct tree *pai;

	int aux;
	int qdir;
	int qesq;
	int fb;

	Fila f;

	init(&f);

	enQueue(&f, *raiz);

	while (!isEmpty(f))
	{
		deQueue(&f, &no);

		do
		{
			qdir = qesq = 0;
			quantNo(no->dir, &qdir);
			quantNo(no->esq, &qesq);

			fb = qdir - qesq;

			if (abs(fb) > 1)
			{
				aux = no->info;
				busca(*raiz, aux, &e, &pai);

				if (no->esq == NULL)
					no = no->dir;
				else if (no->dir == NULL)
					no = no->esq;

				if (fb > 0)
					exclusao(&*raiz, e, pai, 'd');
				else
					exclusao(&*raiz, e, pai, 'e');

				insere(&*raiz, aux);
			}
		} while (abs(fb) > 1);

		if (no->esq != NULL)
			enQueue(&f, no->esq);

		if (no->dir != NULL)
			enQueue(&f, no->dir);
	}
}

int main()
{
	Tree *abb = NULL;

	insere(&abb, 80);
	insere(&abb, 200);
	insere(&abb, 70);
	insere(&abb, 180);
	insere(&abb, 60);
	insere(&abb, 130);
	insere(&abb, 110);
	insere(&abb, 10);
	insere(&abb, 170);
	insere(&abb, 30);
	insere(&abb, 100);
	insere(&abb, 190);
	insere(&abb, 50);
	insere(&abb, 140);
	insere(&abb, 90);
	insere(&abb, 160);
	insere(&abb, 120);
	insere(&abb, 150);

	exibe(abb, 80, 1, 35);
	getc(stdin);

	balanceamento(&abb);

	exibe(abb, 80, 1, 20);
	putchar('\n');
	//system("clear");

	return 0;
}
