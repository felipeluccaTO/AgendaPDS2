#include "Lembrete.hpp"
#include "Excecoes.hpp"

#include <string>
#include <iostream>
#include <iostream>
#include <sstream>
#include <chrono>
#include <ctime>

static std::unordered_map<std::string, Lembrete*> _listadeLembretes;

Lembrete::Lembrete(const std::string& horario, const std::string& mensagem, const std::string& data) {
    _data = data;
    _horario = horario;
    _mensagem = mensagem;
}

std::string Lembrete::getData() const {

    return this->_data; ///< Retorna a data
}

std::string Lembrete::getHorario() const {

    return this->_horario; ///< Retorna o horario
}

std::string Lembrete::getMensagem() const {

    return this->_mensagem; ///< Retorna a mensagem
}

void Lembrete::setData(const std::string& nova_Data) {
    try {
        /// Verifica o formato da nova data
        std::istringstream iss(nova_Data);
        int dia, mes, ano;
        char limitador; ///< Limitador deve ser '/'

        if (!(iss >> dia >> limitador >> mes >> limitador >> ano) || limitador != '/') {
            
            throw std::invalid_argument("Formato da data invalido");
        }

        /// Obtem a data atual do sistema
        auto timepoint_agora = std::chrono::system_clock::now();
    
        /// Converte time_point para time_t
        std::time_t time_t_agora = std::chrono::system_clock::to_time_t(timepoint_agora);
    
        /// Converte time_t para uma struct tm
        struct std::tm* tmAtual = std::localtime(&time_t_agora);

        // Cria uma representacao da nova data
        std::tm tmNovaData = {0}; ///< Inicializa o struct da nova data
        tmNovaData.tm_mday = dia; ///< Atribui o dia da nova data
        tmNovaData.tm_mon = mes - 1; ///< Atribui o mes da nova data (os meses são de 0 a 11)
        tmNovaData.tm_year = ano - 1900; ///< Atribui o ano da nova data (os anos são contados a partir de 1900)

        /// Converte a nova data de time_t para time_point
        auto timepoint_novadata = std::chrono::system_clock::from_time_t(std::mktime(&tmNovaData));

        // Verifica se a nova data esta no futuro
        if (timepoint_novadata <= timepoint_agora) {
        
            throw std::logic_error("Data no passado");
        }

        this->_data = nova_Data; ///< Atribui a nova data
    }
    catch (const std::invalid_argument& e) {
        
        std::cout << "Data deve estar no formato DD/MM/AAAA" << std::endl;
        
        handleExcecao(e);
    }
    catch (const std::logic_error& e) {

        std::cout << "Impossivel adicionar um lembrete para datas anteriores a atual" << std::endl;
        
        handleExcecao(e);
    }
    catch (const std::exception& e) {
    
        handleExcecao(e);
    }
}

void Lembrete::setHorario(const std::string& novo_Horario) {
    
    try {
        /// Verifica o formato do novo horario
        std::istringstream iss(novo_Horario);
        int HH, MM, SS;
        char limitador; ///< Limitador deve ser ':'

        if (!(iss >> HH >> limitador >> MM >> limitador >> SS) || limitador != ':') {
            
            throw std::invalid_argument("Formato do horario invalido");
        }

        /// Obtem a data do lembrete
        std::string data_lembrete = getData();

        if (!data_lembrete.empty()) {
            
            std::istringstream iss(data_lembrete);
            int dia, mes, ano;
            char limitador; ///< Limitador deve ser '/'

            iss >> HH >> limitador >> MM >> limitador >> SS;

            // Cria uma representacao da data do lembrete            
            std::tm tmDataLembrete = {0}; ///< Inicializa o struct da data 
            
            tmDataLembrete.tm_mday = dia; ///< Atribui o dia da data
            
            tmDataLembrete.tm_mon = mes - 1; ///< Atribui o mes da data (os meses são de 0 a 11)
            
            tmDataLembrete.tm_year = ano - 1900; ///< Atribui o ano da data (os anos sao contados a partir de 1900)

            tmDataLembrete.tm_hour = HH; ///< Atribui a nova hora dolembrete

            tmDataLembrete.tm_min = MM; ///< Atribui os novos minutos dolembrete

            tmDataLembrete.tm_sec = SS; ///< Atribui os novos segundos do lembrete
            /// Converte a data de time_t para time_point
            auto timepoint_data_lembrete = std::chrono::system_clock::from_time_t(std::mktime(&tmDataLembrete));

            /// Obtem a data atual do sistema
            auto timepoint_agora = std::chrono::system_clock::now();

            /// Converte time_point para time_t
            std::time_t time_t_agora = std::chrono::system_clock::to_time_t(timepoint_agora);
    
            /// Converte time_t para uma struct tm
            struct std::tm* tmAtual = std::localtime(&time_t_agora);

            // Verifica se o novo horario eh no dia
            if (timepoint_data_lembrete <= timepoint_agora) {
        
                throw std::logic_error("Horario no passado");
            }

            this->_horario = novo_Horario; ///< Atribui o novo horario
        }
        else {

            this->_horario = novo_Horario; ///< Atribui o novo horario
        }
    }
    catch (const std::invalid_argument& e) {
        
        std::cout << "Horario deve estar no formato HH:MM:SS" << std::endl;
        
        handleExcecao(e);
    }
    catch (const std::logic_error& e) {

        std::cout << "Impossivel adicionar uma tarefa ou compromisso para datas anteriores a atual" << std::endl;
        
        handleExcecao(e);
    }
    catch (const std::exception& e) {
    
        handleExcecao(e);
    }
}

void Lembrete::setMensagem(std::string nova_Mensagem) {
    
    try {
        const size_t MAX_CARACTERES = 45; ///< Limite de caracteres para a mensagem do lembrete
        
        /// Verifica se a nova mensagem esta vazia, se a nova mensagem eh igual a mensagem atual ou ultrapassa o limite de caracteres
        if (!nova_Mensagem.empty() || nova_Mensagem != this->_mensagem || nova_Mensagem.length() < MAX_CARACTERES) {

            this->_mensagem = nova_Mensagem; ///< Atribui a nova mensagem
        } 
        else {

            throw std::invalid_argument("Mensagem invalida");
        }
    }
    catch (const std::exception& e) {

        std::cout << "A mensagem deve ser diferente da mensagem atual e possuir no maximo 45 caracteres" << std::endl;

        handleExcecao(e);
    }
}

void ListaLembrete::adicionarLembrete(Lembrete* lembrete, std::string* user_email) {

    _listadeLembretes.insert(std::make_pair(*user_email, lembrete)); ///< Adicionando o lembrete na lista
}

void ListaLembrete::removerLembrete(Lembrete* lembrete, std::string* user_email) {
    
    auto it = std::find_if(
        _listadeLembretes.begin(), _listadeLembretes.end(), 
        [user_email, lembrete](const auto & p) 
        { return (p.first == *user_email && p.second == lembrete); }
        // Utilize p.first e p.second para acessar os elementos do par corretamente
    );

    if (it != _listadeLembretes.end()) {
        _listadeLembretes.erase(it);
    }
}

Lembrete* ListaLembrete::buscarLembrete(std::string* mensagem) {
    auto it = std::find_if(
        _listadeLembretes.begin(),
        _listadeLembretes.end(),
        [mensagem](const auto & p) { return (p.second->getMensagem() == *mensagem); }
        // Corrigido para acessar a mensagem corretamente com p.second->getMensagem()
    );

    if (it != _listadeLembretes.end()) {
        return it->second;
    } else {
        return nullptr;
    }
}

void ImprimirLembretes::verLembretes(std::string* user_email) {
    
    /// Imprime os lembretes atuais da lista
    for (const auto& lembrete : _listadeLembretes) {

        /// Verifica se o lembrete pertence ao usuario logado
        if (lembrete.first == *user_email) {

            std::cout << "Lembrete: " << lembrete.second->getMensagem() << std::endl 
            << "Data: " << lembrete.second->getData() << std::endl
            << "Horario: " << lembrete.second->getHorario() << std::endl;
            std::cout << "------------------------" << std::endl;
        }
    }
}
