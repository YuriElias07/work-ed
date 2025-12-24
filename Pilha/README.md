1️⃣ Descrição: 
  Este projeto é um jogo na linguagem C que que utiliza a estrutura de dados Pilha como lógica de funcionamento. O objetivo é demonstrar conhecimento no manejo das funções que a estrutura pede.

2️⃣ Como funciona o jogo:
  Sendo inspirado no famoso jogo GuitarHero, o codigo simula uma interface com 4 posições clicáveis, a que aparecer no momento devemos clicar com as teclas de 1 a 4. Se acertarmos, o código muda a tecla e avança na sequência aleatória de posições, se errarmos, perdemos uma vida. Quando ela se esgota, perdermos. Também é possível visualizar nossa pontuação em tempo real e escolher entre 3 dificuldades diferentes com cada uma tendo um tempo limite para apertar alguma tecla, se não for apertada uma vida também é perdida.

3️⃣ Demonstração:


4️⃣ Como a pilha foi usada:
  Ao selecionar uma dificuldade, uma pilha é criada usando alocação dinâmica. A quantidade de nós depende da dificulade selecionada e em cada nó existe um número de 0 a 3 para indicar as posições/teclas de 1 a 4 e um ponteiro para o próximo nó. Após ser criada, ela é consumida aos poucos usando a função pop a cada iteração do loop presente no jogo. Dessa forma é feito um uso completo de todas as funções da estrutura de dados Pilha: 
* Criada no início do jogo
* Consumida quando acertamos ou erramos a posição
* Tem o topo analisado
* Destruída quando o jogo acaba.

5️⃣ Estrutura do projeto

📦 jogo-pilha
 ┣ 📜 main.c        → Arquivo principal do jogo
 ┣ 📜 pilha.h       → Definição da estrutura Pilha e protótipos
 ┣ 📜 pilha.c       → Implementação das operações da pilha
 ┣ 📜 receptTimer.c → Lógica da recepção das teclas
 ┣ 📜 receptTimer.h → Protótipo 
 ┗ 📜 README.md     → Documentação do projeto

6️⃣ Como compilar e executar

  Compile usando o GCC:
    "gcc main.c pilha.c receptTimer.c -o jogo"
  Execute: 
    ./jogo
  No Windows, utilize jogo.exe
  
7️⃣ Possíveis melhorias
  - Salvamento de pontuação
  - Implementação de sons e cores
  - Sistema de seleção de músicas pré-definidas
