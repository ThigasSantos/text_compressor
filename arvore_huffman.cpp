#include "arvore_huffman.h"
#include <queue>
#include <vector>
#include <functional>

// Construtor do nó.
Node::Node(char c, int f, Node *l, Node *r)
    : ch(c), freq(f), left(l), right(r) {}

// Implementação do comparador.
bool Compare::operator()(Node *a, Node *b) {
    return a->freq > b->freq;
}

// Função auxiliar para gerar os códigos (sem lambdas).
static void gerarCodigo(Node *no, const std::string &codigo,
                        std::unordered_map<char, std::string> &codigosHuffman) {
    if (no == 0)
        return;
    if (no->ch != '\0') {
        codigosHuffman[no->ch] = codigo;
    }
    gerarCodigo(no->left, codigo + "0", codigosHuffman);
    gerarCodigo(no->right, codigo + "1", codigosHuffman);
}

void construirArvoreHuffman(const std::string &texto,
    std::unordered_map<char, std::string> &codigosHuffman, Node *&raiz) {

    std::unordered_map<char, int> frequencia;
    for (size_t i = 0; i < texto.size(); i++) {
        char ch = texto[i];
        frequencia[ch]++;
    }
    std::priority_queue<Node*, std::vector<Node*>, Compare> pq;
    for (std::unordered_map<char, int>::iterator it = frequencia.begin();
         it != frequencia.end(); ++it) {
        pq.push(new Node(it->first, it->second));
    }
    while (pq.size() > 1) {
        Node *esq = pq.top(); pq.pop();
        Node *dir = pq.top(); pq.pop();
        Node *novo = new Node('\0', esq->freq + dir->freq, esq, dir);
        pq.push(novo);
    }
    raiz = pq.top();
    gerarCodigo(raiz, "", codigosHuffman);
}

std::string compactarHuffman(const std::string &texto,
    const std::unordered_map<char, std::string> &codigosHuffman) {
    std::string resultado;
    for (size_t i = 0; i < texto.size(); i++) {
        char ch = texto[i];
        resultado += codigosHuffman.at(ch);
    }
    return resultado;
}

std::string descompactarHuffman(const std::string &textoCodificado, Node *raiz) {
    std::string resultado;
    Node *atual = raiz;
    for (size_t i = 0; i < textoCodificado.size(); i++) {
        char bit = textoCodificado[i];
        if (bit == '0')
            atual = atual->left;
        else
            atual = atual->right;
        if (atual->left == 0 && atual->right == 0) {
            resultado.push_back(atual->ch);
            atual = raiz;
        }
    }
    return resultado;
}

void liberarArvoreHuffman(Node *raiz) {
    if (raiz != 0) {
        liberarArvoreHuffman(raiz->left);
        liberarArvoreHuffman(raiz->right);
        delete raiz;
    }
}
