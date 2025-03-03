#include "menu.h"
#include <iostream>

int main() {
    int opcao;
    do {
        exibirMenu();
        std::cout << "Opcao: ";
        std::cin >> opcao;
        if (opcao == 1 || opcao == 2) {
            processarEscolha(opcao);
        } else if (opcao != 0) {
            std::cout << "Opcao invalida. Tente novamente.\n";
        }
    } while (opcao != 0);
    std::cout << "Programa encerrado.\n";
    return 0;
}
