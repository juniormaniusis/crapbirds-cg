ABCg
======

Development framework accompanying the course MCTA008-17 Computer Graphics at [UFABC](https://www.ufabc.edu.br/).

----

### Credits

Developed by Harlen Batagelo.

### License

ABCg is licensed under the MIT License. See [LICENSE](https://github.com/hbatagelo/abcg/blob/main/LICENSE) for more information.

----

### Nomes e RA
* Carlos Maniusis Jr. - RA: 11081816 (Prof. Bruno Marques)
* Melissa Gabriela Pereira da Soledade Perrone - RA: 11072216 (Prof Harlen Batagelo)

### Descrição

Jogo inspirado no estilo de Flappy Bird. O pássaro é o personagem que irá percorrer seu caminho desviando de obstáculos. O objetivo é manter-se longe dos obstáculos (duas barras que ficam nas partes superior e inferior da tela), fazendo o pássaro pular até seu destino. Se ele bater em um dos obstáculos, o jogador perde.
Fizemos os desenhos através do [geogebra](https://www.geogebra.org/calculator) para definir os pontos no código. Desenhamos o pássaro, as nuvens do plano de fundo e os obstáculos com a ferramenta de *segmento de reta* do geogebra. Após desenhar, extraímos os pontos (x,y) que compõem os desenhos. 

### Código

* nuvens.cpp: o desenho das nuvens foi criado no geogebra e extraímos os pontos de seu formato a partir de triângulos. Criamos um *array de nuvens* e uma função que faz com que os desenhos das nuvens sejam escolhidos aleatoriamente (são dois tipos de desenho, eles vão aparecendo durante o jogo). 
* bird.cpp: possui vetor de "positions" do pássaro. As posições são indexadas, reaproveita-se pontos. É definida a estrutura geral do pássaro (posição, cores). Os pontos do pássaro também foram extraídos do geogebra e feitos a partir de triângulos. Para deixar o pássaro dinâmico quando ele está indo para cima (velocidade no eixo y positiva) aumentamos a rotação da sua figura no sentido anti-horário. Analogamente, quando o pássaro vai para baixo, a imagem é rotacionada no sentido horário. Além disso, uma força gravitacional empurra o pássaro para baixo e quando surge uma ação do jogador, a queda é interrompida e é aplicada uma força para cima.
* openglwindow.cpp: detecta o clique do usuário e as colisões entre o pássaro e a tubulação. Também é responsável pelas mensagens de "game over", controle da pontuação do usuário e reiniciar o jogo após passados 5 segundos do game over.
* pipe.cpp: representa a tubulação que impede o pássaro se mover para cima e para baixo (é o "obstáculo"). Fica fixo na tela. 
* main.cpp: arquivo que descreve algumas configurações da janela do jogo.
* gamedata.hpp: definição dos comandos e estado do jogo. São definidas as posições (direita, esquerda, pular), estado (jogando, fim de jogo) e também uma pontuação para o jogador. Quanto mais tempo ele se mantem no jogo, maior sua pontuação.
