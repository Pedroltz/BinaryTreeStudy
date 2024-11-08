# Árvore Binária de Busca em Python

## Descrição do Projeto

Este projeto implementa uma Árvore Binária de Busca (BST) em Python. O programa permite ao usuário realizar operações básicas, como inserir elementos, pesquisar elementos e exibir os elementos em ordem. O objetivo principal do código é fornecer uma interface simples para interagir com uma árvore binária de busca, utilizando um menu baseado em texto para executar as operações.

## O que são Árvores Binárias de Busca?

Uma Árvore Binária de Busca (BST) é uma estrutura de dados em que cada nó possui no máximo dois filhos: um filho à esquerda e um filho à direita. A BST possui uma propriedade importante: para cada nó, todos os valores dos nós da subárvore à esquerda são menores que o valor do nó, e todos os valores dos nós da subárvore à direita são maiores. Isso permite que as operações de busca, inserção e remoção sejam feitas de maneira eficiente.

## Características das Árvores Binárias de Busca

- **Inserção**: Inserir um elemento na BST envolve encontrar a posição correta na árvore onde o novo valor deve ser colocado, de acordo com a ordem dos elementos.
- **Busca**: A busca em uma BST é eficiente porque aproveita a ordenação dos elementos, reduzindo a quantidade de nós a serem visitados em cada etapa.
- **Exibição em Ordem**: A exibição em ordem (in-order traversal) percorre a árvore visitando primeiro a subárvore esquerda, depois o nó atual e, por fim, a subárvore direita, resultando em uma lista de valores ordenados.

## Benefícios das Árvores Binárias de Busca

- **Eficiência**: As operações de busca, inserção e remoção têm, em média, complexidade de tempo O(log n) quando a árvore está balanceada, o que faz da BST uma estrutura de dados eficiente para muitas aplicações.
- **Ordenação Natural**: A BST permite armazenar dados de forma ordenada, facilitando a recuperação dos elementos em ordem crescente ou decrescente.

## Estrutura do Código

- **Classe `No`**: Representa cada nó da árvore, contendo um valor (dado) e referências para os filhos esquerdo e direito.
- **Função `inserir`**: Insere um novo valor na árvore, respeitando a propriedade de ordem da BST.
- **Função `pesquisar`**: Busca um valor na árvore e retorna o nó correspondente se encontrado, ou `None` se o valor não estiver presente.
- **Função `em_ordem`**: Exibe os elementos da árvore em ordem crescente.
- **Função `limpar_console`**: Limpa o console para tornar a interface mais amigável durante a execução do menu.
- **Função `main`**: Gerencia o menu principal, permitindo ao usuário interagir com a árvore binária de busca.
