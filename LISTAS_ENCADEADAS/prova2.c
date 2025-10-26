/* QUESTÃO 1 */

#include <stdlib.h>
#include <stdio.h>

struct No
{
    int valor;
    struct No *next;
};

void inserirFinal(struct No* Lista, int valor)
{
    struct No* novo = malloc(sizeof(struct No));
    novo->valor = valor;
    novo->next = NULL;
    
    if(Lista == NULL)
    {
        printf("A lista está vazia.");
        return;
    }
    
    struct No* aux = Lista;
    while(aux->next != NULL)
    {
        aux = aux->next;
    }
    aux->next = novo;
    
}

int main()
{


    return 0;
}