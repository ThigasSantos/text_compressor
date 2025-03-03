#ifndef ARVORE_HUFFMAN_H
#define ARVORE_HUFFMAN_H

#include <string>
#include <unordered_map>

// Estrutura para o nó da árvore de Huffman.
struct Node {
    char ch;
    int freq;
    Node *left;
    Node *right;
    Node(char c, int f, Node *l = 0, Node *r = 0);
};

// Comparador para a fila de prioridade.
struct Compare {
    bool operator()(Node *a, Node *b);
};

// Constrói a árvore de Huffman e gera os códigos para cada caractere.
void construirArvoreHuffman(const std::string &texto,
    std::unordered_map<char, std::string> &codigosHuffman, Node *&raiz);

// Compacta o texto usando os códigos de Huffman.
std::string compactarHuffman(const std::string &texto,
    const std::unordered_map<char, std::string> &codigosHuffman);

// Descompacta o texto codificado usando a árvore de Huffman.
std::string descompactarHuffman(const std::string &textoCodificado, Node *raiz);

// Libera a memória alocada para a árvore de Huffman.
void liberarArvoreHuffman(Node *raiz);

#endif
