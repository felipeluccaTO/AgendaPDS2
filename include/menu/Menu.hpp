#ifndef MENU_HPP
#define MENU_HPP

#include <string>
#include <vector>
#include "Usuario.hpp"
#include "Tarefa.hpp"
#include "Lembrete.hpp"
#include "Calendario.hpp"

class PrimeiroMenu {
public:
  /// @brief Destrutor para destruiçao de subclasses
  virtual ~PrimeiroMenu() = default;

  /// @brief Constroi o proximo menu
  ///
  /// @param opcao A opção que o usuário escolheu
  ///
  /// @param old_menu Um ponteiro que aponta para o menu anterior
  ///
  /// @return Um ponteiro para o próximo menu
  virtual PrimeiroMenu *next(unsigned opcao, PrimeiroMenu *old_menu) = 0;

  /// @brief Busca pelo usuario logado
  ///
  /// @return String com email do usuario logado
  std::string getUsuario() const;

  /// @brief Guarda o usuario logado
  ///
  /// @param user_email O email do usuario logado 
  void setUsuario(std::string user_email);

  /// @brief Muda o titulo do menu
  ///
  /// @param novo_Titulo O novo titulo do menu
  void setTitulo(std::string novo_Titulo);

  /// @brief Muda o subtitulo do menu
  ///
  /// @param novo_Subtitulo O novo subtitulo do menu
  void setSubtitulo(std::string novo_Subtitulo);

  /// @brief Muda as opcoes do menu
  ///
  /// @param novasOpcoes As novas opcoes a serem adicionadas
  void setOpcoes(std::vector<std::string> novasOpcoes);

  /// @brief Renderiza as opçoes do menu
  virtual void renderizar() const;
  
private:
  std::string _user_email; ///< Armazena o email do usuario logado
  std::string _titulo = "Gerenciador de Tarefas e Compromissos "; ///< Armazena o titulo do menu
  std::string _sub_titulo = "Escolha uma opção:"; ///< Armazena o subtitulo do menu
  std::vector<std::string> _opcoes = {"1 --> Entrar", "2 --> Sair"}; ///< Armazena as opçoes do menu
};

class MenuLogin : public PrimeiroMenu {
public:
  /// @brief Constroi o menu de login
  MenuLogin();

  /// @brief Constroi o proximo menu
  ///
  /// @param opcao A opção que o usuário escolheu
  ///
  /// @param old_menu Um ponteiro que aponta para o menu anterior
  ///
  /// @return Um ponteiro para o próximo menu
  PrimeiroMenu *next(unsigned opcao, PrimeiroMenu *old_menu) override;
};

class UsuarioMenu : public PrimeiroMenu {
public:
  /// @brief Constroi o menu do usuario.  
  UsuarioMenu(std::string *login_email);

  /// @brief Constroi o proximo menu
  ///
  /// @param opcao A opção que o usuário escolheu
  ///
  /// @param old_menu Um ponteiro que aponta para o menu anterior
  ///
  /// @return Um ponteiro para o próximo menu
  PrimeiroMenu *next(unsigned option, PrimeiroMenu *old_menu) override;
};

class TarefaMenu : public PrimeiroMenu {
public:
  /// @brief Constroi o menu das tarefas  
  TarefaMenu(std::string *login_email);

  /// @brief Constroi o proximo menu
  ///
  /// @param opcao A opção que o usuário escolheu
  ///
  /// @param old_menu Um ponteiro que aponta para o menu anterior
  ///
  /// @return Um ponteiro para o próximo menu
  PrimeiroMenu *next(unsigned option, PrimeiroMenu *old_menu) override;
};

class LembreteMenu : public PrimeiroMenu {
public:
  /// @brief Constroi o menu dos lembretes  
  LembreteMenu(std::string *login_email);

  /// @brief Constroi o proximo menu
  ///
  /// @param opcao A opção que o usuário escolheu
  ///
  /// @param old_menu Um ponteiro que aponta para o menu anterior
  ///
  /// @return Um ponteiro para o próximo menu
  PrimeiroMenu *next(unsigned option, PrimeiroMenu *old_menu) override;
};

class CompromissoMenu : public PrimeiroMenu {
public:
  /// @brief Constroi o menu dos compromissos  
  CompromissoMenu(std::string *login_email);

  /// @brief Constroi o proximo menu
  ///
  /// @param opcao A opção que o usuário escolheu
  ///
  /// @param old_menu Um ponteiro que aponta para o menu anterior
  ///
  /// @return Um ponteiro para o próximo menu
  PrimeiroMenu *next(unsigned option, PrimeiroMenu *old_menu) override;
};

#endif