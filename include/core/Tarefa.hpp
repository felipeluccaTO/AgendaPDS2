#ifndef TAREFA_HPP
#define TAREFA_HPP

#include <string>
#include <algorithm>
#include <unordered_map>

/// @brief Obtem a cor para imprimir de acordo com o nivel de prioridade
///
/// @details Prioridade 1: Verde, Prioridade 2: Amarelo, Prioridade 3: Vermelho
///
/// @param prioridade A prioridade da tarefa ou compromisso
///
/// @return String com o codigo da cor (em formataçao ANSI) 
std::string setCorPrioridade(unsigned prioridade);

class Tarefa {
public:
  Tarefa(std::string& titulo, std::string& descricao, std::string& data, unsigned prioridade, std::string& estado);
    
  /// @brief Busca pelo titulo da tarefa 
  ///
  /// @return String do titulo
  std::string getTitulo() const;

  /// @brief Busca pela descriçao da tarefa
  /// 
  /// @return String da descriçao 
  std::string getDescricao() const;

  /// @brief Busca pela data da tarefa
  ///
  /// @return String da data
  std::string getData() const;

  /// @brief Busca pela prioridade da tarefa
  ///
  /// @return Unsigned (1, 2 ou 3)
  unsigned getPrioridade() const;
    
  /// @brief Busca pelo estado da tarefa
  ///
  /// @return String do estado (feito, em progresso, nao feito)
  std::string getEstado() const; 
  
  /// @brief Muda o titulo de uma tarefa
  ///
  /// @param novo_Titulo O novo titulo a ser colocado
  void setTitulo(const std::string& novo_Titulo);

  /// @brief Muda a descriçao de uma tarefa
  ///
  /// @param nova_Descricao A nova descriçao a ser colocada
  void setDescricao(const std::string& nova_Descricao);

  /// @brief Muda a data de uma tarefa
  ///
  /// @param nova_Data A nova data a ser colocada
  ///
  /// @attention A data informada deve estar no formato: DD/MM/AAAA
  void setData(const std::string& nova_Data);

  /// @brief Muda a prioridade de uma tarefa
  ///
  /// @param nova_Prioridade A nova prioridade a ser colocada
  ///
  /// @attention A prioridade varia entre: 
  /// 1 --> menos importante, 2 --> importante, 3 --> muito importante.
  void setPrioridade(unsigned nova_Prioridade);

  /// @brief Muda o estado de uma tarefa
  ///
  /// @param novo_Estado O novo estado a ser colocado
  ///
  /// @attention O estado varia entre: feito (deletar em seguida), em progresso, não feito (alertar).
  void setEstado(const std::string& novo_Estado);
   
private:
  std::string _titulo; ///< Armazena o titulo da tarefa 
  std::string _descricao; ///< Armazena a descricao da tarefa
  std::string _data; ///< Armazena a data (em string) da tarefa 
  unsigned _prioridade; ///< Armazena a prioridade da tarefa 
  std::string _estado; ///< Armazena o estado da tarefa 
 };

class Compromisso : public Tarefa {
public:
  Compromisso(std::string& data, std::string& local,std::string& titulo, std::string& descricao, std::string& horario, std::string& estado, unsigned prioridade);

  /// @brief Busca pela cor do compromisso
  ///
  /// @return String com o codigo em formataçao ANSI da cor
  std::string getCor() const;

  /// @brief Busca pelo local do compromisso
  ///
  /// @return String do local  
  std::string getLocal() const;

  /// @brief Busca pelo horario do compromisso
  ///
  /// @return String do horario 
  std::string getHorario() const;

  /// @brief Muda a cor de um compromisso
  ///
  /// @details Necessario para organizaçao dos compromissos por cor
  ///
  /// @attention Cores aceitas: 'laranja', 'azul', 'roxo', 'rosa'
  ///
  /// @param nova_Cor A nova cor a ser adicionada
  void setCor(const std::string& nova_Cor);

  /// @brief Muda o local de um compromisso
  ///
  /// @param novo_Local O novo local a ser colocado 
  void setLocal(const std::string& novo_Local);

  /// @brief Muda o horario de um compromisso
  ///
  /// @param novo_Horario O novo horario a ser colocado
  ///
  /// @attention O horario informado deve estar no formato: HH:MM:SS
  void setHorario(const std::string& novo_Horario);

private:
  std::string _cor; ///< Armazena a cor do comprimisso, escolhida pelo usuario
  std::string _local; ///< Armazena o local do compromisso
  std::string _horario; ///< Armazena o horario do comprimisso
};

class ListaTarefa {
public:
  ListaTarefa() { const auto _listadeTarefa = std::unordered_map<std::string, Tarefa*>(); }

  /// @brief Adiciona uma tarefa na lista de tarefas
  ///
  /// @param tarefa A tarefa a ser adicionada
  ///
  /// @param user_email O email do usuario logado
  static void adicionarTarefa(Tarefa* tarefa, std::string* user_email);

  /// @brief Remove uma tarefa da lista de tarefas
  ///
  /// @param tarefa a Tarefa a ser removida
  ///
  /// @param user_email O email do usuario logado
  static void removerTarefa(Tarefa* tarefa, std::string* user_email);

  /// @brief Busca uma Tarefa pelo seu Título
  ///
  /// @param tarefa_titulo o Título da Tarefa a ser procurada
  static Tarefa* buscarTarefa(const std::string& tarefa_titulo);

  /// @brief Calcula o tamanho da lista
  ///
  /// @return Um unsigned com o tamanho
  unsigned tamanho();
  

};

class ListaCompromisso {
public:
  ListaCompromisso() { const auto _listadeCompromisso = std::unordered_map<std::string, Compromisso*>(); }

  /// @brief Adiciona um compromisso a lista de compromissos
  ///
  /// @param compromisso O compromisso a ser adicionado
  ///
  /// @param user_email O email do usuario logado
  static void adicionarCompromisso(Compromisso* compromisso, std::string* user_email);

  /// @brief Remove um compromisso da lista de compromissos
  ///
  /// @param compromisso O compromisso a ser removido
  ///
  /// @param user_email O email do usuario logado
  static void removerCompromisso(Compromisso* compromisso, std::string* user_email);

  /// @brief Busca uma Compromisso pelo seu Título
  ///
  /// @param compromisso_titulo O Título do Compromisso a ser buscado
  static Compromisso* buscarCompromisso(const std::string& compromisso_titulo);

  /// @brief Calcula o tamanho da lista
  ///
  /// @return Um unsigned com o tamanho
  unsigned tamanho();

};

class ImprimirTarefas : public ListaTarefa {
public:
  /// @brief Mostra a lista de tarefas do usuario logado
  ///
  /// @param user_email O email do usuario logado
  static void verTarefas(std::string* user_email);
};

class ImprimirCompromissos : public ListaCompromisso {
public:
  /// @brief Mostra a lista de compromissos do usuario logado
  ///
  /// @param user_email O email do usuario logado
  static void verCompromissos(std::string* user_email);
};

#endif