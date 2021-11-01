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

Jogo inspirado no estilo de Flappy Bird. O pássaro é o personagem que irá percorrer seu caminho desviando de obstáculos. O objetivo é manter-se longe dos obstáculos (duas barras que ficam na parte superior e inferior da tela), fazendo o pássaro pular até seu destino. Se ele bater em um dos obstáculos, o jogador perde.
Fizemos os desenhos através do [geogebra](https://www.geogebra.org/calculator) para definir os pontos no código. Desenhamos o pássaro, as nuvens do plano de fundo e os obstáculos com a ferramenta de *segmento de reta* do geogebra. Após desenhar, extraímos os pontos (x,y) que compõem os desenhos. 

### Código

* nuvens.cpp: o desenho das nuvens foi criado no geogebra e extraímos os pontos de seu formato. Criamos um *array de nuvens* e uma função que faz com que os desenhos das nuvens sejam escolhidos aleatoriamente (são dois tipos de desenho, eles vão aparecendo durante o jogo).
* bird.cpp: possui vetor de "positions" do pássaro. As posições são indexadas, reaproveita-se pontos. É definida a estrutura geral do pássaro (posição, cores).
* openglwindow.cpp:
* pipe.cpp: 
* main.cpp:
* gamedata.hpp: definição dos comandos e estado do jogo. São definidas as posições (direita, esquerda, pular), estado (jogando, fim de jogo) e também uma pontuação para o jogador. Quanto mais tempo ele se mantem no jogo, maior sua pontuação.
