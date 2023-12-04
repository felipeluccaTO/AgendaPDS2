#include "Usuario.hpp"
#include "Excecoes.hpp"

#include <iostream>
#include <string>
#include <sstream>

static std::unordered_map<std::string, Usuario> _listadeusuario;
 
Usuario::Usuario(std::string& nome, std::string& sobrenome, std::string& idade, std::string& email) {
    setNome(nome, sobrenome);
    setIdade(&idade);
    setEmail(&email);
}

std::string Usuario::getNome() const {

    return this->_nome; ///< Retorna o nome
}

std::string Usuario::getIdade() const {

    return this->_idade; ///< Retorna a idade
}

std::string Usuario::getEmail() const {
    
    return this->_email; ///< Retorna o email
}

void Usuario::setNome(std::string novo_nome, std::string novo_sobrenome) {

    try {

        const size_t MAX_CARACTERES = 40; ///< Limite de caracteres 

        /// Verifica se o nome eh valido
        if (!novo_nome.length() >= MAX_CARACTERES || !(novo_nome.empty())) {

            this->_nome = novo_nome; ///< Atribui o novo nome
        }
        else {

            throw std::invalid_argument("Nome invalido");
        }
        
        /// Verifica se o sobrenome eh valido
        if (!novo_sobrenome.length() >= MAX_CARACTERES || !(novo_sobrenome.empty())) {

            this->_nome = novo_sobrenome; ///< Atribui o novo sobrenome
        }
        else {

            throw std::invalid_argument("Nome invalido");
        }        
    } 
    catch (const std::exception& e) {
        
        std::cout << "O nome e sobrenome devem possuir entre 1 e 50 caracteres" << std::endl;
        
        handleExcecao(e);
    }
}

void Usuario::setIdade(std::string* nova_idade) {

    try {

        const unsigned MIN_IDADE = 1; ///< Idade minima
        const unsigned MAX_IDADE = 150; ///< Idade maxima  
        
        std::istringstream iss(*nova_idade);
        std::string idade_string;

        std::getline(iss, idade_string, ' ');

        int idade = std::stoi(idade_string);

        /// Verifica se a idade eh valida
        if (idade > MIN_IDADE && idade < MAX_IDADE) {

            this->_idade = idade_string; ///< Atribui a nova idade
        }
        else {

            throw std::invalid_argument("Idade invalida");
        }
    } 
    catch (const std::exception& e) {
        
        std::cout << "Insira uma idade valida. (Formato: x anos)" << std::endl;
        
        handleExcecao(e);
    }    
}

void Usuario::setEmail(std::string* novo_email) {

    try {

        if (ListaUsuario::checkUsuario(novo_email)) throw std::logic_error("O email fornecido ja esta em uso");

        std::istringstream iss(*novo_email);
        std::string usuario, dominio;

        /// Quebra o novo email em partes, para fazer as verificacoes necessarias
        std::getline(iss, usuario, '@');
        std::getline(iss, dominio);

        /// Verifica se o usuario ou dominio estao preenchidos
        if (usuario == "" || dominio == "") {
        
            throw std::invalid_argument("Email incompleto"); 
        }

        /// Verifica se o dominio esta preenchido corretamente
        if (dominio != "gmail.com" && dominio != "yahoo.com" && dominio != "outlook.com") {

            throw std::invalid_argument("Dominio do email invalido");
        }

        this->_email = *novo_email; ///< Atribui o novo email
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Email deve estar no formato: usuario@dominio.com" << std::endl
        << "Dominios aceitos:" << std::endl
        << "    - 'gmail.com'" << std::endl
        << "    - 'yahoo.com'" << std::endl
        << "    - 'outlook.com'" << std::endl;

        handleExcecao(e);
    }
    catch (const std::exception& e) {

        handleExcecao(e);
    }
}

void ListaUsuario::adicionarUsuario(Usuario* usuario) {
    
    _listadeusuario.insert(std::make_pair(usuario->getEmail(), *usuario)); ///< Adicionando o email do usuario logado na lista
}

void ListaUsuario::removerUsuario(Usuario* usuario) {

    _listadeusuario.erase(usuario->getEmail()); ///< Removendo o Usuario da lista
}

bool ListaUsuario::checkUsuario(std::string* email) {

    auto it = _listadeusuario.find(*email); ///< Procura o usuario na lista pelo email

    return (it != _listadeusuario.end());
}

bool ListaUsuario::checkUsuario(std::string* email, std::string* nome) {

    auto it = _listadeusuario.find(*email); ///< Procura o usuario na lista pelo email

    return (it != _listadeusuario.end() && it->second.getEmail() == *email);
}
