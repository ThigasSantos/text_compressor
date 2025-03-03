#include "menu.h"
#include "arquivo.h"
#include "arvore_huffman.h"
#include "lcs.h"
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

void exibirMenu() {
    std::cout << "Escolha uma opcao:\n";
    std::cout << "1 - Compactar arquivo\n";
    std::cout << "2 - Descompactar arquivo\n";
    std::cout << "0 - Sair\n";
}

void processarEscolha(int escolha) {
    std::string nomeEntrada, nomeSaida;
    if (escolha == 1) {
        std::cout << "Digite o nome do arquivo a ser compactado: ";
        std::cin >> nomeEntrada;
        std::cout << "Digite o nome do arquivo de saida: ";
        std::cin >> nomeSaida;
        
        // Leitura do arquivo original
        std::string texto = lerArquivo(nomeEntrada);
        
        // Aplica LCS: constrói o dicionário e altera o texto
        std::unordered_map<std::string, std::string> dicionario = construirDicionarioLCS(texto);
        std::string textoLCS = aplicarLCS(texto, dicionario);
        
        // Compressão Huffman
        Node *raiz = 0;
        std::unordered_map<char, std::string> codigosHuffman;
        construirArvoreHuffman(textoLCS, codigosHuffman, raiz);
        std::string textoHuffman = compactarHuffman(textoLCS, codigosHuffman);
        
        // Preparar a saída: primeiro os metadados do LCS, depois um marcador e, por fim, o texto compactado.
        std::ostringstream oss;
        oss << dicionario.size() << "\n";
        for (std::unordered_map<std::string, std::string>::iterator it = dicionario.begin();
             it != dicionario.end(); ++it) {
            // Formato: token e substring original separados por um espaço.
            // Se a substring original contiver espaços, considere usar outro delimitador.
            oss << it->first << " " << it->second << "\n";
        }
        oss << "###DATA###\n";
        oss << textoHuffman;
        
        salvarArquivo(nomeSaida, oss.str());
        liberarArvoreHuffman(raiz);
        
        std::cout << "Arquivo compactado com sucesso!\n";
    } else if (escolha == 2) {
        std::cout << "Digite o nome do arquivo a ser descompactado: ";
        std::cin >> nomeEntrada;
        std::cout << "Digite o nome do arquivo de saida: ";
        std::cin >> nomeSaida;
        
        // Lê o arquivo compactado com metadados
        std::string conteudo = lerArquivo(nomeEntrada);
        std::istringstream iss(conteudo);
        int numEntradas = 0;
        iss >> numEntradas;
        iss.ignore(); // ignora o caractere de nova linha
        
        // Lê o dicionário do arquivo
        std::unordered_map<std::string, std::string> dicionarioLido;
        for (int i = 0; i < numEntradas; i++) {
            std::string linha;
            std::getline(iss, linha);
            size_t pos = linha.find(' ');
            if (pos != std::string::npos) {
                std::string token = linha.substr(0, pos);
                std::string original = linha.substr(pos + 1);
                dicionarioLido[token] = original;
            }
        }
        // Lê o marcador de dados (descarta a linha com \"###DATA###\")
        std::string marcador;
        std::getline(iss, marcador);
        
        // O restante é o texto Huffman compactado.
        std::string textoHuffman((std::istreambuf_iterator<char>(iss)),
                                  std::istreambuf_iterator<char>());
        
        // Carrega o dicionário LCS global para reverter a compressão LCS.
        carregarDicionarioLCS(dicionarioLido);
        
        // Reconstrução da árvore de Huffman a partir do texto compactado.
        Node *raiz = 0;
        std::unordered_map<char, std::string> codigosHuffman;
        construirArvoreHuffman(textoHuffman, codigosHuffman, raiz);
        std::string textoLCS = descompactarHuffman(textoHuffman, raiz);
        std::string textoOriginal = reverterLCS(textoLCS);
        
        salvarArquivo(nomeSaida, textoOriginal);
        liberarArvoreHuffman(raiz);
        
        std::cout << "Arquivo descompactado com sucesso!\n";
    }
}
