#include "arquivo.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::string lerArquivo(const std::string &nomeArquivo) {
    std::ifstream arquivo(nomeArquivo.c_str());
    if (!arquivo) {
        std::cerr << "Erro ao abrir o arquivo: " << nomeArquivo << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << arquivo.rdbuf();
    arquivo.close();
    return buffer.str();
}

void salvarArquivo(const std::string &nomeArquivo, const std::string &conteudo) {
    std::ofstream arquivo(nomeArquivo.c_str());
    if (!arquivo) {
        std::cerr << "Erro ao criar o arquivo: " << nomeArquivo << std::endl;
        return;
    }
    arquivo << conteudo;
    arquivo.close();
}
