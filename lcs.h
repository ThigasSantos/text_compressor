#ifndef LCS_H
#define LCS_H

#include <string>
#include <unordered_map>


std::unordered_map<std::string, std::string> construirDicionarioLCS(std::string &texto);

std::string aplicarLCS(const std::string &texto, 
                       const std::unordered_map<std::string, std::string> &dicionario);

std::string reverterLCS(const std::string &texto);

void carregarDicionarioLCS(const std::unordered_map<std::string, std::string> &dicionario);

#endif
