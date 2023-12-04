#ifndef EXCECOES_HPP
#define EXCECOES_HPP

#include <stdexcept>

/// @brief Lida com as exceçoes geradas pelo programa
///
/// @param e Objeto da exceçao lançado pelo codigo 
void handleExcecao(const std::exception& e);

#endif