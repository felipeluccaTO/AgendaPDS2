#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <string>
#include <unordered_map>
   
class Usuario {
public:
  Usuario(std::string& nome, std::string& sobrenome, std::string& idade, std::string& email);
      
  /// @brief Busca pelo nome do usuario 
  ///
  /// @return String do nome
  std::string getNome() const;

  /// @brief Busca pela idade do usuario
  ///
  /// @return String da idade 
  std::string getIdade() const;
    
  /// @brief Busca pelo email do usuario 
  ///
  /// @return String do email
  std::string getEmail() const; 

  /// @brief Muda o nome e sobrenome de um usuario
  ///
  /// @param nome O nome do usuario 
  ///
  /// @param sobrenome O sobrenome do usuario 
  void setNome(std::string nome, std::string sobrenome);

  /// @brief Muda a idade de um usuario
  ///
  /// @param idade A nova idade 
  void setIdade(std::string* idade);
      
  /// @brief Muda o email de um usuario
  ///
  /// @param email O email a ser alterado
  void setEmail(std::string* email);
        
private:
  std::string _nome; ///< Armazena o primeiro nome do usuario
  std::string _sobrenome; ///< Armazena o sobrenome do usuario
  std::string _idade; ///< Armazena a idade do usuario
  std::string _email; ///< Armazena o email do usuario
};

class ListaUsuario {
public:
  ListaUsuario() { const auto _listadeUsuario = std::unordered_map<std::string, Usuario>(); }
  /// @brief Adiciona um Usuario a lista de Usuarios
  ///
  /// @param usuario O Usuario a ser adicionado
  static void adicionarUsuario(Usuario* usuario);

  /// @brief Remove um Usuario da lista de Usuarios
  ///
  /// @param usuario O Usuario a ser removido
  static void removerUsuario(Usuario* usuario);

  /// @overload
  ///
  /// @brief Verifica se o usuario existe
  ///
  /// @details Verifica se o email ja esta cadastrado
  ///
  /// @param email O email do usuario a ser verificado
  ///
  /// @return True se o usuario existe, false caso contrario 
  static bool checkUsuario(std::string* email);

  /// @overload
  ///
  /// @brief Verifica se o email e o nome fornecidos correpondem na lista
  ///
  /// @param email O email fornecido
  /// 
  /// @param nome O nome fornecido 
  ///
  /// @return True se o nome e o email correpondem, false caso contrario
  static bool checkUsuario(std::string* email, std::string* nome);


};

#endif