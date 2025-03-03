#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <string>

std::string lerArquivo(const std::string &nomeArquivo);
void salvarArquivo(const std::string &nomeArquivo, const std::string &conteudo);

#endif
