#ifndef LEMBRETE_HPP
#define LEMBRETE_HPP

#include <string>
#include <algorithm>
#include <unordered_map>
   
class Lembrete {
public:
    Lembrete(const std::string& horario, const std::string& mensagem, const std::string& data);

    /// @brief Busca pela data do lembrete
    ///
    /// @return String da data 
    std::string getData() const;
    
    /// @brief Busca pelo horario do lembrete
    ///
    /// @return String do horario
    std::string getHorario() const;

    /// @brief Busca pela mensagem do lembrete
    ///
    /// @return String da mensagem
    std::string getMensagem() const;
    
    /// @brief Muda a data de um lembrete
    ///
    /// @param nova_Data A nova data a ser adicionada
    ///
    /// @attention A data informada deve estar no formato: DD/MM/AAAA
    void setData(const std::string& nova_Data);

    /// @brief Muda o horario de um compromisso
    ///
    /// @param novo_Horario O novo horario a ser colocado
    ///
    /// @attention O horario informado deve estar no formato: HH:MM:SS
    void setHorario(const std::string& novo_Horario);

    /// @brief Adiciona uma mensagem para um lembrete
    ///
    /// @param texto A mensagem a ser adicionada
    void setMensagem(std::string texto);
    
private:
    std::string _data; ///< Armazena a data do lembrete
    std::string _horario; ///< Armazena o horario do lembrete
    std::string _mensagem; ///< Armazena a mensagem do lembrete
};

class ListaLembrete {
public:
    ListaLembrete() { const auto _listadeLembretes = std::unordered_map<std::string, Lembrete*>(); }

    /// @brief Adiciona um Lembrete a lista de Lembretes
    ///
    /// @param lembrete O lembrete a ser adicionado
    ///
    /// @param user_email O email do usuário logado
    static void adicionarLembrete(Lembrete* lembrete, std::string* user_email);
    
    /// @brief Remove um lembrete da lista
    ///
    /// @param lembrete O lembrete a ser removido
    ///
    /// @param user_email O email do usuário logado
    static void removerLembrete(Lembrete* lembrete, std::string* user_email);

    /// @brief Procura pelo lembrete pela mensagem
    ///
    /// @param mensagem A mensagem do lembrete a ser buscado
    static Lembrete* buscarLembrete(std::string* mensagem);

    /// @brief Calcula o tamanho do mapa
    ///
    /// @return Um unsigned com o tamanho
    unsigned tamanho();
    
};

class ImprimirLembretes : public ListaLembrete {
public:
    /// @brief Imprime todos lembretes da lista 
    ///
    /// @param user_email O email do usuario logado
    static void verLembretes(std::string* user_email);
};

#endif