#include "Menu.hpp"
#include "LoginMenu.hpp"
#include "Usuario.hpp"
#include "UsuarioMenu.hpp"

#include <iostream>
#include <string>

MenuLogin::MenuLogin() {
  opcoes.push_back("1 --> Entrar");
  opcoes.push_back("2 --> Cadastrar Usuario");
}

PrimeiroMenu *MenuLogin::next(unsigned option) {
  
  switch (option) {
  case 1: {
    std::string login_email;
    std::cout << "> Digite seu email: ";
    std::cin >> login_email;

    std::string login_nome;
    std::cout << "> Digite seu nome: ";
    std::cin >> login_nome;

    //logica para ver se usuario existe ou não (checar email e nome na lista de usuarios)
    
    // Ex: bool confirmarlogin( std::string login_email, std::string login_nome ) ...

    if ( ) { std::cout << "Logando: " << login_nome << login_email std::endl 
             return new UsuarioMenu(usuario);
           }
    // se existi --> logar (terminar a logica)
    
    else {std::cout << "Usuário não encontrado " << std::endl;
            break;} 
    // se não existir --> reportar o erro e voltar para escolha de entrar, cadastrar ou sair 

    // confirmar esse else no break, ou logica de retorno (terminar a logica)
  }
  case 2: {
   

    // criar um usuario 

    std::cout << "> Email: ";
    std::cin >> Usuario.email;
    // usar função de alocar email
    
    std::cout << "> Primeiro nome: ";
    std::cin >> Usuario.nome;
    //usar função de alocar nome
    
    std::cout << "> Sobrenome: ";
    std::cin >> Usuario.sobrenome;
    //usar função de alocar sobrenome

    std::cout << "> Idade: ";
    std::cin >> Usuario.idade;
    //usar função de alocar idade 

    std::cout << "Salvando usuário" << std::endl;

    return new UsuarioMenu(usuario);
  }
  
  }

  // TODO: próximo menu
  return nullptr;
}

