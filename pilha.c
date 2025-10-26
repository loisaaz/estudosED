#include <stdio.h>
#include <stdlib.h>

// Definindo a estrutura Node
struct Node {
    int value;
    struct Node* next;
};

// Definindo a estrutura Stack
struct Stack {
    struct Node* top;
};

// Criar novo nó
struct Node* create_node(int value) //criando estrutura para criar um nó com o parametro valor
{
    struct Node* new_node = malloc(sizeof(struct Node)); // aloca (reserva) memória para o novo nó
    new_node->value = value; //atribuindo valor para o campo
    new_node->next = NULL; // aponta para nulo
    return new_node; // retorna o nó criado
}

// Push
struct Stack* push(struct Stack* s, int value) // PUSH ->  insere um novo elemento no topo da pilha.  
{
    struct Node* new_node = create_node(value); //chama a função para criar o nó
    new_node->next = s->top; //novo nó aponta para onde a o topo da lista aponta
    s->top = new_node; //topo da lista aponta para o nó
    return s; // retorna a nova lista
}

// Pop
struct Stack* pop(struct Stack* s) // POP ->  remove e retorna o elemento do topo da pilha.  
{
    if (s->top == NULL) return s; // verifica se o topo da lista é nulo, se for não há nada para remover e é retornado essa lista
    struct Node* temp = s->top; // criação de nó temporario que aponta para o mesmo local que o topo da lista
    s->top = s->top->next; // topo da lista aponta para onde o ponteiro do 1º elemento apontava
    free(temp); //libera a memoria da veriavel temporaria que apontava para o primeiro elemento
    return s; // retorna a nova lista
}

// Liberar memória da pilha
void free_stack(struct Stack* s) 
{
    struct Node* aux = s->top; // criação de ponteiro aux que aponta para o inicio da lista
    while (aux != NULL) // enquanto para onde aux apontar não for nulo, o loop continua
    {
        struct Node* temp = aux; // criação de ponteiro temporario que tem o valor de aux
        aux = aux->next; // incrementa para o proximo nó apontado
        free(temp); //libera a variável tempporaria
    }
    free(s); // Libera a memória alocada para a estrutura Stack em si.
}

// Imprimir pilha
void print_stack(struct Stack* s) //função que imprime a lista
{
    struct Node* atual = s->top; //  criação de ponteiro aux que aponta para o inicio da lista
    printf("Stack (top -> bottom): ");
    while (atual != NULL) // enquanto para onde aux apontar não for nulo, o loop continua
    {
        printf("%d -> ", atual->value); //imprime os valores da lista
        atual = atual->next; // incrementa para o proximo nó apontado
    }
    printf("NULL\n");
}

// Exemplo de uso
int main() {
    
    struct Stack* s = (struct Stack*) malloc(sizeof(struct Stack)); //aloca memoria para a pilha
    s->top = NULL; //inicializa o ponteiro da pilha apontado para NULL

    s = push(s, 10);
    s = push(s, 20);
    s = push(s, 30);

    print_stack(s);

    s = pop(s);
    print_stack(s);
    
    s = push(s, 90);
    print_stack(s);
    
    free_stack(s);

    return 0;
}
