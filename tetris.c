// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 5

int contador = 0;

typedef struct
{
    char tipo;
    int id;
} Peca;

typedef struct
{
    Peca pecas[MAX];
    int ini;
    int fim;
    int total;
} Fila;

// Função Buffer de entrada
void limparBufferEntrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

Peca gerarPeca()
{
    char tipos[] = {'I', 'O', 'T', 'L'};
    int i = rand() % 4;
    Peca sorteada;
    sorteada.tipo = tipos[i];
    sorteada.id = contador;
    contador++;
    return sorteada;
}

void inicializarFila(Fila *f)
{
    f->ini = 0;
    f->fim = 0;
    f->total = 0;
};

int filaCheia(Fila *f)
{
    return f->total == MAX;
}

int filaVazia(Fila *f)
{
    return f->total == 0;
}

void desenfileirar(Fila *f, Peca *p)
{
    if (filaVazia(f))
    {
        printf("Fila vazia. Impossível remover.\n");
        return;
    }

    *p = f->pecas[f->ini];
    f->ini = (f->ini + 1) % MAX;
    f->total--;
}

void enfileirar(Fila *f, Peca sorteada)
{
    if (filaCheia(f))
    {
        printf("Fila cheia. Não é possível inserir.\n");
        return;
    }

    f->pecas[f->fim] = sorteada; // Pegue a peça sorteada e guarde dentro do vetor

    f->fim = (f->fim + 1) % MAX; // Depois de inserir a peça, avance o marcador de fim da fila para a próxima posição

    f->total++; // Aumente em 1 a quantidade total de peças na fila
}

void mostrarFila(Fila *f)
{
    printf("--== Fila de Pecas ==--\n");

    int i, idx;

    idx = f->ini;

    for (i = 0; i < f->total; i++)
    {
        printf("[%c %d] ",
               f->pecas[idx].tipo,
               f->pecas[idx].id);

        idx = (idx + 1) % MAX;
    }

    printf("\n");
}

void exibirMenu()
{
    printf("--== Menu de Ações ==--\n");
    printf("1 - Jogar Peça\n");
    printf("2 - Inserir Nova Peça\n"); //por enquanto está função está sem uso porque apeça é gerada automaticamente após a remoção
    printf("0 - Sair de fininho\n");
}

//----------------------------------------
// ============ FUNÇÃO MAIN =============
//----------------------------------------

int main()
{
    Fila fila;
    Peca peca;

    srand(time(NULL));

    inicializarFila(&fila);

    for (int i = 0; i <= MAX - 1; i++)
    {
        enfileirar(&fila, gerarPeca());
    }

    int opcao;
    Peca pecas;

    // --== Laço Principal do menu ==--
    do
    {
        mostrarFila(&fila);
        exibirMenu();
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao)
        {
        case 1:
        {
            desenfileirar(&fila, &peca);
            enfileirar(&fila, gerarPeca()); //gera nova uma nova peça e insere automaticamente no fim da fila
            break;
        }
        case 2:
        {
            enfileirar(&fila, gerarPeca());
            break;
        }
        case 0:
            printf("\nSaindo do sistema...\n");
            break;

        default:
            printf("\nOpão inválida! Pressione Enter para tentar novamente.");
            getchar();
            break;
        }
    } while (opcao != 0);

    return 0;
}



    // 🧩 Nível Novato: Fila de Peças Futuras
    //
    // - Crie uma struct Peca com os campos: tipo (char) e id (int).
    // - Implemente uma fila circular com capacidade para 5 peças.
    // - Crie funções como inicializarFila(), enqueue(), dequeue(), filaCheia(), filaVazia().
    // - Cada peça deve ser gerada automaticamente com um tipo aleatório e id sequencial.
    // - Exiba a fila após cada ação com uma função mostrarFila().
    // - Use um menu com opções como:
    //      1 - Jogar peça (remover da frente)
    //      0 - Sair
    // - A cada remoção, insira uma nova peça ao final da fila.



    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).


    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha


