#include "lcs.h"
#include <sstream>

// Variável global para armazenar o dicionário LCS.
static std::unordered_map<std::string, std::string> g_dicionarioLCS;

// Função auxiliar: conta ocorrências não sobrepostas de 'padrao' em 'texto'.
static int contarOcorrencias(const std::string &texto, const std::string &padrao) {
    int count = 0;
    size_t pos = 0;
    while ((pos = texto.find(padrao, pos)) != std::string::npos) {
        count++;
        pos += padrao.size();
    }
    return count;
}

std::unordered_map<std::string, std::string> construirDicionarioLCS(std::string &texto) {
    g_dicionarioLCS.clear();
    int tokenIndex = 1;
    bool encontrou = true;
    const int maxLen = 10; // tamanho máximo considerado para padrão
    const int minLen = 4;  // tamanho mínimo para considerar compressão

    while (encontrou) {
        encontrou = false;
        std::string melhorSubstring = "";
        // Procura pela maior substring repetida
        for (int len = maxLen; len >= minLen; len--) {
            for (size_t i = 0; i <= texto.size() - len; i++) {
                std::string sub = texto.substr(i, len);
                int ocorrencias = contarOcorrencias(texto, sub);
                if (ocorrencias >= 2 && sub.size() > melhorSubstring.size()) {
                    melhorSubstring = sub;
                }
            }
            if (!melhorSubstring.empty()) {
                break; // encontrou uma substring para esse tamanho
            }
        }
        if (!melhorSubstring.empty()) {
            std::string token = "@" + std::to_string(tokenIndex++);
            g_dicionarioLCS[token] = melhorSubstring;
            // Substitui todas as ocorrências (não sobrepostas) da substring por token
            size_t pos = 0;
            while ((pos = texto.find(melhorSubstring, pos)) != std::string::npos) {
                texto.replace(pos, melhorSubstring.size(), token);
                pos += token.size();
            }
            encontrou = true;
        }
    }
    return g_dicionarioLCS;
}

std::string aplicarLCS(const std::string &texto, 
                       const std::unordered_map<std::string, std::string> &dicionario) {
    // Neste exemplo, a função construirDicionarioLCS já alterou o texto.
    return texto;
}

std::string reverterLCS(const std::string &texto) {
    std::string resultado = texto;
    // Para cada token no dicionário, substituí-lo pela substring original.
    for (std::unordered_map<std::string, std::string>::iterator it = g_dicionarioLCS.begin();
         it != g_dicionarioLCS.end(); ++it) {
        size_t pos = 0;
        while ((pos = resultado.find(it->first, pos)) != std::string::npos) {
            resultado.replace(pos, it->first.size(), it->second);
            pos += it->second.size();
        }
    }
    return resultado;
}

void carregarDicionarioLCS(const std::unordered_map<std::string, std::string> &dicionario) {
    g_dicionarioLCS = dicionario;
}
