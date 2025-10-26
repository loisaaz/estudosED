#include <stdio.h>
#include <stdlib.h>
/*
 Gestão de clientes
 o Você foi contratado para desenvolver um sistema de gerenciamento de clientes de uma loja.
 o O sistema deve gerenciar os seguintes dados de cada cliente:
 
 o-Nome (string).
 o-CPF (long).
 o-Contato de celular (long).
 
 o O programa deve ter um menu que oferece as seguintes funcionalidades:
 o Cadastrar cliente
 o Excluir cliente
 o Exibir clientes
 o Consultar clientes pelo CPF
 o Sair do programa
 o PARA ISSO, UTILIZE LISTAS ENCADEADAS
*/
struct cliente
{
    char nome[80];
    long int cpf;
    long int celular;
    struct cliente *prox;
};

//Cadastrar cliente
void cadastrar(struct cliente *c)
{
    struct cliente *p;
    p = (struct cliente *)malloc(sizeof(struct cliente));
    
    printf("NOME: ");
    scanf(" %[^\n]", p->nome);
    
    printf("CPF: ");
    scanf(" %ld", &p->cpf);
    
    printf("CELULAR: ");
    scanf(" %ld", &p->celular);
    
    p->prox = c->prox; //p vai apontar para onde c apontava
    c->prox = p; //c vai apontar para p
    printf("\tCliente %s cadastrado com sucesso!\n", p->nome);
}
//Excluir cliente
void exclusao(struct cliente *head, long int excluirpessoa)
{
    struct cliente *anterior = head;
    struct cliente *atual = head->prox;

    while (atual != NULL)
    {
        if (atual->cpf == excluirpessoa)
        {
            anterior->prox = atual->prox;
            free(atual);
            printf("Cliente com CPF %ld removido.\n", excluirpessoa);
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
    printf("Cliente com CPF %ld não encontrado.\n", excluirpessoa);
}
//Exibir clientes
void ver_clientes(struct cliente *head)
{
    struct cliente *p;
    printf("Clientes cadastrados: \n");
    for (p = head->prox; p != NULL; p = p->prox)
    {
        printf("Nome: %s, CPF: %ld, CELULAR: %ld", p->nome, p->cpf, p->celular);
    
    }
    printf("NULL\n");
}
//Consultar clientes pelo CPF
void Consultar_cliente(struct cliente *head, long int consultar)
{
    struct cliente *j;
    for(j = head->prox; j != NULL; j = j->prox)
    {
        if(j->cpf == consultar)
        {
            printf("INFORMAÇÕES DO CLIENTE:\n NOME: %s, CPF: %ld, CELULAR: %ld\n", j->nome, j->cpf, j->celular);
            return;
        }
    }
    printf("Cliente de CPF %ld não foi encontrado..", consultar);
}

int main()
{
    struct cliente *dados;
    dados = (struct cliente *)malloc(sizeof(struct cliente));
    dados->prox = NULL;
    
    int op = -1;
    while(op != 0)
    {
        printf("\tSISTEMA DE GERENCIAMENTO DE CLIENTES\n");
        printf("\t1 - CADASTRAR CLIENTE.\n");
        printf("\t2 - EXCLUIR CLIENTE.\n");
        printf("\t3 - EXIBIR CLIENTES.\n");
        printf("\t4 - CONSULTAR CLIENTES PELO CPF\n");
        printf("\t0 - SAIR DO PROGRAMA.\n");

        printf("\tOPÇÃO DESEJADA: ");
        scanf("%d", &op);
        switch (op)
        {

            case 0:
                printf("Finalizando execução...");
                break;
            case 1:
                cadastrar(dados);
                break;
            case 2:
                long int busca;
                printf("Digite o CPF do cliente a ser removido: ");
                scanf("%ld", &busca);
                exclusao(dados, busca);
                break;
            case 3:
                ver_clientes(dados);
                break;
            case 4:
                long int cliente;
                printf("Digite o CPF do cliente a ser removido: ");
                scanf("%ld", &cliente);
                Consultar_cliente(dados, cliente);
            default:
                printf("Opção inválida!");
        }
    }
    struct cliente *liberar = dados->prox;
    while (liberar != NULL) 
    {
        struct cliente *temp = liberar;
        liberar = liberar->prox;
        free(temp);
    }
    free(dados); // Libera o nó cabeça
    return 0;
}