# Solar-System
OpenlGl Solar System

**Elideus says: IMPORTANTE!!!** -----------------------------------------------

  É necessário **posicionar os planetas** o mais rápido possível, por causa das órbitas. Eu poderia modelar uma órbita de raio 1, e dava-mos scale consoante a posição do planeta, porém, se **dermos scale na órbita**, esta deixará de ser uma linha e **ficará esticada** e achatada. Por isso, eu posso modelar **8 órbitas** (9 se quiserem a da lua) com **raios específicos**.
  Acho que amanhã bastava reunirmos depois da minha reuniao com o frutuoso (pelas 17h20), até lá estudávamos gestão)

---------------------------------------------------------

TODO: ----------------------------------------------------

- Iluminação proveniente do sol
- Posicionamento certo dos planetas, das velocidades e da órbitra.
- Multiplicar todos os movimentos (translações, rotações, e incrementos/decrementos de vartiáveis) por deltaTime
- Verificar o limite de afastamento de zoom máximo (o zoom de afastamento máximo é diferente se usarmos aproximação com o w, ou pelo menos pareceu-me)
- modelação das órbitas

----------------------------------------------------------

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
