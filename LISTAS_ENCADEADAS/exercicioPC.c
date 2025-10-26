#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

struct cliente {
    char nome[100];
    long int cpf;
    long int celular;
    struct cliente *prox;
};

void cadastro(struct cliente *c)
{
    struct cliente *p = malloc(sizeof(struct cliente));

    printf("\tNOME: ");
    scanf(" %[^\n]", p->nome);
    printf("\tCPF: ");
    scanf(" %ld", &p->cpf);
    printf("\tCELULAR: ");
    scanf(" %ld", &p->celular);

    p->prox = c->prox; // p vai apontar para onde c apontava
    c->prox = p; // c vai apontar para p
    printf("\tCliente cadastrado com sucesso!\n");
}
// Excluir cliente
void exclusao(struct cliente *inicio, long int ex)
{
    struct cliente *p;
    for (p = inicio; p->prox != NULL; p = p->prox)
    {
        if(p->prox->cpf == ex) //verifica se o próximo é o cliente a ser removido
        {
            struct cliente *remover = p->prox; 
            //o cliente que será removido é aquele logo após p.
            /*p é o nó anterior ao que você quer excluir.
            'remover' agora aponta para o cliente que será eliminado da lista.*/
            p->prox = remover->prox; 
            // faz que p passe a apontar para o próximo cliente, apos o cliente removido, para onde ele apontava
            free(remover);
            printf("Cliente com CPF %ld removido.\n", ex);
            return;
        }
    }
    printf("CPF %ld não encontrado.\n", ex);
}

void exibe(struct cliente *inicio)
{
    struct cliente *i;

    printf("\nCLIENTES CADASTRADOS: ");
    for (i = inicio->prox; i!= NULL; i = i->prox)
    {
        printf("%s, %ld, %ld.\n", i->nome, i->cpf, i->celular);
    }
    printf("NULL\n");
}
void consulta(struct cliente *c, long int busca_cpf)
{
    struct cliente *i;
    for (i = c->prox; i!= NULL; i = i->prox)
    {
        if(i->cpf == busca_cpf)
        {
            printf("\nINFORMAÇÕES DO CLIENTE:\n %s, %ld %ld", i->nome, i->cpf, i->celular);
            return;
        }
    }
    printf("CPF %ld não encontrado.\n", busca_cpf);
}

int main()
{
    struct cliente *dados;
    dados = (struct cliente*)malloc(sizeof(struct cliente));
    dados->prox = NULL;

    int op = -1;
    while (op != 0)
    {
        printf("\tSISTEMA DE GERENCIAMENTO.\n");
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
                cadastro(dados);
                break;
            case 2: 
                long int ex;
                printf("Digite o CPF do cliente a ser removido: ");
                scanf("%ld", &ex);

                exclusao(dados, ex);
                break;
            case 3:
                exibe(dados);
                break;
            case 4:
                long int busca_cpf;
                printf("Digite o CPF do cliente: ");
                scanf("%ld", &busca_cpf);

                consulta(dados, busca_cpf);
                break;
            default:
                printf("\n\nOPCAO INVALIDA!\n");
        }
    }
    
    // Liberar a memória da lista antes de sair
    struct cliente *atual = dados->prox;
    while (atual != NULL) {
        struct cliente *temp = atual;
        atual = atual->prox;
        free(temp);
    }
    free(dados); // Libera o nó cabeça
    return 0;
}