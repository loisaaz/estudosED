#include <stdio.h>  
#include <stdlib.h> 

struct No {
    int dado;                    
    struct No* next; 
};

// função criar um nó
struct No* criar_no(int valor)
{
    struct No* new = malloc(sizeof(struct No));
    
    new->dado = valor;
    new->next = NULL;
    return new;
}

// função insere um elemento no começo da lista.
struct No* insere_inicio(struct No* lista, int valor)
{
    struct No* novo = criar_no(valor);
    novo->next = lista;
    return novo;
}

// função insere um elemento no final da lista.
struct No* insere_final(struct No* lista, int valor)
{
    struct No* novo = criar_no(valor);
    
    if (lista == NULL)
        return novo;
        
    struct No* inicio = lista;
    
    while(inicio->next != NULL)
    {
        inicio = inicio->next;
    }
    inicio->next = novo;
    return lista;
}
// Insere um elemento em uma posição específica (índice 'posicao').
struct No* insere_pos(struct No* lista, int v, int pos)
{
    if (lista == NULL || pos < 0)
        return insere_inicio(lista, v);
        
    struct No* aux = lista;
    int c = 0;
    
    while(aux->next != NULL && c < pos - 1)
    {
        aux = aux->next;
        c++;
    }
    
    struct No* novo = criar_no(v); 
    
    novo->next = aux->next;
    aux->next = novo;
    
    return lista;
}

// Remove o primeiro elemento da lista.
struct No* remove_inicio(struct No* lista)
{
    if (lista == NULL)
        return NULL;
    
    struct No* temp = lista;
    lista = lista->next;
    
    free(temp);
    return lista;
    
}

// Remove o último elemento da lista.
struct No* remove_final(struct No* lista)
{
    if (lista == NULL)
        return NULL;
        
    if (lista->next == NULL) {
        free(lista);
        return NULL;
    }
    
    struct No* p = lista;
    while(p->next->next != NULL)
    {
        p = p->next;
    }
    
    free(p->next);
    
    p->next = NULL;
    return lista;
}

// Remove um elemento de uma posição específica.
struct No* remover_pos(struct No* lista, int pos)
{
    // Se a lista for vazia ou a posição for inválida, não faz nada.
    if (lista == NULL || pos < 0)
        return lista;
        
    if(pos == 0)
    {
        return remove_inicio(lista);
    }
    
    struct No* aux = lista;
    int c = 0;
    while(aux->next != NULL && c < pos - 1)
    {
        aux = aux->next;
        c++;
    }
    
    if (aux->next == NULL)
        return lista;
        
    struct No* temp = aux->next;
    aux->next = temp->next;
    free(temp);
    
    return lista;
}    

// Busca um valor na lista.
struct No* buscar_valor(struct No* lista, int valor)
{
    // Se a lista for vazia ou a posição for inválida, não faz nada.
    if (lista == NULL)
        return lista;
    
    struct No* aux = lista;
    
    while(aux != NULL)
    {
        if(aux->dado == valor)
        {
            return aux;
        }
        aux = aux->next;
    }
    return NULL;
}

// Libera TODA a memória alocada para a lista.
struct No* liberamemory(struct No* lista)
{
    struct No* aux = lista;
    while(aux != NULL)
    {
        struct No* temp = aux;
        aux = aux->next;
        
        free(temp);
    }
    return NULL;
}
// Imprime todos os valores da lista no console.
void imprime(struct No* lista)
{
    struct No* aux = lista;
    printf("lista: ");
    
    while(aux != NULL)
    {
        printf("%d->", aux->dado);
        aux = aux->next;
    }
    printf("NULL\n");
}

int main(void)
{
    struct No* lista = NULL;
    lista = insere_inicio(lista, 30);
    lista = insere_inicio(lista, 20);
    lista = insere_inicio(lista, 10);

    lista = insere_final(lista, 40);

    imprime(lista); // implemente imprime usando lista->dado
    lista = insere_pos(lista, 107, 2);
    imprime(lista); // implemente imprime usando lista->dado
    
    lista = remove_inicio(lista);
    lista = remove_final(lista);
    imprime(lista); // implemente imprime usando lista->dado
    
    liberamemory(lista);
    return 0;
}