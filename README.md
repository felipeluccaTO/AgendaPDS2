# AgendaPDS2
Um projeto de PDS2 dos alunos da UFMG, um gerenciador de tarefas e compromissos!
Esse gerenciador é uma aplicação projetada para ajudar os usuários a organizar suas atividades diárias, seja no ambiente de trabalho, estudo ou vida pessoal.
O objetivo principal desse tipo de projeto é oferecer uma plataforma intuitiva e eficiente para o acompanhamento e planejamento de tarefas e compromissos.

# :hammer: Funcionalidades do projeto
- `Agendamento de Tarefas e Compromissos`: Permite que os usuários criem eventos, compromissos e tarefas em datas e horários específicos.
- `Priorização de Tarefas`: Classifica tarefas com base na sua importância e urgência. 
- `Lembretes`: Emite mensagens para ajudar os usuários a não perder compromissos ou prazos importantes.
- `Outros`: outras funcionalidades serão adicionadas ao longo do projeto.

# Instruções de Compilamento e uso 

> - !Pré-requisitos!:Certifique-se de ter o Make instalado no seu sistema. Tenha um compilador C++ (como o g++) instalado.

>- Via MakeFile:
> Digite os comandos a seguir para uso do Progama:
make (Padrão): Este comando chama automaticamente o alvo all, que, por sua vez, chama build. Ele compila todos os arquivos-fonte e gera o executável na pasta bin
make build: Compila todos os arquivos-fonte e gera o executável na pasta bin
make run: Compila e executa o programa.
make test: Compila e executa testes (substitua pela lógica específica do seu projeto).
make clean: Remove os diretórios build e bin, limpando os arquivos gerados.

> - Via MINGW: Você pode compilar manualmente usando código 'g++ -Iinclude/core -Iinclude/menu src/core/Calendario.cpp src/core/Excecoes.cpp src/core/Lembrete.cpp src/core/Notificacao.cpp src/core/Tarefa.cpp src/core/Usuario.cpp src/menu/Menu.cpp main.cpp -o progama.exe' e './progama.exe' no terminal de comando
>
> - Via PROGAMA.bat: Caso deseje basta clicar no arquivo arquivo PROGAMA.bat e o arquivo compilará e execultará automaticamente


# Autores (Grupo 5)
`Felipe Lucca Taumaturgo de Oliveira`
`Samuel Lima Horta`
`Thiago Tobias Valente de Oliveira Santos`
`Roberto Júnior Cassimiro Campolina`
`Daniel Bozi Portes`
