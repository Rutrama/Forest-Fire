# Forest-Fire
Uma simulação de um Incêncio Florestal que utiliza matrizes e vetores para a representação da estrutura. Feito para a disciplina de Algoritmos e Estrutura de Dados.
## Autor
[![GitHub](https://img.shields.io/badge/github-%23121011.svg?style=for-the-badge&logo=github&logoColor=white)](https://github.com/Rutrama) Arthur Santana de Mesquita
## Introdução
Este trabalho consiste na representação de uma floresta através de uma matriz de tamanho variável, seguindo as especificações do documento da [pratica](pratica.pdf) fornecido pelo professor da disciplina.
O valor númerico em cada posição da matriz representa um dos possíveis estados daquela posição:

> 0 -> Área vazia (não queima)

> 1 -> Árvore saudável

> 2 -> Árvore em chamas

> 3 -> Árvore queimada (não propaga mais fogo)

> 4 -> Presença de água

A cada iteração o fogo _(2)_ pode se espalhar, tanto a partir de todos os focos de incêndio disponíveis, quanto através de um único foco aleatório, o que pode ser decidido antes da compilação do programa no arquivo de [configuração](src/config.hpp), uma variável booleana que foi chamada de _FAST_SPREAD_ ou Espalhamento Rápido.
Em ambos os casos, árvores saudáveis _(1)_ próximas ao fogo que está se espalhando são transformadas em novos focos de incêndio _(2)_ enquanto os focos atuais árvores completamente queimadas _(3)_, com a direção desta disperção sendo decidida através da variável _WIND_ que representa a influência de vento sobre o incêndio.

Um animal representado por uma estrutura separada da matriz deverá percorrê-la na tentativa de escapar do fogo. Assim, uma ordem de prioridade de sua movimentação pode ser colocada com base nos terrenos a sua volta. Água _(4)_, Árvore Saudável _(1)_, Área Vazia _(0)_, e finalmente, Árvore Queimada _(3)_,com a posição 2 sendo impossível de acessar e a inabilidade de encontrar uma posição válida levando à morte do animal, mas a continuação da simulação.

A condição real para o encerramento da simulação é o fim do incêndio pela ausência de focos de fogo, ou o término do número de simulações máximo, também estipulado no arquivo de [configuração](src/config.hpp).

## Metodologia

Enquanto o arquivo main.cpp inclui puramente chamadas de outras funções, a lógica do programa foi dividida entre 4 classes que implementam as funcionalidades principais do programa: 

- [Grid](src/grid.hpp): Implementa a matriz onde ocorre o incêndio e as interações do animal com a mesma.
- [Fire](src/fire.hpp): Implementa as funções que permitem que o fogo se espalhe nas direções definidas pelos limites da matriz e pelo vento.
- [Setup](src/setup.hpp): Realiza a leitura do arquivo de [Input](input.dat) e prepara a matriz que será utilizada como Grid
- [Output](src/output.hpp): Realiza a criação e escrita no arquivo de _Output_ a cada iteração e encerra o programa escrevendo o número de iterações total, e em qual iteração o animal pereceu.

Estas classes possuem uma série de funções que serão abordadas individualmente

### [Grid](src/grid.cpp)
- **_getAnimalX_** and **_getAnimalY_**: Métodos de acesso da posição horizontal e vertical do Animal, respectivamente.
-  **_isAnimalDead()_**: Uma função simples que retorna o estado de vida do animal. É utilizada para retornar todas as outras funções logo após a chamada depois que há a morte do animal, para que este não continue se movimentando e interagindo com o terreno.
-  **_getDeathIteration_**: Uma função que acessa a iteração onde o animal pereceu, de forma que esta possa ser colocada no final o arquivo de _output_
- **_getValidDirections_**: Verifica a posições do animal e certifica que as posições adjacentes sejam válidas para sua movimentação, ou seja, que ele não esteja nos limites da matriz.
- **_moveAnimal_**: Utilizando as direções validadas da função anterior verifica qual o tipo de terreno há naquela posição e as salva no vetor safeMoves seguindo a ordem de prioridade de terrenos, de forma que ao selecionar a primeira posição, a função sempre terá acesso a primeira posição disponível da maior prioridade de terreno presente.
- **_CheckAndUseWater_**: Caso o animal se localize em água _(4)_, esta função irá "usar" a água de forma a transformar todos os terrenos adjacentes (sejam eles quais forem) em árvores saudáveis _(1)_. O terreno onde a água se localiza se torna então uma área vazia _(0)_.
- **_handleFireImpact_**: Detecta após o espalhamento do fogo se houve colisão com a posição do animal, e caso tenha ocorrido, permite uma movimentação de emergência para que o animal escape do fogo. Também emite uma mensagem no terminal para que se saiba que a movimentação dupla entre duas iterações foi causada por uma colisão com o fogo.

### [Fire](src/fire.cpp)
-  **_addInitialFire()_**: Adiciona o fogo inicial salvo na estrutura [_Field_](https://github.com/Rutrama/Forest-Fire/blob/main/README.md#L55) ao vetor de focos de incêndio, iniciando a estrutura.
  
-  **_SpreadFire_**: Decide usando a função _rand()_ qual foco será espalhado nesta iteração e modifica seu terreno para cinzas (_3_) além de adicionar novos focos de incêndio ao vetor principal.
  
-  **_getValidFireDirections_**: Verifica a posições do fogo selecionado para propagação e certifica que as posições adjacentes sejam válidas para sua movimentação, ou seja, que ela seja condizente com a direção do vento especificada no arquivo de [configuração](src/config.hpp) e que ela não esteja nos limites da matriz.
  
-  **_SpreadFrom_**: Transforma árvores saudáveis (_1_) em todas as direções validas na matriz (obtidas na função anterior) em focos de incêndio (_2_) e as adiciona no vetor de  _novos_ focos de incêndio.
  
- **_removeBurntTree_**: Remove a árvore na posição especificada do vetor de focos de incêndio. Em especial é usada sempre que uma árvore propaga seu fogo, de forma a remover cinzas (_3_) do vetor.

### [Setup](src/setup.cpp)
- **_struct Field_**: A estrutura básica necessária para inicializar a matriz, contendo o número de linhas, colunas e a posição inicial do fogo além da própria matriz, na forma de um vetor de vetor.
  
- **_readSetup_**: Cria uma matriz vazia do tamanho especificado no arquivo de [entrada](input.dat) e salva na estrutura criada acima as informações obtidas através de sua leitura.

### [Output](src/output.cpp)
- **_writeIteration_**: Função que é chamada todo turno, de forma a salvar uma cópia da matriz após todas as modificações no arquivo de _output_ além de escrever a posição atual do animal.
> Animal em (X, Y)

- **_writeDeathInfo_**: Acessa a função [_getDeathIteration_](https://github.com/Rutrama/Forest-Fire/blob/main/README.md#L39) e salva o valor obtido no arquivo _output.dat_, caso seu valor seja o valor default _(-1)_, o animal sobreviveu
> "O animal morreu na iteração T"
ou
> "O animal sobreviveu!"

## Método de Compilação
O Repositório foi compilado e testado utilizando 
- _g++-14_ no MacOS Ventura 13.7.4
  > g++-14 -std=c++17 src/*.cpp -o forest_fire_simulation -Wall -Wextra
  
- _Apple-Clang_ no MacOS Ventura 13.7.4
  > g++ -std=c++17 src/*.cpp -o forest_fire_simulation -Wall -Wextra
  
- _g++-17_ no Ubuntu 22.04
  > g++-17 src/*.cpp -o forest_fire_simulation -Wall -Wextra

## Referências
- [Documento da Pratica](pratica.pdf)
