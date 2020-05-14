# Solar-System
OpenlGl Solar System

TODO: ----------------------------------------------------

- Iluminação proveniente do sol
- Posicionamento certo dos planetas, das velocidades e da órbitra (talvez seja necessário mudar, dependendo da resposta do prof).
- Diferentes vistas
- As distâncias do modo de vista planeta precisam de um fix, depois trato disso


----------------------------------------------------------

UPDATE (14/05/2020 -22h26) -----------------------------------------------

- modelação das órbitas
- possibilidade de olhar para um planeta específico usando o teclado
  - A seta para a direita move-se de planeta em direção a neptuno, a seta para a esquerda move-se de planeta em planeta em direção a neptuno)
  - Pressionar l para voltar à vista livre
- a tecla L alterna entre olhar fixamente para o sol e olhar livremente
- inputs não contínuos (espaço, t, l, right arrow e left arrow)
  - os inputs como o wasd são inputs contínuos, isto é, se a tecla se mantiver pressionada (hold), as ações causadas pelas mesmas são contínuas e acontecem a cada frame. Isso não se pretende nem tem bom aspeto em ações como "Pause" e "change planet view", pois mantendo a tecla "space" pressionada por 2 frames faria a sequência "pause->play".
  - Dado isto, o implementado foi o seguinte: Quando uma das teclas mencionadas acima é pressionada, esta só pode voltar a ser pressionada depois de ser libertada (ao detetar um GLFW_RELEASE)

UPDATE (13/05/2020 -19h59) -----------------------------------------------

- Escalas e velocidades:
  - Velocidades de translação (não reais)
  - Velocidades de rotação (não reais)
  - Carregamento do modelo da esfera alterado para ser feito apenas 1 vez
  - Adicionado um modelo dos aneis de urano
  - pequena alteração na função do keyboard da camera.h (será possivelmente removida, caso nao se consiga fazer a colisão com o "sol")

UPDATE (13/05/2020 - 00h45) -----------------------------------------------

- Movimento e animações da câmara:
  - Zoom, feito com Scroll
  - Movimento livre com rato e teclado
  - Teclas para movimento (A, S, W, D)
- Animação da pausa adicionada

UPDATE (12/05/2020 - 22h56) -----------------------------------------------

- Projeto começado de modo mas desta vez com carregamento de objetos modelados no blender

UPDATE (12/05/2020 - 10h23) -----------------------------------------------

- Código completamente comentado

UPDATE (11/05/2020 - 22h44) -----------------------------------------------

- Alteração no movimento da camera nas keys W,S (melhoria nas velocidades)
- Tentativa de desenhar orbitas (falhada, codigo ficou comentado)

UPDATE (11/05/2020 - 20h17) -----------------------------------------------

- Aplicadas escalas (nao reais) aos raios, velocidades e distancias dos planetas
- Alterada a orbita dos planetas para sentido anti horário (exceptio mercurio)
- Tentativa de obter as coordenadas dos objetos em coordenadas de exra (semi-conseguido)
- A camera move-se em orbita do sol (necessário dar fix na movimentação vertical)

UPDATE (10/05/2020 - 23h13) -----------------------------------------------

- Alterado o modo como são feitos os highlights (o antigo fazia por cores, cores semelhantes falahvam)

UPDATE (10/05/2020 - 19h32) -----------------------------------------------

- Cores dos planetas alteradas (ainda sem textura)
- Alterada a view da câmera
- Adicionada uma lua
- Movimento da lua à volta da terra
