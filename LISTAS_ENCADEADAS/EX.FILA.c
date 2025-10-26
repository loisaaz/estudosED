/******************************************************************************

SISTEMA DE ATENDIMENTO EM UMA FILAS

o O sistema deve ter um menu que permite as seguintes operações:
o Adicionar paciente: função inserir.
o Atender próximo paciente: função remover.
o Ao atender um paciente, seu ID e nome devem ser exibidos e removido da lista.

o Exibir fila: O programa deve imprimir a lista de pacientes na fila, na ordem de chegada.

o Procurar paciente(s) mais idoso(s): O programa deve procurar e imprimir o(s) paciente(s) mais idoso(s).

o Cuidado que podem haver mais de um paciente com idades iguais e maiores que os demais.

o Sair do programa: O usuário deve poder sair do programa quando desejar.


*******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
struct Paciente
{
    char nome[80];
    int idade;
    int id;
    struct Paciente* prox;
};
struct Fila
{
    struct Paciente *first; //para remoção
    struct Paciente *last; //inserção
};

// criar paciente
struct Paciente* criar(char nome[80], int idade, int id)
{
    struct Paciente* new = (struct Paciente*)malloc(sizeof(struct Paciente));
    strcpy(new->nome, nome);
    new->idade = idade;
    new->id = id;
    new->prox = NULL;
    
    return new;
}

//Adicionar paciente: função inserir.
struct Fila* inserir(struct Fila* fila, char nome[80], int idade, int id)
{
    struct Paciente* new = criar(nome, idade, id);
    if(fila->last == NULL)
    {
        fila->first = new;
        fila->last = new;
    }
    else
    {
        // o ultimo antigo agr aponta para o novo elemento adicionado no final da fila
        fila->last->prox = new;
        // ponteiro da fila é atualizado para apontar para o novo elemento
        fila->last = new;
    }
    return fila;
}

/*Atender próximo paciente: função remover.
remove do inicio
Ao atender um paciente, seu ID e nome devem ser exibidos e removido da lista.*/
struct Fila* remover(struct Fila* fila)
{
    if(fila->first == NULL)
    {
        printf("Fila de atendimento vazia!");
        return fila;
    }
    
    // ponteiro temporario para fazer a remoção
    struct Paciente* temp = fila->first;
    
    // 3. Exibe os dados do paciente que está sendo atendido
    printf("\n--- PACIENTE ATENDIDO ---\n");
    printf("ID: %d\n", temp->id);
    printf("Nome: %s\n", temp->nome);
    printf("Idade: %d\n", temp->idade);
    printf("-------------------------\n");
    
    fila->first = fila->first->prox;
    
    if(fila->first == NULL)
    {
        fila->last == NULL;
        //se no inicio n tem nada no final tbm nao terá
    }
    free(temp); // libera memoria do nó ATENDIDO
    
    return fila; // fila atualizado
}

// Exibir fila: O programa deve imprimir a lista de pacientes na fila, na ordem de chegada
void imprime(struct Fila* fila)
{
    if(fila->last == NULL)
    {
        printf("Fila de atendimento vazia!");
        return fila;
    }
    struct Paciente* p = fila->first;
    int pos = 0;
    while(p != NULL)
    {
        printf("\n--- FILA DE ATENDIMENTO ---\n");
        printf("POSIÇÃO: %d\n", pos);
        printf("ID: %d\n", p->id);
        printf("Nome: %s\n", p->nome);
        printf("Idade: %d\n", p->idade);
        printf("-------------------------\n"); 
        
        p = p->prox;
        pos++;
    }
    printf("NULL\n");
}
int main()
{
    int op;
    

    return 0;
}