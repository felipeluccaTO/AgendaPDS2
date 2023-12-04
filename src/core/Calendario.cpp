#include "Calendario.hpp"

#define STRING(num) #num

void Calendario::inserir(std::string key, std::vector<std::string> value) {

    _mapa_Horario.insert(std::pair<std::string, std::vector<std::string>>(key, value));
}

unsigned Calendario::sizeMapaHorario() {

    return _mapa_Horario.size();
}

void Calendario::inserir(std::string key) {

    _agenda.insert(std::pair<std::string, std::map<std::string, std::vector<std::string>>>(key, _mapa_Horario));
    _mapa_Horario.clear();
}

unsigned Calendario::sizeAgenda() {

    return _agenda.size();
}

void Calendario::imprimirCalendario(std::string data) {

    int dia = int(char(data[0]) + char(data[1])) - 1;
    int mes = char(data[3]) + char(data[4]);
    int ano = char(data[6]) + char(data[7]) + char(data[8]) + char(data[9]);

    for (unsigned cont=0; cont<7; cont++ ) {
        dia ++;

        if (dia > 30) {
            dia -= 30;
            mes ++;
        }

        if (mes > 12) {
            mes -= 12;
            ano ++;
        }

        std::string dia_Atual = STRING(dia);
        dia_Atual += '/';
        dia_Atual += STRING(mes);
        dia_Atual += '/';
        dia_Atual += STRING(ano);

        auto it = (_agenda.find(dia_Atual)->second).begin();

        std::cout << "Atividades do dia " << dia_Atual << ": " << std::endl << std::endl;

        while (it != (_agenda.find(dia_Atual)->second).end()) {
            std::cout << "Horario: " << it->first << std::endl << std::endl << "Atividades: " << std::endl << std::endl;

            if ((it->second).size() == 0) {
                std::cout << "Nenhuma atividade registrada!" << std::endl << std::endl;
            }

            for (unsigned i=0; i < (it->second).size(); i++) {
                
                std::cout << (it->second)[i] << std::endl;
            }
            it++;
        }
    }
}
