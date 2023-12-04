#include "Menu.hpp"
#include "Calendario.hpp"
#include "Lembrete.hpp"
#include "Tarefa.hpp"



#include <iostream>
#include <string>
#include <ctime>
#define STRING(num) #num

std::string PrimeiroMenu::getUsuario() const {

  return this->_user_email;
} 

void PrimeiroMenu::setUsuario(std::string user_email) {

  this->_user_email = user_email;
}

void PrimeiroMenu::setTitulo(std::string novoTitulo) {
  
  this->_titulo = novoTitulo;
}

void PrimeiroMenu::setSubtitulo(std::string novoSubstitulo) {

  this->_sub_titulo = novoSubstitulo;
}

void PrimeiroMenu::setOpcoes(std::vector<std::string> novasOpcoes) {

  this->_opcoes = novasOpcoes;
}

void PrimeiroMenu::renderizar() const {

  std::string border(_titulo.size() + 5, '=');
  std::cout << border << '\n';
  std::cout << "|| " << _titulo << "||" << '\n';
  std::cout << border << "\n\n";

  std::cout << _sub_titulo << '\n' << '\n';

  for (std::string opt : _opcoes) {
    
    std::cout << opt << '\n';
  }
  
  std::cout << border << "\n\n";
  
  std::cout << std::endl << "> Escolha: ";
}

MenuLogin::MenuLogin() {

  setTitulo("Seja bem-vindo ao Gerenciador de Tarefas! ");
  setSubtitulo("Escolha uma opcao:");
  setOpcoes({"1 --> Fazer login", "2 --> Fazer novo cadastro", "3 --> Sair do programa"});
}

PrimeiroMenu *MenuLogin::next(unsigned option, PrimeiroMenu *old_menu) {
  
  switch (option) {
    case 1: {

      std::string login_email;
      std::cout << std::endl << "> Digite seu email: ";
      std::cin >> login_email;

      std::string login_nome;
      std::cout << "> Digite seu nome: ";
      std::cin >> login_nome;

      std::cout << "Fazendo login..." << std::endl << std::endl;

      /// Verifica se o usuario esta cadastrado no sistema com o email e nome fornecidos
      if (ListaUsuario::checkUsuario(&login_email, &login_nome)) { 
        
        std::cout << "Logado com sucesso em: " << login_nome << " (" << login_email << ")!" << std::endl;
        
        return new UsuarioMenu(&login_email);
      }
      else {
        std::cout << "Usuario nao encontrado!" << std::endl << std::endl;
        std::cout << "Ainda nao possui uma conta? Seleciona a opcao 2 para criar um novo cadastro." << std::endl << std::endl;
        
        return new MenuLogin();
      }
    }
    
    case 2: {

      std::string register_email;
      std::cout << "> Insira o seu email: ";
      std::cin >> register_email;

      std::string register_nome;
      std::cout << "> Insira o seu primeiro nome: ";
      std::cin >> register_nome;
      
      std::string register_sobrenome;
      std::cout << "> Insira o seu sobrenome: ";
      std::cin >> register_sobrenome;

      std::string register_idade;
      std::cout << "> Insira a sua idade: ";
      std::cin >> register_idade;

      if (ListaUsuario::checkUsuario(&register_email)) {

        std::cout << "O email informado ja esta cadastrado, favor inserir outro!" << std::endl << std::endl;
        std::cout << "Se deseja acessar a plataforma, selecione a opcao 1." << std::endl << std::endl;

        return new MenuLogin();
      } else {

        std::cout << "Cadastrando usuario..." << std::endl;

        Usuario* new_user = new Usuario(register_nome, register_sobrenome, register_idade, register_email);
        
        ListaUsuario::adicionarUsuario(new_user);

        if (ListaUsuario::checkUsuario(&register_email, &register_nome)) {
          
          std::cout << "Usuario " << register_nome << " (" << register_email << ") cadastrado com sucesso!" << std::endl;
          
          return new UsuarioMenu(&register_email);
        }
        else {

          std::cout << "Nao foi possivel cadastrar o novo usuario!" << std::endl;

          return new MenuLogin();
        }
      }
    }

    case 3: {

      std::cout << "Saindo do programa..." <<  std::endl;
      return nullptr;
    }

    default: {

      std::cout << "Opcao invalida!" << std::endl;
      std::cout << "Escolha uma opcao valida!" << std::endl;
      return new MenuLogin();
    }
  }
}

UsuarioMenu::UsuarioMenu(std::string* user_email) {
  
  setTitulo("Que bom ter voce de volta, " + *user_email + "!");
  setSubtitulo("Calendario da semana:");
  setOpcoes({"1 --> Lembretes", "2 --> Compromissos", "3 --> Tarefas", "4 --> Deslogar", "5 --> Sair"});
  setUsuario(*user_email);

  Calendario user_calendario;

  // Pega a data atual do computador do usuario
  std::time_t t = std::time(nullptr);
  std::tm* now = std::localtime(&t);

  // Transforma em uma string no formato: DD/MM/AAAA
  std::string dia = STRING(now->tm_mday);
  dia += '/';
  dia += STRING(now->tm_mon + 1);
  dia += '/';
  dia += STRING(now->tm_year + 1900);

  user_calendario.imprimirCalendario(dia); ///< Imprimindo o calendario da semana
}

PrimeiroMenu *UsuarioMenu::next(unsigned option, PrimeiroMenu *old_menu) {

  std::string usuario_atual = getUsuario();

  switch (option) {
    case 1: {

      std::cout << std::endl << "Aqui estao seus lembretes salvos: " << std::endl; 
      
      ImprimirLembretes::verLembretes(&usuario_atual);
      
      return new LembreteMenu(&usuario_atual);
    }

    case 2: {

      std::cout << std::endl << "Aqui estao seus compromissos salvos: " << std::endl;
      
      ImprimirCompromissos::verCompromissos(&usuario_atual);
      
      return new CompromissoMenu(&usuario_atual);
    }

    case 3: {

      std::cout << std::endl << "Aqui estao suas tarefas salvas: " << std::endl;
      
      ImprimirTarefas::verTarefas(&usuario_atual);

      return new TarefaMenu(&usuario_atual);
    }

    case 4: {
      
      std::cout << "Voltando..." << std::endl;
      return old_menu;
    }

    case 5: {
      
      std::cout << "Saindo do progama..." << std::endl;
      return nullptr;
    }

    default: {

      std::cout << "Opcao invalida!" << std::endl;
      std::cout << "Escolha uma opcao valida!" << std::endl;
      return new UsuarioMenu(&usuario_atual);
    }
  }
}
 
TarefaMenu::TarefaMenu(std::string *login_email) {

  setTitulo("Menu de Tarefas! ");
  setSubtitulo("Escolha uma opçao:");
  setOpcoes({"1 --> Adicionar um nova Tarefa", "2 --> Remover um Tarefa", "3 --> Editar uma Tarefa", "4 --> Voltar", "5 --> Sair"});
  setUsuario(*login_email);
}

PrimeiroMenu *TarefaMenu::next(unsigned option, PrimeiroMenu *old_menu) {
  
    std::string usuario_atual = getUsuario();

  switch (option) {
    
    case 1: {
        
        std::string nova_tarefa_titulo;
        std::cout << "Insira um titulo para sua Tarefa" << std::endl;
        std::cin >> nova_tarefa_titulo;

        std::string nova_tarefa_descricao;
        std::cout << "Insira uma descricao para sua Tarefa" << std::endl;
        std::cin >> nova_tarefa_descricao;

        std::string nova_tarefa_data;
        std::cout << "Insira uma data para sua Tarefa no formato DD/MM/AAA" << std::endl;
        std::cin >> nova_tarefa_data;

        unsigned nova_tarefa_prioridade;
        std::cout << "Insira uma prioridade para sua Tarefa: " << std::endl;
        std::cout << "1 --> menos importante, 2 --> importante, 3 --> muito importante" << std::endl;
        std::cin >> nova_tarefa_prioridade;

        std::string nova_tarefa_estado;
        std::cout << "Insira um estado para sua Tarefa: " << std::endl;
        std::cout << "feito , em progresso, não feito " << std::endl;
        std::cin >> nova_tarefa_estado;
        
        std::cout << "Adicionando Tarefa..." << std::endl;

        Tarefa* new_Tarefa = new Tarefa(nova_tarefa_titulo, nova_tarefa_descricao, nova_tarefa_data, nova_tarefa_prioridade, nova_tarefa_estado );

        ListaTarefa::adicionarTarefa(new_Tarefa, &usuario_atual);

        // não achei uma função dessa para Tarefa
        if (ListaTarefa::buscarTarefa(nova_tarefa_titulo) != nullptr) {

            std::cout << "A Tarefa adicionada com sucesso!" << std::endl;
        }
        else {

            std::cout << "Nao foi possivel adicionar A nova Tarefa." << std::endl;
        }
        
        return new TarefaMenu(&usuario_atual);
    }
    case 2: {

        std::string titulo_Tarefa;
        std::cout << std::endl << "Digite o titulo da Tarefa que deseja remover: " << std::endl;
        std::cin >> titulo_Tarefa;

        std::cout << "Buscando pela Tarefa..." << std::endl;
        
        //precisa criar a função a baixo
        Tarefa* tarefa = ListaTarefa::buscarTarefa(titulo_Tarefa);

        if (tarefa != nullptr) {

            ListaTarefa::removerTarefa(tarefa, &usuario_atual); ///< Removendo a Tarefa

            std::cout << "A Tarefa com Titulo '" << titulo_Tarefa << "' foi removida com sucesso!" << std::endl;
        }
        else {

            std::cout << "A Tarefa com Titulo '" << titulo_Tarefa << "' nao foi encontrada." << std::endl;
        }

        return new TarefaMenu(&usuario_atual);
    }
    case 3: {

        std::string titulo_Tarefa;
        std::cout << std::endl << "Digite o titulo da Tarefa que deseja editar: " << std::endl;
        std::cin >> titulo_Tarefa;

        std::cout << "Buscando pela Tarefa..." << std::endl;
        
        Tarefa* tarefa = ListaTarefa::buscarTarefa(titulo_Tarefa);

        if (tarefa != nullptr) {

            std::cout << "Alterando a Tarefa..." << std::endl
            << "Titulo: " << tarefa->getTitulo() << std::endl
            << "Descricao: " << tarefa->getDescricao() << std::endl
            << "Data: " << tarefa->getData() << std::endl
            << "Prioridade: " << tarefa->getPrioridade() << std::endl
            << "Estado: " << tarefa->getEstado() << std::endl;
            
            std::cout << std::endl << "Voce deseja..." << std::endl
            << "1 --> Editar Titulo" << std::endl
            << "2 --> Editar Descricao" << std::endl
            << "3 --> Editar Data" << std::endl
            << "4 --> Editar Prioridade" << std::endl
            << "5 --> Editar Estado" << std::endl;

            unsigned opcao_editar;

            switch (opcao_editar) {
                case 1: {

                    std::string novo_titulo;
                    std::cout << "Digite um novo Titulo pata a Tarefa:" << std::endl;
                    std::cin >> novo_titulo;

                    std::cout << "Alterando Titulo...";

                    tarefa->setTitulo(novo_titulo);

                    Tarefa* tarefa_alterado = ListaTarefa::buscarTarefa(novo_titulo);  

                    if (tarefa_alterado != nullptr && tarefa_alterado->getData() == tarefa->getData() && tarefa_alterado->getDescricao() == tarefa->getDescricao()) {

                        std::cout << "O Titulo da tarefa foi alterado com sucesso para: " << tarefa->getTitulo() << "!" << std::endl;
                    }
                    else {

                        std::cout << "Nao foi possivel alterar o Titulo da tarefa." << std::endl;
                    }
                }
                case 3: {

                    std::string nova_data;
                    std::cout << "Digite uma nova data para a tarefa (no formato: DD/MM/AAAA):" << std::endl;
                    std::cin >> nova_data;

                    std::cout << "Alterando data...";

                    tarefa->setData(nova_data);  

                    if (tarefa->getData() == nova_data) {

                        std::cout << "A data da tarefa foi alterada com sucesso para: " << tarefa->getData() << "!" << std::endl;
                    }
                    else {

                        std::cout << "Nao foi possivel alterar a data da tarefa." << std::endl;
                    }
                }
                case 2: {

                    std::string novo_descricao;
                    std::cout << "Digite uma nova Descricao pata a Tarefa:" << std::endl;
                    std::cin >> novo_descricao;

                    std::cout << "Alterando Descricao...";

                    tarefa->setDescricao(novo_descricao);  

                    if (tarefa->getDescricao() == novo_descricao) {

                        std::cout << "A Descricao da tarefa foi alterada com sucesso para: " << tarefa->getDescricao() << "!" << std::endl;
                    }
                    else {

                        std::cout << "Nao foi possivel alterar a Descricao da tarefa." << std::endl;
                    }
                }

                case 4: { 
                    unsigned nova_prioridade;
                    std::cout << "Digite a nova prioridade da tarefa entre:" << std::endl;
                    std::cout << "'1 --> menos importante, 2 --> importante, 3 --> muito importante'" << std:: endl;
                    std::cin >> nova_prioridade;

                    std::cout << "Alterando prioridade...";

                    tarefa->setPrioridade(nova_prioridade);  

                    if (tarefa->getPrioridade() == nova_prioridade) {
                     
                     std::cout << "A prioridade da tarefa foi alterada com sucesso para: " << tarefa->getPrioridade() << "!" << std::endl;
                    
                    }
                    else {

                        std::cout << "Nao foi possivel alterar a prioridade da tarefa." << std::endl;
                    }
                }

                case 5: { 
                    std::string nova_estado;
                    std::cout << "Digite uma novo estado para a tarefa entre : " << std::endl;
                    std::cout << "'feito , em progresso, não feito' " << std::endl;
                    std::cin >> nova_estado;

                    std::cout << "Alterando estado...";

                    tarefa->setEstado(nova_estado);
 

                    if (tarefa->getEstado() == nova_estado) {

                        std::cout << "O esatado da tarefa foi alterado com sucesso para: " << tarefa->getEstado() << "!" << std::endl;
                    }
                    else {

                        std::cout << "Nao foi possivel alterar o estado da tarefa." << std::endl;
                    }
                }
            } 
        }
        else {

            std::cout << "A tarefa com Titulo '" << titulo_Tarefa << "' nao foi encontrada." << std::endl;
        }

        return new TarefaMenu(&usuario_atual);
    }
    case 4: {

        std::cout << "Voltando..." << std::endl;
        return old_menu;
    }
    
    case 5: {
      
      std::cout << "Saindo do progama..." << std::endl;
      return nullptr;
    }

    default: {
        
        std::cout << "Opcao invalida!" << std::endl;
        std::cout << "Escolha uma opcao valida!" << std::endl;
        return new TarefaMenu(&usuario_atual);
    }
  }
}

CompromissoMenu::CompromissoMenu(std::string *login_email) {
    
    setTitulo("Menu de Compromissos");
    setSubtitulo("Escolha uma opção:");
    setOpcoes({"1 --> Adicionar novo Compromisso", "2 --> Remover Compromisso", "5 --> Editar Compromisso " "4 --> Voltar", "5 --> Sair"});
    setUsuario(*login_email);
}

PrimeiroMenu *CompromissoMenu::next(unsigned option, PrimeiroMenu *old_menu) {
    
    std::string usuario_atual = getUsuario();

    switch (option) {
        case 1: {

            std::string nova_compromisso_titulo;
            std::cout << "Insira um titulo para seu Compromisso" << std::endl;
            std::cin >> nova_compromisso_titulo;

            std::string nova_compromisso_descricao;
            std::cout << "Insira uma descricao para seu Compromisso" << std::endl;
            std::cin >> nova_compromisso_descricao;

            std::string nova_compromisso_data;
            std::cout << "Insira uma data para seu compromisso no formato DD/MM/AAA" << std::endl;
            std::cin >> nova_compromisso_data;

            unsigned nova_compromisso_prioridade;
            std::cout << "Insira uma prioridade para sua compromisso: " << std::endl;
            std::cout << "1 --> menos importante, 2 --> importante, 3 --> muito importante" << std::endl;
            std::cin >> nova_compromisso_prioridade;

            std::string nova_compromisso_estado;
            std::cout << "Insira um estado para sua compromisso: " << std::endl;
            std::cout << "feito , em progresso, não feito " << std::endl;
            std::cin >> nova_compromisso_estado;

            std::string nova_compromisso_local;
            std::cout << "Insira um local para seu compromisso: " << std::endl;
            std::cin >> nova_compromisso_local;

            std::string nova_compromisso_horario;
            std::cout << "Insira um horario para seu compromisso no formato HH:MM:SS : " << std::endl;
            std::cin >> nova_compromisso_horario;
            
            std::cout << "Adicionando compromisso..." << std::endl;

            Compromisso* new_compromisso = new Compromisso(nova_compromisso_data, nova_compromisso_local, nova_compromisso_titulo, nova_compromisso_descricao, nova_compromisso_horario, nova_compromisso_estado,  nova_compromisso_prioridade );

            ListaCompromisso::adicionarCompromisso(new_compromisso, &usuario_atual);

        // não achei uma função dessa para compromisso
            if (ListaCompromisso::buscarCompromisso(nova_compromisso_titulo) != nullptr) {

                std::cout << "A compromisso adicionada com sucesso!" << std::endl;
            }
            else {

                std::cout << "Nao foi possivel adicionar A nova compromisso." << std::endl;
            }

            return new CompromissoMenu(&usuario_atual);
        }
        case 2: {
       
            std::string titulo_Compromisso;
            std::cout << std::endl << "Digite o titulo da compromisso que deseja remover: " << std::endl;
            std::cin >> titulo_Compromisso;

            std::cout << "Buscando pelo Compromisso..." << std::endl;
            
            //precisa criar a função a baixo
            Compromisso* compromisso = ListaCompromisso::buscarCompromisso(titulo_Compromisso);

            if (compromisso != nullptr) {
                
                ListaCompromisso::removerCompromisso(compromisso, &usuario_atual); ///< Removendo a compromisso

                std::cout << "A compromisso com Titulo '" << titulo_Compromisso << "' foi removido com sucesso!" << std::endl;
            }
            else {

                std::cout << "A compromisso com Titulo '" << titulo_Compromisso << "' nao foi encontrado." << std::endl;
            }

                return new CompromissoMenu(&usuario_atual);
            }

        case 3: {

            std::string titulo_compromisso;
            std::cout << std::endl << "Digite o titulo do Compromisso que deseja editar: " << std::endl;
            std::cin >> titulo_compromisso;

            std::cout << "Buscando pela compromisso..." << std::endl;
            
            Compromisso* compromisso = ListaCompromisso::buscarCompromisso(titulo_compromisso);

            if (compromisso != nullptr) {

                std::cout << "Alterando o compromisso..." << std::endl
                << "Titulo: " << compromisso->getTitulo() << std::endl
                << "Descricao: " << compromisso->getDescricao() << std::endl
                << "Data: " << compromisso->getData() << std::endl
                << "Prioridade: " << compromisso->getPrioridade() << std::endl
                << "Estado: " << compromisso->getEstado() << std::endl
                << "Local: " << compromisso->getLocal() << std::endl
                << "horario: " << compromisso->getHorario() << std::endl;
                
                std::cout << std::endl << "Voce deseja..." << std::endl
                << "1 --> Editar Titulo" << std::endl
                << "2 --> Editar Descricao" << std::endl
                << "3 --> Editar Data" << std::endl
                << "4 --> Editar Prioridade" << std::endl
                << "5 --> Editar Estado"<< std::endl
                << "6 --> Editar Local"<< std::endl
                << "7 --> Editar horario"<< std::endl;

                unsigned opcao_editar;

                switch (opcao_editar) {
                    case 1: {

                        std::string novo_titulo;
                        std::cout << "Digite um novo Titulo pata a compromisso:" << std::endl;
                        std::cin >> novo_titulo;

                        std::cout << "Alterando Titulo...";

                        compromisso->setTitulo(novo_titulo);

                        Compromisso* compromisso_alterado = ListaCompromisso::buscarCompromisso(novo_titulo);  

                        if (compromisso_alterado != nullptr && compromisso_alterado->getData() == compromisso->getData() && compromisso_alterado->getDescricao() == compromisso->getDescricao()) {

                            std::cout << "O Titulo do Compromisso foi alterado com sucesso para: " << compromisso->getTitulo() << "!" << std::endl;
                        }
                        else {

                            std::cout << "Nao foi possivel alterar o Titulo do compromisso." << std::endl;
                        }
                    }
                    
                    case 2: {

                        std::string novo_descricao;
                        std::cout << "Digite uma nova Descricao para o compromisso:" << std::endl;
                        std::cin >> novo_descricao;

                        std::cout << "Alterando Descricao...";

                        compromisso->setDescricao(novo_descricao);  

                        if (compromisso->getDescricao() == novo_descricao) {

                            std::cout << "A Descricao da compromisso foi alterada com sucesso para: " << compromisso->getDescricao() << "!" << std::endl;
                        }
                        else {

                            std::cout << "Nao foi possivel alterar a Descricao do compromisso." << std::endl;
                        }
                    }

                    case 3: {

                        std::string nova_data;
                        std::cout << "Digite uma nova data para o compromisso (no formato: DD/MM/AAAA):" << std::endl;
                        std::cin >> nova_data;

                        std::cout << "Alterando data...";

                        compromisso->setData(nova_data);  

                        if (compromisso->getData() == nova_data) {

                            std::cout << "A data do compromisso foi alterada com sucesso para: " << compromisso->getData() << "!" << std::endl;
                        }
                        else {

                            std::cout << "Nao foi possivel alterar a data do compromisso." << std::endl;
                        }
                    }

                    case 4: { 

                        unsigned nova_prioridade;
                        std::cout << "Digite a nova prioridade do compromisso entre:" << std::endl;
                        std::cout << "'1 --> menos importante, 2 --> importante, 3 --> muito importante'" << std:: endl;
                        std::cin >> nova_prioridade;

                        std::cout << "Alterando prioridade...";

                        compromisso->setPrioridade(nova_prioridade);  

                        if (compromisso->getPrioridade() == nova_prioridade) {
                        
                        std::cout << "A prioridade do compromisso foi alterada com sucesso para: " << compromisso->getPrioridade() << "!" << std::endl;
                        
                        }
                        else {

                            std::cout << "Nao foi possivel alterar a prioridade do compromisso." << std::endl;
                        }
                    }

                    case 5: { 

                        std::string nova_estado;
                        std::cout << "Digite uma novo estado para o compromisso entre : " << std::endl;
                        std::cout << "'feito , em progresso, não feito' " << std::endl;
                        std::cin >> nova_estado;

                        std::cout << "Alterando estado...";

                        compromisso->setEstado(nova_estado);
    

                        if (compromisso->getEstado() == nova_estado) {

                            std::cout << "O esatado do compromisso foi alterado com sucesso para: " << compromisso->getEstado() << "!" << std::endl;
                        }
                        else {

                            std::cout << "Nao foi possivel alterar o estado do compromisso." << std::endl;
                        }
                    }
                    case 6: {

                        std::string novo_local;
                        std::cout << "Digite um novo Local para o compromisso:" << std::endl;
                        std::cin >> novo_local;

                        std::cout << "Alterando Local...";

                        compromisso->setLocal(novo_local);  

                        if (compromisso->getLocal() == novo_local) {

                            std::cout << "O Local do compromisso foi alterada com sucesso para: " << compromisso->getLocal() << "!" << std::endl;
                        }
                        else {

                            std::cout << "Nao foi possivel alterar o Local do compromisso." << std::endl;
                        }

                    }

                    case 7: {

                        std::string nova_horario;
                        std::cout << "Digite um novo horario para o compromisso (no formato: HH:MM:SS):" << std::endl;
                        std::cin >> nova_horario;

                        std::cout << "Alterando horario...";

                        compromisso->setHorario(nova_horario);  

                        if (compromisso->getHorario() == nova_horario) {

                            std::cout << "O horario do compromisso foi alterada com sucesso para: " << compromisso->getHorario() << "!" << std::endl;
                        }
                        else {

                            std::cout << "Nao foi possivel alterar o horario do compromisso." << std::endl;
                        }

                    }

                } 
            }
            else {

                std::cout << "O compromisso com Titulo '" << titulo_compromisso << "' nao foi encontrado." << std::endl;
            }

                return new CompromissoMenu(&usuario_atual);
            }

        case 4: {

            std::cout << "Voltando..." << std::endl;
            return old_menu;
        }

        case 5: {
      
            std::cout << "Saindo do progama..." << std::endl;
            return nullptr;
        }
        
        default: {

            std::cout << "Opcao invalida!" << std::endl;
            std::cout << "Escolha uma opcao valida!" << std::endl;
            return new CompromissoMenu(&usuario_atual);
        }
    }
}

LembreteMenu::LembreteMenu(std::string* user_email) {
  
  setTitulo("Menu de Lembretes! ");
  setSubtitulo("Escolha uma opçao:");
  setOpcoes({"1 --> Adicionar um novo lembrete", "2 --> Remover um lembrete", "3 --> Editar um lembrete", "4 --> Voltar", "5 --> Sair"});
  setUsuario(*user_email);
}

PrimeiroMenu *LembreteMenu::next(unsigned option, PrimeiroMenu *old_menu) {

    std::string usuario_atual = getUsuario();
  
  switch (option) {
    case 1: {

        std::string novo_lembrete_data;
        std::cout << "Insira uma data para seu lembrete" << std::endl;
        std::cin >> novo_lembrete_data;

        std::string novo_lembrete_horario;
        std::cout << "Insira um horario para seu lembrete" << std::endl;
        std::cin >> novo_lembrete_horario;

        std::string novo_lembrete_mensagem;
        std::cout << "Insira uma mensagem para seu lembrete" << std::endl;
        std::cin >> novo_lembrete_mensagem;

        std::cout << "Adicionando lembrete..." << std::endl;

        Lembrete* new_lembrete = new Lembrete(novo_lembrete_horario, novo_lembrete_mensagem, novo_lembrete_data);

        ListaLembrete::adicionarLembrete(new_lembrete, &usuario_atual);

        if (ListaLembrete::buscarLembrete(&novo_lembrete_mensagem) != nullptr) {

            std::cout << "O lembrete foi adicionado com sucesso!" << std::endl;
        }
        else {

            std::cout << "Nao foi possivel adicionar o novo lembrete." << std::endl;
        }
        
        return new LembreteMenu(&usuario_atual);
    }
    case 2: {

        std::string mensagem_lembrete;
        std::cout << std::endl << "Digite a mensagem do lembrete que deseja remover: " << std::endl;
        std::cin >> mensagem_lembrete;

        std::cout << "Buscando por lembrete..." << std::endl;
        
        Lembrete* lembrete = ListaLembrete::buscarLembrete(&mensagem_lembrete);

        if (lembrete != nullptr) {

            ListaLembrete::removerLembrete(lembrete, &usuario_atual); ///< Removendo o lembrete

            std::cout << "O lembrete com mensagem '" << mensagem_lembrete << "' foi removido com sucesso!" << std::endl;
        }
        else {

            std::cout << "O lembrete com mensagem '" << mensagem_lembrete << "' nao foi encontrado." << std::endl;
        }

        return new LembreteMenu(&usuario_atual);
    }
    case 3: {

        std::string mensagem_lembrete;
        std::cout << std::endl << "Digite a mensagem do lembrete que deseja editar: " << std::endl;
        std::cin >> mensagem_lembrete;

        std::cout << "Buscando por lembrete..." << std::endl;
        
        Lembrete* lembrete = ListaLembrete::buscarLembrete(&mensagem_lembrete);

        if (lembrete != nullptr) {

            std::cout << "Alterando o lembrete..." << std::endl
            << "Mensagem: " << lembrete->getMensagem() << std::endl
            << "Data: " << lembrete->getData() << std::endl
            << "Horario: " << lembrete->getHorario() << std::endl;
            
            std::cout << std::endl << "Voce deseja..." << std::endl
            << "1 --> Editar mensagem" << std::endl
            << "2 --> Editar data" << std::endl
            << "3 --> Editar horario" << std::endl;

            unsigned opcao_editar;

            switch (opcao_editar) {
                case 1: {

                    std::string nova_mensagem;
                    std::cout << "Digite uma nova mensagem para o lembrete:" << std::endl;
                    std::cin >> nova_mensagem;

                    std::cout << "Alterando mensagem...";

                    lembrete->setMensagem(nova_mensagem);

                    Lembrete* lembrete_alterado = ListaLembrete::buscarLembrete(&nova_mensagem);  

                    if (lembrete_alterado != nullptr && lembrete_alterado->getData() == lembrete->getData() && lembrete_alterado->getHorario() == lembrete->getHorario()) {

                        std::cout << "A mensagem do lembrete foi alterada com sucesso para: " << lembrete->getMensagem() << "!" << std::endl;
                    }
                    else {

                        std::cout << "Nao foi possivel alterar a mensagem do lembrete." << std::endl;
                    }
                }
                case 2: {

                    std::string nova_data;
                    std::cout << "Digite uma nova data para o lembrete (no formato: DD/MM/AAAA):" << std::endl;
                    std::cin >> nova_data;

                    std::cout << "Alterando data...";

                    lembrete->setData(nova_data);  

                    if (lembrete->getData() == nova_data) {

                        std::cout << "A data do lembrete foi alterada com sucesso para: " << lembrete->getData() << "!" << std::endl;
                    }
                    else {

                        std::cout << "Nao foi possivel alterar a data do lembrete." << std::endl;
                    }
                }
                case 3: {

                    std::string novo_horario;
                    std::cout << "Digite um novo horario para o lembrete (no formato: HH:MM:SS):" << std::endl;
                    std::cin >> novo_horario;

                    std::cout << "Alterando horario...";

                    lembrete->setHorario(novo_horario);  

                    if (lembrete->getHorario() == novo_horario) {

                        std::cout << "O horario do lembrete foi alterado com sucesso para: " << lembrete->getHorario() << "!" << std::endl;
                    }
                    else {

                        std::cout << "Nao foi possivel alterar o horario do lembrete." << std::endl;
                    }
                }
            } 
        }
        else {

            std::cout << "O lembrete com mensagem '" << mensagem_lembrete << "' nao foi encontrado." << std::endl;
        }

        return new LembreteMenu(&usuario_atual);
    }
    case 4: {

        std::cout << "Voltando..." << std::endl;
        return old_menu;
    }
    
    case 5: {
      
      std::cout << "Saindo do progama..." << std::endl;
      return nullptr;
    }

    default: {
        
        std::cout << "Opcao invalida!" << std::endl;
        std::cout << "Escolha uma opcao valida!" << std::endl;
        return new LembreteMenu(&usuario_atual);
    }
  }
}



