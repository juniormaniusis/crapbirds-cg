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

Jogo inspirado no estilo de Flappy Bird. O pássaro é o personagem que irá percorrer seu caminho desviando de obstáculos. Se ele bater em um dos obstáculos, o jogador perde.
Fizemos os desenhos através do [geogebra](https://www.geogebra.org/calculator) para definir os pontos no código. Desenhamos o pássaro, as nuvens do plano de fundo e os obstáculos com a ferramenta de *segmento de reta* do geogebra. Após desenhar, extraímos os pontos (x,y) que compõem os desenhos. 

### Código

* nuvens.cpp: o desenho das nuvens foi criado no geogebra e extraímos os pontos de seu formato. Criamos um *array de nuvens* e uma função que faz com que os desenhos das nuvens sejam escolhidos aleatoriamente (são dois tipos).
