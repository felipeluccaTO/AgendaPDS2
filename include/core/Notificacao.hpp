#ifndef NOTIFICACAO_HPP
#define NOTIFICACAO_HPP

#include "Tarefa.hpp"
#include "Lembrete.hpp"

#include <ctime>
#include <chrono>

class Notificacao {
public:
    Notificacao(const int hora_Antes, const int min_Antes);
    
    /// @brief Compara com o horario real e notifica um compromisso no horario programado
    ///
    /// @param compromisso O compromisso a ser notificado
    void notificar(Compromisso* compromisso);
    
    /// @brief Compara com o horario real e notifica um lembrete no horario programado
    ///
    /// @param lembrete O lembrete a ser notificado
    void notificar(Lembrete* lembrete);

    /// @brief Ativa uma notificação
    void ativarNotificacao();

    /// @brief Desativa uma notificação
    void desativarNotificacao();

    /// @brief Verifica o estado da notificação
    ///
    /// @return true (se está ativada) ou false (se está desativada)
    bool checkEstado();

private:
    int _min_Antes; ///< Armazena os minutos de antecedencia da notificaçao (1 a 59) 
    int _hora_Antes; ///< Armazena as horas de antecedencia da notificaçao (1 a 23)
    bool _estado; ///< Armazena o estado da notificação (ativada = true, desativada = false)
};

#endif