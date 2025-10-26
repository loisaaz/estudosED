#include <stdio.h>  
#include <stdlib.h> 

// O 'struct' (estrutura) é um tipo de dado que permite agrupar diferentes variáveis sob um único nome.
// Aqui, estamos definindo um "molde" para os elementos (nós) da nossa lista.
// Cada elemento precisa de duas informações:
// 1. O dado que ele armazena (um inteiro).
// 2. Um ponteiro para o próximo elemento da lista. É essa ligação que "encadeia" os elementos.
struct ElementoLista {
    int dado;                    // Variável para armazenar o valor inteiro do elemento.
    struct ElementoLista* proximo; // Ponteiro para outro elemento do mesmo tipo (struct ElementoLista).
                                 // É esse ponteiro que conecta um elemento ao seguinte, formando a lista.
};

// Esta função tem a responsabilidade única de criar um novo nó (elemento) da lista.
// Ela retorna um ponteiro para o elemento recém-criado.
// O tipo de retorno é 'struct ElementoLista*' porque a função devolve o endereço de memória do novo elemento.
struct ElementoLista* criar_elemento(int valor)
{
    // Declara um ponteiro chamado 'novo'. Este ponteiro irá guardar o endereço de memória do elemento que vamos criar.
    struct ElementoLista* novo; 
    // informando ao compilador que este ponteiro apontará para nossa estrutura.
    novo = (struct ElementoLista*) malloc(sizeof(struct ElementoLista));
    
    // Aqui, estamos atribuindo o 'valor' recebido como parâmetro para o campo 'dado' do nosso novo elemento.
    novo->dado = valor;
    
    // Por padrão, um novo elemento ainda não está conectado a ninguém.
    // Portanto, seu ponteiro 'proximo' deve apontar para NULL, indicando o fim da lista (ou que ele é o único elemento).
    novo->proximo = NULL;
    
    // A função retorna o ponteiro 'novo', que contém o endereço do bloco de memória alocado e inicializado.
    // Quem chamou esta função agora tem acesso ao novo elemento.
    return novo;
}

// Esta função insere um elemento no começo da lista.
// Ela precisa de dois parâmetros: o ponteiro para o início da lista atual ('inicio') e o valor a ser inserido.
// Ela retorna o novo início da lista. É crucial que ela retorne este valor, porque o início da lista MUDA após a inserção.
struct ElementoLista* inserir_no_inicio(struct ElementoLista *inicio, int valor)
{
    // Primeiro, criamos o novo elemento que será inserido.
    struct ElementoLista* novo = criar_elemento(valor);
    
    // A lógica da inserção no início é:
    // O ponteiro do nosso novo elemento deve apontar para o que era o 'inicio' da lista antiga.
    // Ex: Se a lista era [10] -> NULL, e estamos inserindo 20, o 'proximo' do 20 apontará para o 10.
    
    novo->proximo = inicio;
    //[20] -> [10] -> NULL
    // Agora, o novo elemento se tornou o primeiro da lista.
    // A função retorna o ponteiro para este novo elemento, que é o novo 'inicio' da lista.
    // O programa principal (main) deve atualizar sua variável 'lista' com este novo endereço. Ex: lista = inserir_no_inicio(lista, 20);
    return novo;
}

// Esta função insere um elemento no final da lista.
// Ela precisa percorrer a lista até encontrar o último elemento para fazer a conexão.
// Ela retorna o ponteiro para o início da lista. Geralmente, ele não muda (a menos que a lista estivesse vazia).
struct ElementoLista* inserir_no_final(struct ElementoLista* inicio, int valor)
{
    // Cria o novo elemento a ser inserido.
    struct ElementoLista* novo = criar_elemento(valor);
     
    // Caso especial: se a lista está vazia ('inicio' é NULL), o novo elemento é, ao mesmo tempo, o início e o fim da lista.
    if (inicio == NULL)
        return novo; // Retornamos o novo elemento como o novo início da lista.

    // Para percorrer a lista sem perder a referência do início, criamos um ponteiro auxiliar, chamado 'ponteiro_auxiliar'.
    // 'ponteiro_auxiliar' começa apontando para o mesmo local que 'inicio'.
    struct ElementoLista* ponteiro_auxiliar = inicio;
    
    // Este loop 'while' percorre a lista.
    // A condição 'ponteiro_auxiliar->proximo != NULL' significa: "enquanto o próximo do elemento atual não for o fim da lista".
    // Quando o loop terminar, 'ponteiro_auxiliar' estará apontando para o ÚLTIMO elemento da lista.
    while (ponteiro_auxiliar->proximo != NULL)
        ponteiro_auxiliar = ponteiro_auxiliar->proximo; // 'ponteiro_auxiliar' avança para o próximo elemento.

    // Agora que 'ponteiro_auxiliar' aponta para o último elemento, fazemos o ponteiro 'proximo' dele apontar para o 'novo' elemento.
    // Isso efetivamente "engata" o novo elemento no final da lista.
    ponteiro_auxiliar->proximo = novo;
    
    // Retornamos o ponteiro para o início da lista. Ele não mudou neste caso, mas é uma boa prática manter a consistência da função.
    return inicio;
}

// Insere um elemento em uma posição específica (índice 'posicao').
// A contagem de posições começa em 0 (primeiro elemento é posição 0).
struct ElementoLista* inserir_na_posicao(struct ElementoLista* inicio, int valor, int posicao) {
    // Se a posição for 0 ou menor, ou se a lista estiver vazia, a inserção é feita no início.
    // Esta é uma forma de tratar casos de borda e simplificar a lógica.
    if (posicao <= 0 || inicio == NULL)
        return inserir_no_inicio(inicio, valor);
    
    // Ponteiro auxiliar para percorrer a lista.
    struct ElementoLista* atual = inicio;
    int contador = 0;

    // Este loop percorre a lista até encontrar o elemento ANTERIOR à posição de inserção.
    // A condição 'contador != posicao - 1' faz com que paremos no nó que virá ANTES do nosso novo nó.
    // A condição 'atual->proximo != NULL' previne que o programa quebre se a posição for maior que o tamanho da lista.
    // Nesse caso, a inserção ocorrerá no final.
    while (atual->proximo != NULL && contador < posicao - 1)
    {
        atual = atual->proximo;
        contador++;
    }

    // Cria o novo elemento.
    struct ElementoLista* novo = criar_elemento(valor);
    
    // A lógica de inserção no meio é:
    // 1. O 'proximo' do novo elemento deve apontar para o mesmo lugar que o 'proximo' do elemento 'atual'.
    novo->proximo = atual->proximo;
    
    // 2. O 'proximo' do elemento 'atual' agora deve apontar para o novo elemento.
    atual->proximo = novo;
    
    // Retorna o início da lista (que não mudou).
    return inicio;
}

// Remove o primeiro elemento da lista.
// Retorna o ponteiro para o novo início da lista.
struct ElementoLista* remover_do_inicio(struct ElementoLista* inicio)
{
    // Se a lista estiver vazia, não há nada a remover. Retorna NULL.
    if (inicio == NULL)
        return NULL;
    
    // Para não perder a referência do elemento a ser removido (e liberar sua memória),
    // criamos um ponteiro temporário que aponta para o início atual.
    struct ElementoLista* temporario = inicio;
    
    // O 'inicio' da lista é atualizado para apontar para o segundo elemento.
    inicio = inicio->proximo;
    
    // 'free()' libera a memória que foi alocada com 'malloc'.
    // Isso é crucial para evitar vazamento de memória (memory leak).
    free(temporario);
    
    // Retorna o novo início da lista.
    return inicio;
}

// Remove o último elemento da lista.
struct ElementoLista* remover_do_final(struct ElementoLista* inicio)
{
    // Se a lista estiver vazia, não há o que remover.
    if (inicio == NULL) 
        return NULL;

    // Caso especial: se a lista só tem um elemento.
    // Removemos esse elemento e a lista se torna vazia (NULL).
    if (inicio->proximo == NULL) 
    {
        free(inicio);
        return NULL;
    }

    // Precisamos encontrar o PENÚLTIMO elemento para poder desconectar o último.
    // Criamos um ponteiro auxiliar para percorrer a lista.
    struct ElementoLista* atual = inicio;

    // A condição 'atual->proximo->proximo != NULL' significa: "enquanto o próximo do próximo não for NULL".
    // Quando este loop terminar, 'atual' estará apontando para o PENÚLTIMO elemento.
    while (atual->proximo->proximo != NULL)
        atual = atual->proximo;

    // 'atual->proximo' é o último elemento. Liberamos a memória dele.
    free(atual->proximo);
    
    // O penúltimo elemento agora se torna o último.
    // Seu ponteiro 'proximo' deve ser atualizado para NULL.
    atual->proximo = NULL;
    
    // Retorna o início da lista, que não mudou.
    return inicio;
}

// Remove um elemento de uma posição específica.
struct ElementoLista* remover_na_posicao(struct ElementoLista* inicio, int posicao)
{
    // Se a lista for vazia ou a posição for inválida, não faz nada.
    if (inicio == NULL || posicao < 0)
        return inicio;
        
    // Se a posição for 0, é o mesmo que remover do início. Reutilizamos a função já criada.
    if (posicao == 0)
        return remover_do_inicio(inicio);
    
    // Ponteiro auxiliar para percorrer a lista até o elemento ANTERIOR ao que será removido.
    struct ElementoLista* atual = inicio;
    int contador = 0;
    while (atual->proximo != NULL && contador < posicao - 1)
    {
        atual = atual->proximo;
        contador++;
    }

    // Se 'atual->proximo' for NULL, significa que a posição informada está fora dos limites da lista.
    // Neste caso, por simplicidade, o código poderia simplesmente remover o último, como está fazendo aqui, ou não fazer nada.
    // O ideal seria um tratamento de erro mais explícito.
    if (atual->proximo == NULL)
        return inicio; // Retornamos o início sem modificações se a posição não for encontrada.
    
    // 'temporario' aponta para o elemento que queremos remover.  
    struct ElementoLista* temporario = atual->proximo;
    
    // O ponteiro 'proximo' do elemento 'atual' (que é o anterior ao removido)
    // passa a apontar para o elemento DEPOIS do removido.
    // Isso efetivamente "pula" o elemento a ser removido da lista.
    atual->proximo = temporario->proximo;
    
    // Libera a memória do elemento removido.
    free(temporario);
    
    return inicio;
}

// Busca um valor na lista.
// Retorna um ponteiro para o PRIMEIRO elemento encontrado com o valor, ou NULL se não encontrar.
struct ElementoLista* buscar_valor(struct ElementoLista* inicio, int valor)
{
    // Ponteiro auxiliar para percorrer a lista.
    struct ElementoLista* atual = inicio;
    
    // Loop que percorre toda a lista, do início ao fim.
    while (atual != NULL)
    {
        // Se o 'dado' do elemento atual for igual ao 'valor' procurado...
        if (atual->dado == valor)
            return atual; // ...retorna o ponteiro para este elemento.
        
        // Se não for, avança para o próximo.
        atual = atual->proximo;
    }
    
    // Se o loop terminar sem encontrar o valor, significa que ele não está na lista. Retorna NULL.
    return NULL;
}

// Libera TODA a memória alocada para a lista.
// É uma função muito importante para evitar vazamentos de memória ao final do programa.
// Não retorna nada (void), pois seu propósito é apenas limpar a memória.
void liberar_lista(struct ElementoLista* inicio)
{
    struct ElementoLista* atual = inicio;
    
    // Loop que continua enquanto ainda houver elementos na lista.
    while (atual != NULL)
    {
        // Guarda o ponteiro para o elemento atual em 'temporario'.
        struct ElementoLista* temporario = atual;
        // Avança o ponteiro 'atual' para o próximo elemento.
        atual = atual->proximo;
        // Libera a memória do elemento que ficou para trás (apontado por 'temporario').
        free(temporario);
    }
}

// Imprime todos os valores da lista no console.
void imprimir_lista(struct ElementoLista* inicio)
{
    struct ElementoLista* atual = inicio;
    printf("Lista: ");
    
    // Loop que percorre todos os elementos.
    while (atual != NULL)
    {
        // Imprime o valor do dado do elemento atual.
        printf("%d -> ", atual->dado);
        // Avança para o próximo elemento.
        atual = atual->proximo;
    }
    // Ao final, imprime "NULL" para indicar o fim da lista.
    printf("NULL\n");
}

// A função 'main' é o ponto de entrada do programa.
// É aqui que testamos todas as funções que criamos.
int main()
{
    // É crucial inicializar o ponteiro da lista como NULL.
    // Isso indica que, no início, a lista está vazia.
    struct ElementoLista* lista = NULL;

    // --- Teste de Inserções ---
    // A cada inserção, o valor retornado pela função atualiza a variável 'lista'.
    // Isso é especialmente importante para 'inserir_no_inicio', que muda o ponteiro inicial.
    lista = inserir_no_inicio(lista, 30);      // Lista se torna: 30 -> NULL
    lista = inserir_no_inicio(lista, 20);      // Lista se torna: 20 -> 30 -> NULL
    lista = inserir_no_inicio(lista, 10);      // Lista se torna: 10 -> 20 -> 30 -> NULL
    lista = inserir_no_final(lista, 40);       // Lista se torna: 10 -> 20 -> 30 -> 40 -> NULL
    lista = inserir_na_posicao(lista, 25, 2);  // Insere 25 na posição 2 (após o 20). Lista: 10 -> 20 -> 25 -> 30 -> 40 -> NULL

    printf("Após inserções:\n");
    imprimir_lista(lista); // Mostra o estado da lista.

    // --- Teste de Remoções ---
    lista = remover_do_inicio(lista);        // Remove o 10. Lista: 20 -> 25 -> 30 -> 40 -> NULL
    lista = remover_do_final(lista);         // Remove o 40. Lista: 20 -> 25 -> 30 -> NULL
    lista = remover_na_posicao(lista, 1);      // Remove o elemento na posição 1 (o 25). Lista: 20 -> 30 -> NULL

    printf("\nApós remoções:\n");
    imprimir_lista(lista); // Mostra o estado da lista.

    // --- Teste de Busca ---
    struct ElementoLista* encontrado = buscar_valor(lista, 30);
    // Verifica se o ponteiro retornado é diferente de NULL.
    if (encontrado != NULL)
        printf("\nValor 30 encontrado na lista.\n");
    else
        printf("\nValor 30 não está na lista.\n");

    // --- Liberação de Memória ---
    // Ao final do programa, chama a função para limpar todos os nós da lista da memória.
    liberar_lista(lista);
    // Após essa chamada, a variável 'lista' aponta para um endereço que não é mais válido,
    // seria uma boa prática atribuir NULL a ela, embora o programa termine em seguida.
    // lista = NULL;

    // Retorna 0 para indicar que o programa foi executado com sucesso.
    return 0;0
}