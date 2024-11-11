import random
import matplotlib.pyplot as plt

# Classe do nó
class No:
    def __init__(self, dado):
        self.dado = dado
        self.esquerda = None
        self.direita = None
        self.altura = 1  # Altura do nó para balanceamento AVL

# Função para obter a altura de um nó
def get_altura(no):
    if no is None:
        return 0
    return no.altura

# Função para calcular o fator de balanceamento de um nó
def get_balance(no):
    if no is None:
        return 0
    return get_altura(no.esquerda) - get_altura(no.direita)

# Rotação à direita
def rotacao_direita(y):
    x = y.esquerda
    T2 = x.direita

    # Realiza a rotação
    x.direita = y
    y.esquerda = T2

    # Atualiza as alturas
    y.altura = 1 + max(get_altura(y.esquerda), get_altura(y.direita))
    x.altura = 1 + max(get_altura(x.esquerda), get_altura(x.direita))

    # Retorna a nova raiz
    return x

# Rotação à esquerda
def rotacao_esquerda(x):
    y = x.direita
    T2 = y.esquerda

    # Realiza a rotação
    y.esquerda = x
    x.direita = T2

    # Atualiza as alturas
    x.altura = 1 + max(get_altura(x.esquerda), get_altura(x.direita))
    y.altura = 1 + max(get_altura(y.esquerda), get_altura(y.direita))

    # Retorna a nova raiz
    return y

# Função para inserir um nó na árvore AVL
def inserir(no, dado):
    # Realiza a inserção normal de uma BST
    if no is None:
        return No(dado)
    elif dado < no.dado:
        no.esquerda = inserir(no.esquerda, dado)
    elif dado > no.dado:
        no.direita = inserir(no.direita, dado)
    else:
        return no  # Valores duplicados não são permitidos

    # Atualiza a altura do ancestral
    no.altura = 1 + max(get_altura(no.esquerda), get_altura(no.direita))

    # Obtém o fator de balanceamento
    balance = get_balance(no)

    # Realiza rotações se o nó estiver desbalanceado
    # Caso Esquerda Esquerda
    if balance > 1 and dado < no.esquerda.dado:
        return rotacao_direita(no)

    # Caso Direita Direita
    if balance < -1 and dado > no.direita.dado:
        return rotacao_esquerda(no)

    # Caso Esquerda Direita
    if balance > 1 and dado > no.esquerda.dado:
        no.esquerda = rotacao_esquerda(no.esquerda)
        return rotacao_direita(no)

    # Caso Direita Esquerda
    if balance < -1 and dado < no.direita.dado:
        no.direita = rotacao_direita(no.direita)
        return rotacao_esquerda(no)

    return no

# Função para encontrar o nó com o menor valor
def get_min_value_node(no):
    atual = no
    while atual.esquerda is not None:
        atual = atual.esquerda
    return atual

# Função para remover um nó da árvore AVL
def remover(no, dado):
    # Realiza a remoção normal de uma BST
    if no is None:
        return no

    if dado < no.dado:
        no.esquerda = remover(no.esquerda, dado)
    elif dado > no.dado:
        no.direita = remover(no.direita, dado)
    else:
        if no.esquerda is None:
            temp = no.direita
            no = None
            return temp
        elif no.direita is None:
            temp = no.esquerda
            no = None
            return temp

        temp = get_min_value_node(no.direita)
        no.dado = temp.dado
        no.direita = remover(no.direita, temp.dado)

    if no is None:
        return no

    # Atualiza a altura do nó atual
    no.altura = 1 + max(get_altura(no.esquerda), get_altura(no.direita))

    # Obtém o fator de balanceamento
    balance = get_balance(no)

    # Realiza rotações se o nó estiver desbalanceado
    # Caso Esquerda Esquerda
    if balance > 1 and get_balance(no.esquerda) >= 0:
        return rotacao_direita(no)

    # Caso Esquerda Direita
    if balance > 1 and get_balance(no.esquerda) < 0:
        no.esquerda = rotacao_esquerda(no.esquerda)
        return rotacao_direita(no)

    # Caso Direita Direita
    if balance < -1 and get_balance(no.direita) <= 0:
        return rotacao_esquerda(no)

    # Caso Direita Esquerda
    if balance < -1 and get_balance(no.direita) > 0:
        no.direita = rotacao_direita(no.direita)
        return rotacao_esquerda(no)

    return no

# Função para pesquisar um nó
def pesquisar(no, dado):
    if no is None or no.dado == dado:
        return no
    if dado < no.dado:
        return pesquisar(no.esquerda, dado)
    else:
        return pesquisar(no.direita, dado)

# Função para editar um nó
def editar(no, antigo_dado, novo_dado):
    no = remover(no, antigo_dado)
    no = inserir(no, novo_dado)
    return no

# Funções de travessia
def em_ordem(raiz):
    if raiz is not None:
        em_ordem(raiz.esquerda)
        print(raiz.dado, end=" ")
        em_ordem(raiz.direita)

def pre_ordem(raiz):
    if raiz is not None:
        print(raiz.dado, end=" ")
        pre_ordem(raiz.esquerda)
        pre_ordem(raiz.direita)

def pos_ordem(raiz):
    if raiz is not None:
        pos_ordem(raiz.esquerda)
        pos_ordem(raiz.direita)
        print(raiz.dado, end=" ")

# Função para exibir a árvore visualmente
def exibir_arvore(raiz):
    def plotar_no(no, x, y, dx):
        if no is not None:
            plt.text(x, y, str(no.dado), ha="center", va="center",
                     bbox=dict(facecolor="skyblue", edgecolor="black"))
            if no.esquerda is not None:
                plt.plot([x, x - dx], [y, y - 1], color="black")
                plotar_no(no.esquerda, x - dx, y - 1, dx / 2)
            if no.direita is not None:
                plt.plot([x, x + dx], [y, y - 1], color="black")
                plotar_no(no.direita, x + dx, y - 1, dx / 2)

    plt.figure(figsize=(12, 8))
    plotar_no(raiz, 0, 0, 4)
    plt.axis("off")
    plt.show()

# Função para limpar o console (Finge que não existe)
def limpar_console():
    import os
    os.system('cls' if os.name == 'nt' else 'clear')

# Função para balancear a árvore (já é balanceada automaticamente)
def balancear_arvore(raiz):
    # Em uma árvore AVL, a árvore é balanceada durante as inserções e remoções
    print("A árvore AVL está balanceada.")

# Função para inserir de 8 a 15 números aleatórios na árvore
def inserir_numeros_aleatorios(raiz):
    quantidade = random.randint(8, 15)  # Define a quantidade de números aleatórios entre 8 e 15
    numeros = random.sample(range(1, 100), quantidade)  # Gera números únicos entre 1 e 100

    print("Números aleatórios a serem inseridos na árvore:", numeros)
    for numero in numeros:
        raiz = inserir(raiz, numero)  # Insere cada número na árvore

    return raiz

# Função principal
def main():
    raiz = None
    while True:
        limpar_console()
        print("Menu de Operações da Árvore AVL:")
        print("1. Criar árvore vazia")
        print("2. Inserir um elemento")
        print("3. Excluir um elemento")
        print("4. Exibir a árvore em pré-ordem")
        print("5. Exibir a árvore em pós-ordem")
        print("6. Exibir a árvore em ordem simétrica (em-ordem)")
        print("7. Visualizar a árvore")
        print("8. Buscar um elemento")
        print("9. Editar um elemento")
        print("10. Balancear a árvore")
        print("11. Inserir números aleatórios na árvore")
        print("12. Sair")
        opcao = int(input("Digite a sua opção: "))

        if opcao == 1:
            raiz = None
            print("Árvore AVL vazia criada.")
        elif opcao == 2:
            dado = int(input("Digite o inteiro a ser inserido: "))
            raiz = inserir(raiz, dado)
            print(f"{dado} inserido na árvore.")
        elif opcao == 3:
            dado = int(input("Digite o inteiro a ser removido: "))
            raiz = remover(raiz, dado)
            print(f"{dado} removido da árvore (se estava presente).")
        elif opcao == 4:
            print("Elementos da árvore em pré-ordem: ", end="")
            pre_ordem(raiz)
            print()
        elif opcao == 5:
            print("Elementos da árvore em pós-ordem: ", end="")
            pos_ordem(raiz)
            print()
        elif opcao == 6:
            print("Elementos da árvore em ordem simétrica (em-ordem): ", end="")
            em_ordem(raiz)
            print()
        elif opcao == 7:
            if raiz is not None:
                exibir_arvore(raiz)
            else:
                print("A árvore está vazia.")
        elif opcao == 8:
            dado = int(input("Digite o inteiro a ser pesquisado: "))
            if pesquisar(raiz, dado) is not None:
                print(f"{dado} encontrado na árvore.")
            else:
                print(f"{dado} não encontrado na árvore.")
        elif opcao == 9:
            antigo_dado = int(input("Digite o elemento a ser editado: "))
            novo_dado = int(input("Digite o novo valor: "))
            if pesquisar(raiz, antigo_dado) is not None:
                raiz = editar(raiz, antigo_dado, novo_dado)
                print(f"Elemento {antigo_dado} editado para {novo_dado}.")
            else:
                print(f"Elemento {antigo_dado} não encontrado na árvore.")
        elif opcao == 10:
            balancear_arvore(raiz)
        elif opcao == 11:
            raiz = inserir_numeros_aleatorios(raiz)
            print("Números aleatórios inseridos na árvore.")
        elif opcao == 12:
            print("Saindo do programa.")
            break
        else:
            print("Opção inválida! Por favor, escolha entre 1 e 12.")

        input("\nPressione Enter para continuar...")

if __name__ == "__main__":
    main()
