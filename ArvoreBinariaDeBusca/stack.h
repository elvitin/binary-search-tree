struct stack
{
	struct no *item;
	struct stack *prox;
};
typedef struct stack pilha;

void init(pilha **p)
{
	*p = NULL;
}

char isEmpty(pilha *p)
{
	return p == NULL;
}

/* 
int Top(Pilha *P)
{
	if(!isEmpty(P))
		return P->info;
	return -1;
}
*/

void push(pilha **p, struct no *item)
{
	pilha *nova = (pilha *)malloc(sizeof(pilha));
	nova->item = item;
	nova->prox = *p;
	*p = nova;
}

void pop(pilha **p, struct no **item)
{
	pilha *aux;
	if (!isEmpty(*p))
	{
		aux = *p;
		*item = (*p)->item;
		*p = (*p)->prox;
		free(aux);
	}
	else
		*item = NULL;
}