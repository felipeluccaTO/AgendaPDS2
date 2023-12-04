#ifndef CALENDARIO_HPP
#define CALENDARIO_HPP

#include "Tarefa.hpp"
#include "Lembrete.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <map>

class Calendario {
public:
    /// @brief Insere um grupo de atividades em um determinado horário
    ///
    /// @param key O horario das atividades
    ///
    /// @param value As atividades que serão inseridas
    void inserir(std::string key, std::vector<std::string> value);

    /// @brief Calcula o tamanho do mapa de horários
    ///
    /// @return Um unsigned com o tamanho
    unsigned sizeMapaHorario();

    /// @brief Insere um horário com atividades(ou não) em um determinado dia
    ///
    /// @param key O dia
    ///
    /// @param value As atividades que serão inseridas
    void inserir(std::string key); 

    /// @brief Calcula o tamanho da agenda
    ///
    /// @return Um unsigned com o tamanho
    unsigned sizeAgenda();

    /// @brief Imprime o calendario de 7 dias a partir do dia escolhido (Contando com ele)
    ///
    /// @param data O primero dia da sequência a ser mostrada
    void imprimirCalendario(std::string data);

private:
    std::map<std::string, std::vector<std::string>> _mapa_Horario; ///< Mapa para armazenar as atividades por horário
    std::map<std::string, std::map<std::string, std::vector<std::string>>> _agenda; ///< Mapa para armazenar os horários por dia
};

#endif