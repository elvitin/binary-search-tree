//No da lista
typedef struct node
{
	struct node *ant;
	struct tree *item;
	struct node *prox;

} Node;


//Descritor
typedef struct fila	
{
	struct node *front; //Comeco
	struct node *rear;  //Fim
	
} Fila;


bool isEmpty (Fila f)
{
	return f.front == NULL;
}

void init (Fila *f)
{
	f->front = f->rear = NULL;
}


void enQueue (Fila *f, struct tree *info)
{
	Node *novoNo = malloc(sizeof (Node));
	novoNo->item = info;
	novoNo->prox = NULL;

	if (isEmpty(*f)) // if (f->rear == NULL)
	{
		novoNo->ant = NULL;
		f->front = f->rear = novoNo;
	}
	else
	{
		novoNo->ant = f->rear;
		f->rear->prox = novoNo;
		f->rear = novoNo;
	}
}

void deQueue (Fila *f, struct tree **no)
{
	if (!isEmpty(*f))
	{
		*no = f->front->item;
		f->front = f->front->prox;
		
		if (f->front == NULL)
		{
			free(f->rear);
			f->rear = NULL;
		}
		else
		{
			free(f->front->ant);
			f->front->ant = NULL;
		}
	}
	else
		*no = NULL;
}


