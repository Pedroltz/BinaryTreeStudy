#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó da árvore
struct No {
    int dado;
    struct No *esquerda;
    struct No *direita;
};

// Função para criar um novo nó
struct No* novoNo(int dado) {
    struct No *no = (struct No*)malloc(sizeof(struct No));
    no->dado = dado;
    no->esquerda = no->direita = NULL;
    return no;
}

// Função para inserir um novo nó na árvore
struct No* inserir(struct No* no, int dado) {
    if (no == NULL) {
        return novoNo(dado);
    }
    if (dado < no->dado) {
        no->esquerda = inserir(no->esquerda, dado);
    } else if (dado > no->dado) {
        no->direita = inserir(no->direita, dado);
    }
    return no;
}

// Função para pesquisar um elemento na árvore
struct No* pesquisar(struct No* no, int dado) {
    if (no == NULL || no->dado == dado) {
        return no;
    }
    if (dado < no->dado) {
        return pesquisar(no->esquerda, dado);
    } else {
        return pesquisar(no->direita, dado);
    }
}

// Função para exibir a árvore em ordem
void emOrdem(struct No* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esquerda);
        printf("%d ", raiz->dado);
        emOrdem(raiz->direita);
    }
}

// Função para limpar o console
void limparConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Função principal
int main() {
    struct No *raiz = NULL;
    int opcao, dado;
    do {
        limparConsole(); // Limpa o console

        printf("Menu de Operacoes da Arvore Binaria de Busca:\n");
        printf("1. Inserir um elemento\n");
        printf("2. Pesquisar um elemento\n");
        printf("3. Exibir a arvore em ordem\n");
        printf("4. Sair\n");
        printf("Digite a sua opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o inteiro a ser inserido: ");
                scanf("%d", &dado);
                raiz = inserir(raiz, dado);
                printf("%d inserido na árvore.\n", dado);
                break;
            case 2:
                printf("Digite o inteiro a ser pesquisado: ");
                scanf("%d", &dado);
                if (pesquisar(raiz, dado) != NULL) {
                    printf("%d encontrado na árvore.\n", dado);
                } else {
                    printf("%d não encontrado na árvore.\n", dado);
                }
                break;
            case 3:
                printf("Elementos da árvore em ordem: ");
                emOrdem(raiz);
                printf("\n");
                break;
            case 4:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opção inválida! Por favor, escolha entre 1 e 4.\n");
                break;
        }
        printf("\nPressione Enter para continuar...");
        getchar(); // Consumir o '\n' deixado pelo scanf
        getchar(); // Espera pelo Enter
    } while (opcao != 4);

    return 0;
}
