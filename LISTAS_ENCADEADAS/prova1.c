#include <stdlib.h>
#include <stdio.h>
/*
struct No{
    int valor;
    struct No *next;
};


void inseririnicio(struct No** lista, int valor)
{
    struct No* p = malloc(sizeof(struct No));
    p->valor = valor;
    p->next = *lista;
    *lista = p;
}*/

struct No
{
    int valor;
    struct No *next;
};
struct Fila
{
    struct No *first;
    struct No *last;
};

int remover(struct Fila *minhafila)
{
    if(minhafila == NULL || minhafila->first == NULL)
    {
        printf("A lista está vazia.");
        return 0;
    }
    struct No *temp = minhafila->first;
    //no saindo da lista
    minhafila->first = temp->next;
    //avança
    
    if(minhafila->first == NULL)
    {
        minhafila->last = NULL;
    }
    free(temp);
    
    return 1;
}

int main()
{


    return 0;
}