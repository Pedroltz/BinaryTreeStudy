class No:
    def __init__(self, dado):
        self.dado = dado
        self.esquerda = None
        self.direita = None

# Função para inserir um novo nó na árvore
def inserir(no, dado):
    if no is None:
        return No(dado)
    if dado < no.dado:
        no.esquerda = inserir(no.esquerda, dado)
    elif dado > no.dado:
        no.direita = inserir(no.direita, dado)
    return no

# Função para pesquisar um elemento na árvore
def pesquisar(no, dado):
    if no is None or no.dado == dado:
        return no
    if dado < no.dado:
        return pesquisar(no.esquerda, dado)
    else:
        return pesquisar(no.direita, dado)

# Função para exibir a árvore em ordem
def em_ordem(raiz):
    if raiz is not None:
        em_ordem(raiz.esquerda)
        print(raiz.dado, end=" ")
        em_ordem(raiz.direita)

# Função para limpar o console
def limpar_console():
    import os
    os.system('cls' if os.name == 'nt' else 'clear')

# Função principal
def main():
    raiz = None
    while True:
        limpar_console()  # Limpa o console
        print("Menu de Operacoes da Arvore Binaria de Busca:")
        print("1. Inserir um elemento")
        print("2. Pesquisar um elemento")
        print("3. Exibir a arvore em ordem")
        print("4. Sair")
        opcao = int(input("Digite a sua opcao: "))

        if opcao == 1:
            dado = int(input("Digite o inteiro a ser inserido: "))
            raiz = inserir(raiz, dado)
            print(f"{dado} inserido na árvore.")
        elif opcao == 2:
            dado = int(input("Digite o inteiro a ser pesquisado: "))
            if pesquisar(raiz, dado) is not None:
                print(f"{dado} encontrado na árvore.")
            else:
                print(f"{dado} não encontrado na árvore.")
        elif opcao == 3:
            print("Elementos da árvore em ordem: ", end="")
            em_ordem(raiz)
            print()
        elif opcao == 4:
            print("Saindo do programa.")
            break
        else:
            print("Opção inválida! Por favor, escolha entre 1 e 4.")

        input("\nPressione Enter para continuar...")

if __name__ == "__main__":
    main()
    input("Pressione Enter para sair...")
