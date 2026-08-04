// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

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

// 🛡️ Nível Aventureiro: Reserva de Peças com Pilha
//
// - Implemente uma pilha linear com capacidade para 3 peças.
// - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
// - Permita enviar uma peça da fila para a pilha (reserva).
// - Crie um menu com opção:
//      2 - Enviar peça da fila para a reserva (pilha)
//      3 - Usar peça da reserva (remover do topo da pilha)
// - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
// - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).


typedef struct {
    char tipo;
    int id;
} Peca;

typedef struct {
    Peca itens[TAM_PILHA];
    int topo;
} Pilha;

// eu fiz uma peca nova com tipo aleatorio e o id que chega por parametro
Peca gerarPeca(int id) {
    char tipos[4] = {'I', 'O', 'T', 'L'};
    Peca p;

    p.tipo = tipos[rand() % 4];
    p.id = id;

    return p;
}

// aqui a fila comeca com 5 pecas, como pede o nivel novato
void inicializarFila(Peca fila[], int *frente, int *tras, int *quantidade, int *proximoId) {
    int i;

    *frente = 0;
    *tras = -1;
    *quantidade = 0;
    *proximoId = 1;

    for (i = 0; i < TAM_FILA; i++) {
        *tras = (*tras + 1) % TAM_FILA;
        fila[*tras] = gerarPeca(*proximoId);
        *proximoId = *proximoId + 1;
        *quantidade = *quantidade + 1;
    }
}

// mostra as pecas na ordem certa, mesmo sendo uma fila circular
void mostrarFila(Peca fila[], int frente, int quantidade) {
    int i;
    int pos;

    printf("\nFila atual:\n");

    for (i = 0; i < quantidade; i++) {
        pos = (frente + i) % TAM_FILA;
        printf("[%d] Tipo: %c | Id: %d\n", i + 1, fila[pos].tipo, fila[pos].id);
    }
}

// pega a peca que esta na frente da fila
Peca removerDaFila(Peca fila[], int *frente, int *quantidade) {
    Peca p;

    p = fila[*frente];
    *frente = (*frente + 1) % TAM_FILA;
    *quantidade = *quantidade - 1;

    return p;
}

// coloca uma peca no final da fila
void inserirNaFila(Peca fila[], int *tras, int *quantidade, Peca peca) {
    *tras = (*tras + 1) % TAM_FILA;
    fila[*tras] = peca;
    *quantidade = *quantidade + 1;
}

// a pilha comeca vazia
void inicializarPilha(Pilha *pilha) {
    pilha->topo = -1;
}

// olha se a pilha ja chegou no limite
int pilhaCheia(Pilha *pilha) {
    if (pilha->topo == TAM_PILHA - 1) {
        return 1;
    }

    return 0;
}

// olha se a pilha esta vazia
int pilhaVazia(Pilha *pilha) {
    if (pilha->topo == -1) {
        return 1;
    }

    return 0;
}

// coloca uma peca no topo da pilha
void push(Pilha *pilha, Peca peca) {
    if (pilhaCheia(pilha) == 0) {
        pilha->topo = pilha->topo + 1;
        pilha->itens[pilha->topo] = peca;
    }
}

// tira uma peca do topo da pilha
Peca pop(Pilha *pilha) {
    Peca p;

    p.id = -1;
    p.tipo = '?';

    if (pilhaVazia(pilha) == 0) {
        p = pilha->itens[pilha->topo];
        pilha->topo = pilha->topo - 1;
    }

    return p;
}

// mostra a pilha de um jeito simples
void mostrarPilha(Pilha *pilha) {
    int i;

    printf("\nPilha de reserva:\n");

    if (pilhaVazia(pilha) == 1) {
        printf("[vazia]\n");
    } else {
        for (i = pilha->topo; i >= 0; i--) {
            printf("[%d] Tipo: %c | Id: %d\n", i + 1, pilha->itens[i].tipo, pilha->itens[i].id);
        }
    }
}

int main() {
    Peca fila[TAM_FILA];
    Pilha pilha;
    int frente;
    int tras;
    int quantidade;
    int proximoId;
    int opcao;
    Peca p;

    srand((unsigned)time(NULL));

    // eu começo com a fila cheia para já deixar tudo pronto
    inicializarFila(fila, &frente, &tras, &quantidade, &proximoId);
    inicializarPilha(&pilha);

    do {
        // eu mostro a fila antes do menu para ficar mais fácil ver o que mudou
        mostrarFila(fila, frente, quantidade);
        mostrarPilha(&pilha);

        printf("\nMenu\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            // quando joga, sai a primeira peca da fila
            p = removerDaFila(fila, &frente, &quantidade);
            printf("\nVocê jogou a peça %c com id %d.\n", p.tipo, p.id);

            // depois eu coloco outra no final para a fila continuar com 5
            inserirNaFila(fila, &tras, &quantidade, gerarPeca(proximoId));
            proximoId = proximoId + 1;

            printf("Nova peça foi colocada no final da fila.\n");
        } else if (opcao == 2) {
            if (pilhaCheia(&pilha) == 0) {
                p = removerDaFila(fila, &frente, &quantidade);
                printf("\nVocê reservou a peça %c com id %d.\n", p.tipo, p.id);

                inserirNaFila(fila, &tras, &quantidade, gerarPeca(proximoId));
                proximoId = proximoId + 1;

                push(&pilha, p);
                printf("A peça foi colocada na pilha de reserva.\n");
            } else {
                printf("\nA pilha esta cheia.\n");
            }
        } else if (opcao == 3) {
            if (pilhaVazia(&pilha) == 0) {
                p = pop(&pilha);
                printf("\nVocê usou a peça reservada %c com id %d.\n", p.tipo, p.id);
            } else {
                printf("\nA pilha esta vazia.\n");
            }
        } else if (opcao == 0) {
            printf("\nSaindo do jogo...\n");
        } else {
            printf("\nOpção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}


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

