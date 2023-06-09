# Jacktunadoversaolabirinto
<br>Esta é a segunda atividade da matéria Algoritmos e Estrutura de Dados I(AEDIS I), foi proposto a construção de um algoritmo que conseguisse ler n matrizes de um arquivo e interliga-las fazendo dessa forma um minigame, porém ele seria aleatório, sendo assim, não é possível controlar para onde o algoritmo andaria.</br><br> Alguns dados foram dados, o jogador começaria com 10 de vida e com sua mochila totalmente vazia, quando ele achasse 4 itens que são representados por números na matriz, quando ele pega um item automaticamente o número onde ele pegou o item é subtraido por 1 e ele continua a andar, caso ele encontrasse um * ele teria sua vida diminuida em 1, e caso uma parede fosse encontrada ele não poderia ultrapassa-la e teria que voltar.</br><br> Foram propostas duas condições de parada, uma caso sua vida chegasse a zero então ele estaria morto e a execução seria interrompida, e caso ele andasse por todas as matrizes em seu caminho aleatório e voltasse para seu ponto de partida e não achasse nenhum item, então ele simplesmente desistiria e saíria do labirinto por ele entrou.</br>
# Lógica usada
<br>Durante a produção do algoritmo, foi usado como base um prédio, onde o personagem começa no ultimo andar e tem que descer andar por andar, quando ele fosse descer um andar haveria uma escada, caso ele encontrasse um # quando fosse descer a escada era considerado como se houvesse algo bloqueando sua descida, então ele simplesmente voltaria e tentaria encontrar outro caminho para o proximo andar, quando ele estivesse no último andar ele encontraria um elevador que o voltaria diretamente para o primeiro para que ele continuasse sua aventura pelo labirinto.</br>
<div align="center">
<img src="https://user-images.githubusercontent.com/115949326/231914702-469b6094-4150-4b30-abfe-f636e2e0de88.png" width=250px></img>
</div>

<br> Durante sua jornada ele encontraria diversos perigos, e teria que lutar contra eles, quando ele lutasse ele se machucaria um pouco ou estaria cansado da batalha por isso sua vida é diminuida em 1.</br>
<div align="center">
<img src="https://user-images.githubusercontent.com/115949326/231917174-0be86c3c-6e2e-42ec-be3f-217c689d6a42.png" width=250px></img>
<img src="https://user-images.githubusercontent.com/115949326/231917684-378a7f02-0465-49c5-bb9d-c6ee5060ab9e.png" width=250px></img>
<img src="https://user-images.githubusercontent.com/115949326/231918262-b151ead4-1553-4f6c-979b-7375db0cb58d.png" width=250px></img>
</div>

<br > Neste caso, foi verificado se o player poderia ir para a sua direita, quando foi retornado que sim ele foi e tomou 1 de dano, pois encontrou um perigo</br>

<br> Como citado acima, para o caminhamento ser realizado é necessário uma verificação, e confirmação, para isso foi usado um método de sombra, em que a posição para a qual ele quer ir seja verificada, e caso seja válida a sombra se torna o player.</br>
<div align="center">
<img src="https://user-images.githubusercontent.com/115949326/231920298-4f62f941-d1b2-443f-86dc-4e35d0fa810b.png" width=250px></img>
<img src="https://user-images.githubusercontent.com/115949326/231920645-83dc12f9-0200-4b38-b22f-7a97c6aab319.png" width=250px></img>
</div>
<br>Nesse caso, ele tentou ir para o lugar em que a sombra dele estava, porém, aquele lugar era uma parede então foi retornado uma resposta negativa para ele, dizendo para procurar outro caminho.</br>

# Exemplo de input e output:
<div align="center"><img src="https://user-images.githubusercontent.com/115949326/233801188-bce37403-13a3-41d0-8763-2f43c216e8f3.png" width=150px></img>
<img src="https://user-images.githubusercontent.com/115949326/233801266-cd0ac111-6ffa-4aed-b444-7bd64e2440f8.png" width=144px></img>
</div>

# Funcionamento
<br> Agora quanto ao funcionamento, foi feito de forma que possam ser jogadas matrizes de grandes portes, pois ele lê uma por uma e depois salva em um arquivo que será criado durante a execução do código, quando ele precisa verificar se poderá passar de matriz, é chamada uma matriz auxiliar para que seja possivel verificar sem mudar o arquivo em que está a matriz atual, se for possivel, tal função retornará positivo para a conferência, caso contrário negativo, e o arquivo onde está a matriz atual permanecerá o mesmo.</br>
# Funções
- lendolabirinto(): Essa função tem como objetivo ler o arquivo que contêm os dados das matrizes e passar um por um para a matriz de duas dimensões, nesta função será chamada outra função para a confecção dos arquivos de cada matriz. E após isso será chamada a próxima função a andando()
- andando(): Esta função é uma das principais do código, ela se inicia mandando os dados do primeiro arquivo para a matriz de duas dimensões para que se inicie o caminhamento, com isso é perguntado em qual posição o usuário deseja começar o minigame, caso ele escolha um # ele será forçado a escolher outra posição que não seja esta, por outro lado caso ele escolha * ele não receberá dano até sair do local, assim que ele sair ele já estará vulnerável à qualquer outro que encontrar pelo seu caminho. Nesta função ainda é feito as condicionais para que ele continue ou pare a sua aventura pelo labirinto, por exemplo caso sua vida chegue a zero, o programa será encerrado na mesma hora e serão printadas todas as informações, e o arquivo de saída será atualizado, caso ele ache itens ou perca vida essa função também terá as condicionais necessárias para fazer os tratamentos destes casos. Ainda nela, o número que indicará para onde ele andará será randomizado de 0 a 7, cada um representando uma das posições cardiais, 0- leste; 1- Sudeste;2-Sul;3-Sudoeste;4- Oeste;5-Noroeste; 6-Norte; 7-Nordeste. 
- consertandobugs(): Esta função recebe a string da projeção da posição, e tem como objetivo evitar que código tente subtrair 1 de um # ou * pois isso ocasionária em um erro, está função serve somente para comparação, e funciona desta forma: Caso a posição não seja um * ele entrará em outra condicional que comparará novamente, se ele não for um # então ele passará pelas duas condicionais e a função retornará 1 permitindo o uso do dado naquela posição para a operação.
- naoehperigo(): Está função é muito parecida com a anterior, ela também recebe uma string da projeção da posição do player, mas é usada em outros lugares, pois nem sempre necessito de que o dado não seja nenhum dos dois, mas funciona simplesmente pelo fato entrar na função e como o nome já diz se não for perigo retornará 1 e perimitirá a entrada em alguma condicional, caso contrário retorna 0.
- ehparede(): Esta função é a mesma coisa que a anterior, muda somente o fato de que quando retorna 1 quer dizer que é uma parede e 0 não é.
- andando2(): Esta função é onde o player passa pelos andares do labirinto, ela funciona de forma que caso ele tente quebrar o limite das matrizes ele seja enviado para esta função, quando enviado para esta função uma matriz auxiliar receberá os dados do arquivo da respectiva profundidade, à partir disso, são feitas as comparações para que haja o movimento do personagem, caso a posição para a qual ele irá seja uma #, ele simplesmente não irá e tentará achar um outro caminho, caso contrário as especificações do caminhamento serão executadas. No caso em que ele troca de andar serão feitas algumas alterações importantes para o funcionamento do código, primeiramente ele salvará todas as informações obtidas no arquivo da profundidade na qual ele estava e após isso ele mudará para o arquivo da profundidade para a qual ele está se movendo, feito esse processo ele pegara todos os dados que estão na matriz do arquivo e continuará até que uma das condições de parada sejam atingidas.
- andando3(): Esta função é o caso do caminhamento normal, onde ele não esta quebrando nenhum limite da matriz atual, ele funciona de maneira simples e só executará as funções do caminhamento, caso ele consiga caminhar, ela retorna true, e permite o caminhamento, caso contrário ele não irá para a projeção da posição e procurará outro caminho.
- fazendo_arquivos(): Esta função é chamada dentro da função lendolabirinto(), ela recebe o contador de profundidade, e a partir dele ela fará o arquivo da respectiva profundidade e armazenará nele a matriz que está naquele andar, com isso, o código consegue ter o seu funcionamento garantido.
- casasnaovisitadas(): Foi proposto que ao finalizar o código, tivessemos uma forma de mostrar o quanto nosso algoritmo andou, então está função faz a contagem das casas que não foram visitadas pelo algoritmo, ela faz isso pelo fato de que existe um vetor de controle no código, este vetor marca todas as posições já passadas com um "p", e nesta função serão contadas todas as posições que não possuem um p naquela região desconsiderando os #, pois não é possivel caminhas nas paredes.
- verificandosenaoconseguiuandar(): Esta função foi feita para resolver o caso de que o player estivesse preso, com todas as posições à sua volta como parede, funciona com um vetor de booleanos assim que o vetor estiver totalmente true e outra variavél que verifica que ele permaneceu na mesma posição, o programa será encerrados.
# Conclusão
A implementação deste algoritmo foi muito interessante, porém o algoritmo aleatório é muito dificilmente comparável com qualquer outro, por exemplo os algoritmos de busca de largura e profundidade, e ele se torna dificil de analisar assintoticamente, pois ele é aleatório, o que faz com que ele possa ser o melhor caso em um caso tão específico que ele quase se torna impossível. Portanto, ele não se encaixa tão bem na maioria dos casos, mas em casos que você necessita explorar sem saber o que há na sua frente ele pode se igualar à outros algoritmos.

# Compilação e Execução

Esse pequeno exemplo possui um arquivo Makefile que realiza todo o procedimento de compilação e execução. Para tanto, temos as seguintes diretrizes de execução:


| Comando                |  Função                                                                                           |                     
| -----------------------| ------------------------------------------------------------------------------------------------- |
|  `make clean`          | Apaga a última compilação realizada contida na pasta build                                        |
|  `make`                | Executa a compilação do programa utilizando o gcc, e o resultado vai para a pasta build           |
|  `make run`            | Executa o programa da pasta build após a realização da compilação                                 |
