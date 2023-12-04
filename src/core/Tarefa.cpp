#include "Tarefa.hpp"
#include "Excecoes.hpp"

#include <iostream>
#include <sstream>
#include <chrono>
#include <ctime>

static std::unordered_map<std::string, Compromisso*> _listadeCompromisso;
static std::unordered_map<std::string, Tarefa*> _listadeTarefa;

Tarefa::Tarefa(std::string& titulo, std::string& descricao, std::string& data, unsigned prioridade, std::string& estado) {
    _titulo = titulo;
    _descricao = descricao;
    _data = data;
    _prioridade = prioridade;
    _estado = estado;
}

std::string Tarefa::getTitulo() const {

    return this->_titulo; ///< Retorna o titulo
}

std::string Tarefa::getDescricao() const {

    return this->_descricao; ///< Retorna a descriçao
}

std::string Tarefa::getData() const {

    return this->_data; ///< Retorna a data
}

unsigned Tarefa::getPrioridade() const {

    return this->_prioridade; ///< Retorna a prioridade
}

std::string Tarefa::getEstado() const {

    return this->_estado; ///< Retorna o estado
}

void Tarefa::setTitulo(const std::string& novo_Titulo) {

    try {
        const size_t MAX_CARACTERES = 50; ///< Limite de caracteres para o novo titulo

        /// Verifica se o novo titulo eh valido
        if (!novo_Titulo.length() >= MAX_CARACTERES || !novo_Titulo.empty()) {

            this->_titulo = novo_Titulo; ///< Atribui o novo titulo
        }
        else {

            throw std::invalid_argument("Titulo invalido");
        }
    } 
    catch (const std::exception& e) {
        
        std::cout << "Titulo deve possuir entre 1 e 50 caracteres" << std::endl;
        
        handleExcecao(e);
    }
}

void Tarefa::setDescricao(const std::string& nova_Descricao) {

    try {
        const size_t MAX_CARACTERES = 120; ///< Limite de caracteres para a nova descricao

        /// Verifica se a nova descricao eh valida
        if (!nova_Descricao.length() || !nova_Descricao.empty()) {

            this->_descricao = nova_Descricao; //< Atribui a nova descricao
        }
        else {
        
            throw std::invalid_argument("Descricao invalida");
        }
    }
    catch (const std::exception& e) {
        
        std::cout << "Descricao deve possuir entre 1 e 120 caracteres" << std::endl;
        
        handleExcecao(e);
    }
}

void Tarefa::setData(const std::string& nova_Data) {

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

        std::cout << "Impossivel adicionar uma tarefa ou compromisso para datas anteriores a atual" << std::endl;
        
        handleExcecao(e);
    }
    catch (const std::exception& e) {
    
        handleExcecao(e);
    }
}

void Tarefa::setPrioridade(const unsigned nova_Prioridade) {
    try {
        /// Verifica se a nova prioridade eh valida
        if (nova_Prioridade == 1 || nova_Prioridade == 2 || nova_Prioridade == 3) {
        
            this->_prioridade = nova_Prioridade; ///< Atribui a nova prioridade
        }
        else {

            throw std::invalid_argument("Prioridade invalida");
        }
    }
    catch (const std::exception& e) {

        std::cout << "A prioridade deve ser: " << std::endl
        << "    - '1' para menos importante" << std::endl
        << "    - '2' para importante" << std::endl
        << "    - '3' para mais importante" << std::endl;
        
        handleExcecao(e);
    }
}

void Tarefa::setEstado(const std::string& novo_Estado) {

    try {    
        /// Verifica se o novo estado eh valido
        if (novo_Estado == "feito" || novo_Estado == "em progresso" || novo_Estado == "não feito") {
        
            this->_estado = novo_Estado; ///< Atribui o novo estado
        }
        else {

            throw std::invalid_argument("Estado invalido");
        }
    }
    catch (const std::exception& e) {

        std::cout << "O estado deve ser: " << std::endl
        << "    - 'feito'" << std::endl 
        << "    - 'em progresso'" << std::endl 
        << "    - 'nao feito'" << std::endl;

        handleExcecao(e);
    }    
}

Compromisso::Compromisso(std::string& data, std::string& local, std::string& titulo, std::string& descricao, std::string& horario,
            std::string& estado, unsigned prioridade) : Tarefa(titulo, descricao, data, prioridade, estado) {
    _local = local;
    _horario = horario;
}

std::string Compromisso::getCor() const {

    return this->_cor; ///< Retorna a cor
}

std::string Compromisso::getLocal() const {

    return this->_local; ///< Retorna o local
}

std::string Compromisso::getHorario() const {

    return this->_horario; ///< Retorna o horario
}

void Compromisso::setCor(const std::string& nova_Cor) {

    try {

        // Escolher a cor com base na prioridade
        std::string cor;
        
        if (nova_Cor == "laranja") {

            this->_cor = "\033[38;2;247;99;25m"; ///< Atribui a cor laranja
        }
        else if (nova_Cor == "azul") {

            this->_cor = "\033[38;2;25;84;247m"; ///< Atribui a cor azul
        }
        else if (nova_Cor == "roxo") {

            this->_cor = "\033[38;2;140;25;247m"; ///< Atribui a cor roxa
        }
        else if (nova_Cor == "rosa") {

            this->_cor = "\033[38;2;247;25;180m"; ///< Atribui a cor rosa
        }
        else if (!nova_Cor.empty()) {

            throw std::invalid_argument("Cor invalida");
        }
    }
    catch (std::exception& e) {

        std::cout << "Cores aceitas:" << std::endl
        << "    - 'laranja'" << std::endl
        << "    - 'azul'" << std::endl
        << "    - 'roxo'" << std::endl
        << "    - 'rosa'" << std::endl;

        handleExcecao(e);
    }
}

void Compromisso::setLocal(const std::string& novo_Local) {

    try {
        const size_t MAX_CARACTERES = 100; ///< Limite de caracteres para o novo local

        /// Verifica se o novo local eh valido
        if (!novo_Local.length() >= MAX_CARACTERES || !novo_Local.empty()) {

            this->_local = novo_Local; ///< Atribui o novo local
        }
        else {

            throw std::invalid_argument("Local invalido");
        }
    } 
    catch (const std::exception& e) {
        
        std::cout << "Local deve possuir entre 1 e 100 caracteres" << std::endl;
        
        handleExcecao(e);
    }
}

void Compromisso::setHorario(const std::string& novo_Horario) {

        try {
        /// Verifica o formato do novo horario
        std::istringstream iss(novo_Horario);
        int HH, MM, SS;
        char limitador; ///< Limitador deve ser ':'

        if (!(iss >> HH >> limitador >> MM >> limitador >> SS) || limitador != ':') {
            
            throw std::invalid_argument("Formato do horario invalido");
        }

        /// Obtem a data do compromisso
        std::string data_compromisso = getData();

        if (!data_compromisso.empty()) {
            
            std::istringstream iss(data_compromisso);
            int dia, mes, ano;
            char limitador; ///< Limitador deve ser '/'

            iss >> HH >> limitador >> MM >> limitador >> SS;

            // Cria uma representacao da data do compromisso
            std::tm tmDataCompromisso = {0}; ///< Inicializa o struct da data 
            
            tmDataCompromisso.tm_mday = dia; ///< Atribui o dia da data
            
            tmDataCompromisso.tm_mon = mes - 1; ///< Atribui o mes da data (os meses são de 0 a 11)
            
            tmDataCompromisso.tm_year = ano - 1900; ///< Atribui o ano da data (os anos sao contados a partir de 1900)

            tmDataCompromisso.tm_hour = HH; ///< Atribui a nova hora do compromisso

            tmDataCompromisso.tm_min = MM; ///< Atribui os novos minutos do compromisso

            tmDataCompromisso.tm_sec = SS; ///< Atribui os novos segundos do compromisso

            /// Converte a data de time_t para time_point
            auto timepoint_data_compromisso = std::chrono::system_clock::from_time_t(std::mktime(&tmDataCompromisso));

            /// Obtem a data atual do sistema
            auto timepoint_agora = std::chrono::system_clock::now();

            /// Converte time_point para time_t
            std::time_t time_t_agora = std::chrono::system_clock::to_time_t(timepoint_agora);
    
            /// Converte time_t para uma struct tm
            struct std::tm* tmAtual = std::localtime(&time_t_agora);

            // Verifica se o novo horario eh no dia
            if (timepoint_data_compromisso <= timepoint_agora) {
        
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

std::string setCorPrioridade(unsigned prioridade) {

    // Escolher a cor com base na prioridade
    std::string cor;
        
    switch (prioridade) {
        case 1:
            cor = "\033[38;2;29;247;25m"; // Verde (prioridade 1)
            return cor;

        case 2:
            cor = "\033[38;2;247;228;25m"; // Amarelo (prioridade 2)
            return cor;

        case 3:
            cor = "\033[38;2;247;25;25m"; // Vermelho (prioridade 3)
            return cor;

        default:
            cor = "\033[0m"; // Padrão (sem cor)
            return cor;
    }
}

void ListaTarefa::adicionarTarefa(Tarefa* tarefa, std::string* user_email) {

    _listadeTarefa.insert(std::make_pair(*user_email, tarefa)); ///< Adicionando a tarefa na lista
}

void ListaTarefa::removerTarefa(Tarefa* tarefa, std::string* user_email) {
    auto it = std::find_if(
        _listadeTarefa.begin(),
        _listadeTarefa.end(),
        [user_email, tarefa](const auto & p) {
            return (p.first == *user_email && p.second == tarefa);
            // Utilize p.first e p.second em vez de p->first e p->second
        }
    );

    if (it != _listadeTarefa.end()) {
        _listadeTarefa.erase(it);
    }
}

Tarefa* ListaTarefa::buscarTarefa(const std::string& tarefa_titulo){
    auto it =_listadeTarefa.find(tarefa_titulo);
        if (it != _listadeTarefa.end()) {
            return (it->second);
        } else {
            return nullptr; // Tarefa não encontrada
        }
}

unsigned ListaTarefa::tamanho() {

    return _listadeTarefa.size(); ///< Retornando o tamanho da lista
}

void ImprimirTarefas::verTarefas(std::string* user_email) {
    
    /// Imprime as tarefas atuais da lista
    for (const auto& tarefa : _listadeTarefa) {

        /// Verifica se a tarefa pertence ao usuario
        if (tarefa.first == *user_email) {
            
            /// Obtem a prioridade
            unsigned prioridade = tarefa.second->getPrioridade();

            /// Obtem a cor
            std::string cor = setCorPrioridade(prioridade);
            
            std::cout << "----------" << std::endl

            << cor

            << "Titulo: " << tarefa.second->getTitulo() << std::endl

            << "\033[0m" ///< Restaura a cor padrao do texto
            
            << "Descriçao: " << tarefa.second->getDescricao() << std::endl
            
            << "Data: " << tarefa.second->getData() << std::endl

            << "Prioridade: " << tarefa.second->getPrioridade() << std::endl
            
            << "Estado: " << tarefa.second->getEstado() << std::endl

            << std::endl;
        }        
    }
}

void ListaCompromisso::adicionarCompromisso(Compromisso* compromisso, std::string* user_email) {
    
    _listadeCompromisso.insert(std::make_pair(*user_email, compromisso)); ///< Adicionando o compromisso na lista
}


void ListaCompromisso::removerCompromisso(Compromisso* compromisso, std::string* user_email) {
    auto it = std::find_if(
        _listadeCompromisso.begin(),
        _listadeCompromisso.end(),
        [user_email, compromisso](const auto & p) {
            return (p.first == *user_email && p.second == compromisso);
            // Use p.first e p.second em vez de p->first e p->second
        }
    );

    if (it != _listadeCompromisso.end()) {
        _listadeCompromisso.erase(it);
    }
}

Compromisso* ListaCompromisso::buscarCompromisso(const std::string& compromisso_titulo) {
        auto it = _listadeCompromisso.find(compromisso_titulo);
        if (it != _listadeCompromisso.end()) {
            return (it->second);
        } else {
            return nullptr; // Compromisso não encontrado
        }
    }

unsigned ListaCompromisso::tamanho() {

    return _listadeCompromisso.size(); ///< Retornando o tamanho da lista
}

void ImprimirCompromissos::verCompromissos(std::string* user_email) {

    /// Imprime os compromissos atuais da lista
    for (const auto& compromisso : _listadeCompromisso) {
        
        /// Verifica se o compromisso pertence ao usuario
        if (compromisso.first == *user_email) {
            
            /// Obtem a prioridade
            unsigned prioridade = compromisso.second->getPrioridade();

            /// Obtem a cor
            std::string cor_prioridade = setCorPrioridade(prioridade);

            std::string cor_compromisso = compromisso.second->getCor();
            
            std::cout << "----------" << std::endl

            << cor_prioridade ///< Muda a cor do texto, de acordo com a prioridade
            
            << "Titulo: " << compromisso.second->getTitulo() << std::endl;

            /// Verifica se o compromisso tem uma cor definida pelo usuario
            /// Se nao tem, volta para a cor padrao do texto
            if (!cor_compromisso.empty()) {

                std::cout << cor_compromisso; ///< Muda a cor do texto para a cor escolhida pelo usuario
            }
            else {

                std::cout << "\033[0m"; ///< Restaura a cor padrao do texto
            }
            
            std::cout << "Descriçao: " << compromisso.second->getDescricao() << std::endl
            
            << "Data: " << compromisso.second->getData() << ", às " << compromisso.second->getHorario() << std::endl
            
            << "Local: " << compromisso.second->getLocal() << std::endl
            
            << "Prioridade: " << prioridade << std::endl

            << "Estado: " << compromisso.second->getEstado() << std::endl
            
            << "\033[0m" ///< Restaura a cor padrao do texto

            << std::endl;
        }        
    }
}
