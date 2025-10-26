#include <stdio.h> 
#include <stdlib.h> 

// Definição da estrutura do Nó (Node)
// Cada nó armazena um valor e um ponteiro para o próximo nó na fila.
struct Node
{
    int value; // Variável para armazenar o dado (valor inteiro) do nó.
    struct Node* next; // Ponteiro para o próximo struct Node na lista encadeada (ou NULL se for o último).
};

// Definição da estrutura da Fila (Queue)
struct Queue
{
    struct Node* first; // Ponteiro para o primeiro elemento (cabeça) da fila (onde a remoção ocorre - DEQUEUE).
    struct Node* last; // Ponteiro para o último elemento (cauda) da fila (onde a inserção ocorre - ENQUEUE).
};

// Função para criar um novo nó
struct Node* create_node(int value)
{
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    new_node->value = value; // Atribui o valor passado como argumento 
    new_node->next = NULL; // O novo nó é inserido no final, então seu ponteiro 'next' aponta inicialmente para NULL.

    return new_node; // Retorna o ponteiro para o nó criado.
}

// Função para Inserir (Enfileirar/Enqueue)
// Insere um novo nó no FIM da fila, seguindo o princípio FIFO.
// Recebe o ponteiro da fila e o valor a ser inserido. Retorna a fila atualizada.
struct Queue* insert_node(struct Queue* fila, int value)
{
    struct Node* new_node = create_node(value); // Cria um novo nó com o valor especificado.

    // Verifica se a fila está vazia (se o ponteiro 'last' é NULL).
    if (fila->last == NULL)
    {
        // Se a fila estava vazia, o novo nó é o primeiro e o último.
        fila->first = new_node; // O 'first' da fila aponta para o novo nó.
        fila->last = new_node; // O 'last' da fila também aponta para o novo nó.
    }
    else
    {
        // Se a fila não está vazia:

        //ANTES DA INSERÇÃO: [10] -> NULL

        // O ponteiro 'next' e 'last' é atualizado para apontar para o novo nó.
        fila->last->next = new_node;
        // O ponteiro 'last' da fila é atualizado para apontar para o novo nó (o novo final da fila).
        fila->last = new_node;

        //APÓS A INSERÇÃO: [10] -> [20] -> NULL
    }
    return fila; // Retorna o ponteiro para a fila atualizada.
}

// Função para Remover (Desenfileirar/Dequeue)
// Remove o nó do INÍCIO da fila, seguindo o princípio FIFO.
// Recebe o ponteiro da fila e retorna a fila após a remoção.
struct Queue* remove_node(struct Queue* q)
{
    // Verifica se a fila está vazia (se 'first' é NULL).
    if (q->first == NULL)
        return q; // Se estiver vazia, retorna a fila sem fazer nada.

    // Cria um ponteiro temporário para o nó que será removido (o primeiro).
    struct Node* temp = q->first;

    //[10] -> [20] -> NULL
    // O ponteiro 'first' da fila é movido para o próximo nó na lista.
    q->first = q->first->next;
    //-> [20] -> NULL

    // Verifica se a fila ficou vazia após a remoção.
    if (q->first == NULL)
    {
        // Se ficou vazia, o ponteiro 'last' também deve ser ajustado para NULL.
        q->last = NULL;
    }
    
    // Libera a memória alocada para o nó removido (evita vazamento de memória).
    free(temp);

    return q; // Retorna o ponteiro para a fila atualizada.
}

// Função para verificar se a fila está vazia.
// Retorna 1 (true) se a fila está vazia, e 0 (false) caso contrário.
int is_empty(struct Queue* q)
{
    // A fila está vazia se o ponteiro 'first' for NULL.
    return (q->first == NULL);
}

// Função para liberar toda a memória alocada para a fila.
// Percorre todos os nós e libera cada um, além de liberar a própria estrutura da Fila.
void free_queue(struct Queue* q)
{
    struct Node* current = q->first; // Começa pelo primeiro nó.
    
    // Percorre a lista encadeada nó por nó.
    while (current != NULL)
    {
        struct Node* temp = current; // Guarda o ponteiro para o nó atual antes de avançar.
        current = current->next; // Move o ponteiro 'current' para o próximo nó.
        free(temp); // Libera a memória do nó salvo em 'temp'.
    }
    
    // Libera a memória alocada para a estrutura Queue em si.
    free(q);
}

// Função para imprimir os elementos da fila.
// Percorre a lista do 'first' ao 'last' e imprime os valores.
void print_queue(struct Queue* q)
{
    struct Node* current = q->first; // Começa a percorrer pelo primeiro nó.
    printf("Queue: ");
    
    // Loop que continua enquanto houver um nó (o ponteiro 'current' não é NULL).
    while (current != NULL)
    {
        printf("%d -> ", current->value); // Imprime o valor do nó atual, seguido de " -> ".
        current = current->next; // Move para o próximo nó.
    }
    printf("NULL\n"); // Indica o fim da fila.
}

// Função principal (exemplo de uso)
int main()
{
    // Aloca memória dinamicamente para a estrutura Queue.
    struct Queue* q = (struct Queue*) malloc(sizeof(struct Queue));

    // Inicializa os ponteiros da fila para NULL (fila vazia).
    q->first = NULL;
    q->last = NULL;

    // --- ENQUEUE (Inserção) ---
    // Insere o valor 10 no final da fila.
    q = insert_node(q, 10);
    // Insere o valor 20 no final da fila.
    q = insert_node(q, 20);
    // Insere o valor 30 no final da fila.
    q = insert_node(q, 30);

    // Imprime a fila: 10 -> 20 -> 30 -> NULL
    print_queue(q);

    // --- DEQUEUE (Remoção) ---
    // Remove o primeiro elemento (10) da fila.
    q = remove_node(q);

    // Imprime a fila após a remoção: 20 -> 30 -> NULL
    print_queue(q);

    // Libera toda a memória alocada para a fila, evitando vazamentos.
    free_queue(q);

    return 0; // Indica que o programa foi executado com sucesso.
}