struct no
{
    struct no *esq;
    int info;
    struct no *dir;
};
typedef struct no tree;

struct no *novoNo (int info)
{
    tree *no = (tree *) malloc (sizeof (tree));
    no->esq = no->dir = NULL;
    no->info = info;
    return no;
}

void insereRecursivo(tree **no, int info)
{
    if (*no == NULL)
        *no = novoNo (info);
    else 
    {
        if (info < (*no)->info)
            insereRecursivo (&(*no)->esq, info);
        else
            insereRecursivo (&(*no)->dir, info);
    }
}

int nivel (tree *no, int info)
{
    if(no == NULL)
        return -1;
    else
    {
        int nivel = 1;

        while (no != NULL)
        {
            if(no->info == info)
                return nivel;
            
            no = info < no->info ? no->esq : no->dir;
            nivel++;
        }
        return -1;
    }
}

void encontraPai(tree *no, int *pai, int *flag, int info)
{
    if (no != NULL)
    {
        if (no->info == info || no->esq != NULL && no->esq->info == info || no->dir != NULL && no->dir->info == info)
        {
            *pai = no->info;
            *flag = 0;
        }
        else
        {
            encontraPai(no->esq, &*pai, &*flag, info);
            if (*flag)
                encontraPai(no->dir, &*pai, &*flag, info);
        }
    }
}

int retornaPai(tree *no, int info)
{
    int flag = 1;
    int pai = -1;
    encontraPai(no, &pai, &flag, info);
    return pai;
}

void preOrdemIterativo(tree *no)
{
    pilha *p;
    init(&p);
    tree *aux;

    push(&p, no);

    while (!isEmpty(p))
    {
        pop(&p, aux);
        printf("[%d]", aux->info);

        if (aux->dir != NULL)
            push(&p, &aux->dir);

        if (aux->esq != NULL)
            push(&p, &aux->esq);
    }
}


