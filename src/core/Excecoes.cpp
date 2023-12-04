#include "../include/core/Excecoes.hpp"

#include <iostream>

void handleExcecao(const std::exception& e) {
    
    /// Mensagem de erro a ser exibida em caso de excecao gerada
    std::cerr << "Erro: " << e.what() << std::endl;
}
