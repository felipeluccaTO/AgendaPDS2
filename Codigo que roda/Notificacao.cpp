#include "Notificacao.hpp"

#include <iostream>

using namespace std;

Notificacao::Notificacao(const int hora_antes, const int min_antes) {
    _min_Antes = min_antes;
    _hora_Antes = hora_antes;
    _estado = true;
}

void Notificacao::notificar(Compromisso* compromisso) {
    time_t timer;
    struct tm *horarioLocal;
    time(&timer); // Obtem informações de data e hora
    horarioLocal = localtime(&timer); // Converte a hora atual para a hora local

    int horaAtual = horarioLocal->tm_hour;
    int minAtual = horarioLocal->tm_min;

    int horaCompromisso = compromisso->getHorario()[0] + compromisso->getHorario()[1];
    int minCompromisso = compromisso->getHorario()[3] + compromisso->getHorario()[4];

    if (_estado && horaCompromisso - _hora_Antes == horaAtual && minCompromisso - _min_Antes == minAtual) {
        cout << compromisso->getDescricao() << " Daqui a: " << _hora_Antes << "h e " << _min_Antes << "min" << endl;
    }
}

void Notificacao::notificar(Lembrete* lembrete) {
    time_t timer;
    struct tm *horarioLocal;
    time(&timer); // Obtem informações de data e hora
    horarioLocal = localtime(&timer); // Converte a hora atual para a hora local

    int horaAtual = horarioLocal->tm_hour;
    int minAtual = horarioLocal->tm_min;
    
    int horaLembrete = lembrete->getHorario()[0] + lembrete->getHorario()[1];
    int minLembrete = lembrete->getHorario()[3] + lembrete->getHorario()[4];

    if (_estado && horaLembrete - _hora_Antes == horaAtual && minLembrete - _min_Antes == minAtual) {
        cout << lembrete->getMensagem() << " Daqui a: " << _hora_Antes << "h e " << _min_Antes << "min" << endl;
    }
}

void Notificacao::ativarNotificacao() {
    _estado = true;
}

void Notificacao::desativarNotificacao() {
    _estado = false;
}

bool Notificacao::checkEstado() {
    return _estado;
}
