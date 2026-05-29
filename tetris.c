// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 5
#define MAX_PILHA 3

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

typedef struct
{
    Peca pecas[MAX_PILHA];
    int topo;
} Pilha;

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

void inicializarPilha(Pilha *p)
{
    p->topo = -1;
}

int pilhaVazia(Pilha *p)
{
    return p->topo == -1;
}

int pilhaCheia(Pilha *p)
{
    return p->topo == MAX_PILHA - 1;
}

int filaCheia(Fila *f)
{
    return f->total == MAX;
}

int filaVazia(Fila *f)
{
    return f->total == 0;
}

void push(Pilha *p, Peca novaPeca) //FUNÇÃO EMPILHAR
{
    if (pilhaCheia(p))
    {
        printf("Pilha cheia.\n");
        return;
    }

    p->topo++;

    p->pecas[p->topo] = novaPeca;
}

void pop(Pilha *p, Peca *removida) //DESEMPILHAR
{
    if (pilhaVazia(p))
    {
        printf("Pilha vazia.\n");
        return;
    }

    *removida = p->pecas[p->topo];

    p->topo--;
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
void mostrarPilha(Pilha *p)
{
    printf("--== Pilha de Reserva ==--\n");

    if (pilhaVazia(p))
    {
        printf("Pilha vazia.\n");
        return;
    }

    for (int i = p->topo; i >= 0; i--)
    {
        printf("[%c %d] ",
               p->pecas[i].tipo,
               p->pecas[i].id);
    }

    printf("\n");
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

void exibirEstado(Fila *fila, Pilha *pilha)
{
    printf("\n=====================================\n");
    printf("         ESTADO ATUAL\n");
    printf("=====================================\n\n");

    printf("Fila de Pecas: ");

    int idx = fila->ini;

    for (int i = 0; i < fila->total; i++)
    {
        printf("[%c %d] ",
               fila->pecas[idx].tipo,
               fila->pecas[idx].id);

        idx = (idx + 1) % MAX;
    }

    printf("\n\n");

    printf("Pilha de Reserva (Topo -> Base): ");

    if (pilhaVazia(pilha))
    {
        printf("Vazia");
    }
    else
    {
        for (int i = pilha->topo; i >= 0; i--)
        {
            printf("[%c %d] ",
                   pilha->pecas[i].tipo,
                   pilha->pecas[i].id);
        }
    }

    printf("\n");
    printf("=====================================\n");
}

void exibirMenu()
{
    printf("--== Menu de Ações ==--\n");
    printf("1 - Jogar Peça da frente da fila\n");
    printf("2 - Enviar peça da fila para reserva(pilha)\n");
    printf("3 - usar peça da reserva(pilha)\n");
    printf("4 - Trocar peça da frente da fila com o topo da pilha\n");
    printf("5 - Trocar os 3 primeiros da fila com as 3 peças da pilha\n");
    printf("0 - Sair\n");
}

//----------------------------------------
// ============ FUNÇÃO MAIN =============
//----------------------------------------

int main()
{
    Fila fila;
    Pilha pilha;
    Peca peca;

    srand(time(NULL));

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    for (int i = 0; i <= MAX - 1; i++)
    {
        enfileirar(&fila, gerarPeca());
    }

    int opcao;
    Peca pecas;

    // --== Laço Principal do menu ==--
    do
    {
        exibirEstado(&fila, &pilha);
        exibirMenu();
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao)
        {
        case 1:
        {
            desenfileirar(&fila, &peca);
            enfileirar(&fila, gerarPeca());
            break;
        }
        case 2:
        {
            if (pilhaCheia(&pilha))
            {
                printf("Pilha cheia. Não é possível reservar mais peças.\n");
                break;
            }

            desenfileirar(&fila, &peca);

            push(&pilha, peca);

            enfileirar(&fila, gerarPeca());

            break;
        }
        case 3:
        {
            if (pilhaVazia(&pilha))
            {
                printf("Pilha vazia. Nenhuma peça reservada para usar.\n");
                break;
            }

            pop(&pilha, &peca);

            printf("Peça [%c %d] usada da reserva.\n",
                   peca.tipo,
                   peca.id);

            break;
        }

        case 4:
        {
            if (pilhaVazia(&pilha))
            {
                printf("Pilha vazia. Não há peça para trocar.\n");
                break;
            }

            Peca temp;

            temp = fila.pecas[fila.ini];

            fila.pecas[fila.ini] = pilha.pecas[pilha.topo];

            pilha.pecas[pilha.topo] = temp;

            printf("Troca realizada entre a frente da fila e o topo da pilha.\n");

            break;
        }

        case 5:
        {
            if (fila.total < 3)
            {
                printf("Fila não possui 3 peças.\n");
                break;
            }

            if (pilha.topo < 2)
            {
                printf("Pilha não possui 3 peças.\n");
                break;
            }

            Peca tempFila[3];

            int pos0 = fila.ini;
            int pos1 = (fila.ini + 1) % MAX;
            int pos2 = (fila.ini + 2) % MAX;

            tempFila[0] = fila.pecas[pos0];
            tempFila[1] = fila.pecas[pos1];
            tempFila[2] = fila.pecas[pos2];

            fila.pecas[pos0] = pilha.pecas[pilha.topo];
            fila.pecas[pos1] = pilha.pecas[pilha.topo - 1];
            fila.pecas[pos2] = pilha.pecas[pilha.topo - 2];

            pilha.pecas[pilha.topo]     = tempFila[0];
            pilha.pecas[pilha.topo - 1] = tempFila[1];
            pilha.pecas[pilha.topo - 2] = tempFila[2];

            printf("Troca realizada entre os 3 primeiros da fila e os 3 da pilha.\n");

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


