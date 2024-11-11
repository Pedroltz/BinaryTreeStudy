#include <iostream>
#include <algorithm>
#include <cstdlib>

using namespace std;

// Classe do nó
class No {
public:
    int dado;
    No* esquerda;
    No* direita;
    int altura;

    No(int val) {
        dado = val;
        esquerda = direita = nullptr;
        altura = 1;  // Altura inicial do nó
    }
};

// Função para obter a altura de um nó
int getAltura(No* no) {
    if (no == nullptr)
        return 0;
    return no->altura;
}

// Função para calcular o fator de balanceamento de um nó
int getBalance(No* no) {
    if (no == nullptr)
        return 0;
    return getAltura(no->esquerda) - getAltura(no->direita);
}

// Rotação à direita
No* rotacaoDireita(No* y) {
    No* x = y->esquerda;
    No* T2 = x->direita;

    // Realiza a rotação
    x->direita = y;
    y->esquerda = T2;

    // Atualiza as alturas
    y->altura = 1 + max(getAltura(y->esquerda), getAltura(y->direita));
    x->altura = 1 + max(getAltura(x->esquerda), getAltura(x->direita));

    // Retorna a nova raiz
    return x;
}

// Rotação à esquerda
No* rotacaoEsquerda(No* x) {
    No* y = x->direita;
    No* T2 = y->esquerda;

    // Realiza a rotação
    y->esquerda = x;
    x->direita = T2;

    // Atualiza as alturas
    x->altura = 1 + max(getAltura(x->esquerda), getAltura(x->direita));
    y->altura = 1 + max(getAltura(y->esquerda), getAltura(y->direita));

    // Retorna a nova raiz
    return y;
}

// Função para inserir um nó na árvore AVL
No* inserir(No* no, int dado) {
    // Realiza a inserção normal de uma BST
    if (no == nullptr)
        return new No(dado);
    if (dado < no->dado)
        no->esquerda = inserir(no->esquerda, dado);
    else if (dado > no->dado)
        no->direita = inserir(no->direita, dado);
    else  // Valores duplicados não são permitidos
        return no;

    // Atualiza a altura do ancestral
    no->altura = 1 + max(getAltura(no->esquerda), getAltura(no->direita));

    // Obtém o fator de balanceamento
    int balance = getBalance(no);

    // Realiza rotações se o nó estiver desbalanceado
    // Caso Esquerda Esquerda
    if (balance > 1 && dado < no->esquerda->dado)
        return rotacaoDireita(no);

    // Caso Direita Direita
    if (balance < -1 && dado > no->direita->dado)
        return rotacaoEsquerda(no);

    // Caso Esquerda Direita
    if (balance > 1 && dado > no->esquerda->dado) {
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }

    // Caso Direita Esquerda
    if (balance < -1 && dado < no->direita->dado) {
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }

    return no;
}

// Função para encontrar o nó com o menor valor
No* getMinValueNode(No* no) {
    No* atual = no;
    while (atual->esquerda != nullptr)
        atual = atual->esquerda;
    return atual;
}

// Função para remover um nó da árvore AVL
No* remover(No* raiz, int dado) {
    // Realiza a remoção normal de uma BST
    if (raiz == nullptr)
        return raiz;

    if (dado < raiz->dado)
        raiz->esquerda = remover(raiz->esquerda, dado);
    else if (dado > raiz->dado)
        raiz->direita = remover(raiz->direita, dado);
    else {
        // Nó com um ou nenhum filho
        if ((raiz->esquerda == nullptr) || (raiz->direita == nullptr)) {
            No* temp = raiz->esquerda ? raiz->esquerda : raiz->direita;

            // Caso nenhum filho
            if (temp == nullptr) {
                temp = raiz;
                raiz = nullptr;
            }
            else  // Um filho
                *raiz = *temp;  // Copia os conteúdos do filho não vazio
            delete temp;
        }
        else {
            // Nó com dois filhos: pega o sucessor em ordem (menor na subárvore direita)
            No* temp = getMinValueNode(raiz->direita);

            // Copia o valor do sucessor para este nó
            raiz->dado = temp->dado;

            // Remove o sucessor
            raiz->direita = remover(raiz->direita, temp->dado);
        }
    }

    // Se a árvore tinha apenas um nó
    if (raiz == nullptr)
        return raiz;

    // Atualiza a altura do nó atual
    raiz->altura = 1 + max(getAltura(raiz->esquerda), getAltura(raiz->direita));

    // Obtém o fator de balanceamento
    int balance = getBalance(raiz);

    // Realiza rotações se o nó estiver desbalanceado
    // Caso Esquerda Esquerda
    if (balance > 1 && getBalance(raiz->esquerda) >= 0)
        return rotacaoDireita(raiz);

    // Caso Esquerda Direita
    if (balance > 1 && getBalance(raiz->esquerda) < 0) {
        raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
        return rotacaoDireita(raiz);
    }

    // Caso Direita Direita
    if (balance < -1 && getBalance(raiz->direita) <= 0)
        return rotacaoEsquerda(raiz);

    // Caso Direita Esquerda
    if (balance < -1 && getBalance(raiz->direita) > 0) {
        raiz->direita = rotacaoDireita(raiz->direita);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

// Função para pesquisar um nó
No* pesquisar(No* no, int dado) {
    if (no == nullptr || no->dado == dado)
        return no;
    if (dado < no->dado)
        return pesquisar(no->esquerda, dado);
    else
        return pesquisar(no->direita, dado);
}

// Função para editar um nó
No* editar(No* raiz, int antigo_dado, int novo_dado) {
    raiz = remover(raiz, antigo_dado);
    raiz = inserir(raiz, novo_dado);
    return raiz;
}

// Funções de travessia
void emOrdem(No* raiz) {
    if (raiz != nullptr) {
        emOrdem(raiz->esquerda);
        cout << raiz->dado << " ";
        emOrdem(raiz->direita);
    }
}

void preOrdem(No* raiz) {
    if (raiz != nullptr) {
        cout << raiz->dado << " ";
        preOrdem(raiz->esquerda);
        preOrdem(raiz->direita);
    }
}

void posOrdem(No* raiz) {
    if (raiz != nullptr) {
        posOrdem(raiz->esquerda);
        posOrdem(raiz->direita);
        cout << raiz->dado << " ";
    }
}

// Função para exibir a árvore visualmente
void exibirArvore(No* raiz, string indent = "", bool ultimo = true) {
    if (raiz != nullptr) {
        cout << indent;
        if (ultimo) {
            cout << "R----";
            indent += "     ";
        }
        else {
            cout << "L----";
            indent += "|    ";
        }
        cout << raiz->dado << endl;
        exibirArvore(raiz->esquerda, indent, false);
        exibirArvore(raiz->direita, indent, true);
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

// Função para balancear a árvore (a árvore AVL já é balanceada automaticamente)
void balancearArvore(No* raiz) {
    cout << "A árvore AVL já está balanceada automaticamente." << endl;
}

// Função principal
int main() {
    No* raiz = nullptr;
    while (true) {
        limparConsole();
        cout << "Menu de Operações da Árvore AVL:" << endl;
        cout << "1. Criar árvore vazia" << endl;
        cout << "2. Inserir um elemento" << endl;
        cout << "3. Excluir um elemento" << endl;
        cout << "4. Exibir a árvore em pré-ordem" << endl;
        cout << "5. Exibir a árvore em pós-ordem" << endl;
        cout << "6. Exibir a árvore em ordem simétrica (em-ordem)" << endl;
        cout << "7. Visualizar a árvore" << endl;
        cout << "8. Buscar um elemento" << endl;
        cout << "9. Editar um elemento" << endl;
        cout << "10. Balancear a árvore" << endl;
        cout << "11. Sair" << endl;
        cout << "Digite a sua opção: ";
        int opcao;
        cin >> opcao;

        if (opcao == 1) {
            raiz = nullptr;
            cout << "Árvore AVL vazia criada." << endl;
        }
        else if (opcao == 2) {
            cout << "Digite o inteiro a ser inserido: ";
            int dado;
            cin >> dado;
            raiz = inserir(raiz, dado);
            cout << dado << " inserido na árvore." << endl;
        }
        else if (opcao == 3) {
            cout << "Digite o inteiro a ser removido: ";
            int dado;
            cin >> dado;
            raiz = remover(raiz, dado);
            cout << dado << " removido da árvore (se estava presente)." << endl;
        }
        else if (opcao == 4) {
            cout << "Elementos da árvore em pré-ordem: ";
            preOrdem(raiz);
            cout << endl;
        }
        else if (opcao == 5) {
            cout << "Elementos da árvore em pós-ordem: ";
            posOrdem(raiz);
            cout << endl;
        }
        else if (opcao == 6) {
            cout << "Elementos da árvore em ordem simétrica (em-ordem): ";
            emOrdem(raiz);
            cout << endl;
        }
        else if (opcao == 7) {
            if (raiz != nullptr)
                exibirArvore(raiz);
            else
                cout << "A árvore está vazia." << endl;
        }
        else if (opcao == 8) {
            cout << "Digite o inteiro a ser pesquisado: ";
            int dado;
            cin >> dado;
            if (pesquisar(raiz, dado) != nullptr)
                cout << dado << " encontrado na árvore." << endl;
            else
                cout << dado << " não encontrado na árvore." << endl;
        }
        else if (opcao == 9) {
            cout << "Digite o elemento a ser editado: ";
            int antigo_dado;
            cin >> antigo_dado;
            cout << "Digite o novo valor: ";
            int novo_dado;
            cin >> novo_dado;
            if (pesquisar(raiz, antigo_dado) != nullptr) {
                raiz = editar(raiz, antigo_dado, novo_dado);
                cout << "Elemento " << antigo_dado << " editado para " << novo_dado << "." << endl;
            }
            else {
                cout << "Elemento " << antigo_dado << " não encontrado na árvore." << endl;
            }
        }
        else if (opcao == 10) {
            balancearArvore(raiz);
        }
        else if (opcao == 11) {
            cout << "Saindo do programa." << endl;
            break;
        }
        else {
            cout << "Opção inválida! Por favor, escolha entre 1 e 11." << endl;
        }

        cout << "\nPressione Enter para continuar...";
        cin.ignore();
        cin.get();
    }
    return 0;
}
