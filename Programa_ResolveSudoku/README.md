## Algoritmo de Welsh Powell


O algoritmo de Welsh-Powell é como um jogo de colorir um mapa. Vamos imaginar que temos um mapa com várias regiões, e o objetivo é pintar cada região com uma cor diferente, mas sem pintar regiões que são vizinhas com a mesma cor.


## Passo a passo do Welsh-Powell:


Passo 1: Comece escolhendo uma região qualquer do mapa e pinte-a com uma cor.


Passo 2: Agora, olhe para as regiões vizinhas dessa região que você pintou. Regiões vizinhas são as que estão ao redor ou que fazem fronteira com a região que você pintou.


Passo 3: Verifique se alguma dessas regiões vizinhas já foi pintada com a mesma cor da região que você pintou no Passo 1. Se você encontrar uma região vizinha com a mesma cor, escolha uma nova cor diferente e volte para o Passo 1.


Passo 4: Se todas as regiões vizinhas tiverem cores diferentes da região que você pintou, escolha a próxima região não pintada e pinte-a com uma nova cor.


Passo 5: Repita o Passo 2 e o Passo 3 para cada nova região que você pintar. Sempre verifique se alguma região vizinha já foi pintada com a mesma cor e, se sim, escolha uma nova cor.


Passo 6: Continue pintando as regiões restantes uma a uma e verificando se alguma região vizinha já foi pintada com a mesma cor. Se sim, escolha uma nova cor.


Passo 7: Quando todas as regiões estiverem pintadas e nenhuma região vizinha tiver a mesma cor, o jogo estará completo e todas as regiões estarão coloridas de forma correta.


O algoritmo de Welsh-Powell é como um jogo de colorir um mapa, onde você vai pintando região por região com cores diferentes, sempre verificando se as regiões vizinhas têm a mesma cor.


## Para a resolução do nosso Sudoku o Algoritmo de Welsh Powell funciona desta forma:


Preparação


1. Temos um tabuleiro de Sudoku que queremos resolver.
2. Cada célula do tabuleiro pode ter um número de 1 a 9.
3. No entanto, algumas células já têm números preenchidos inicialmente.
4. Nosso objetivo é preencher as células vazias de forma que nenhum número se repita em uma mesma linha, coluna ou subgrade (um quadrado 3x3 dentro do tabuleiro).


Organização


1. Vamos começar organizando as células em ordem decrescente de quantas outras células estão conectadas a ela.
2. Isso significa que as células com mais conexões serão colocadas no topo da lista e as com menos conexões ficarão no final.


Pintando as células


1. Agora vamos pintar as células uma por uma na ordem em que estão na lista organizada.
2. Começamos com a célula que tem o maior número de conexões.
3. Damos a ela a cor 1.


Pintando as células adjacentes


1. Agora, para cada célula na lista organizada, vamos verificar se alguma das células adjacentes já foi pintada com a mesma cor.
2. Se encontrarmos uma célula adjacente com a mesma cor, vamos tentar usar uma cor diferente para a célula atual.
3. Continuamos verificando todas as células adjacentes até encontrarmos uma cor que não seja usada por nenhuma célula adjacente.


Repetição


1. Continuamos pintando as células restantes na ordem em que estão na lista organizada.
2. Para cada célula, repetimos o passo 4, verificando as células adjacentes e encontrando uma cor disponível para a célula atual.


Conclusão


1. Quando todas as células forem pintadas, teremos uma solução para o Sudoku.
2. Todas as células estarão preenchidas com números e não haverá repetição de números em linhas, colunas ou subgrades.


## Algoritmo de backtracking


O algoritmo de backtracking é como um jogo de adivinhação. Vamos supor que você tenha um quebra-cabeça para resolver, mas você não sabe qual é a peça correta para colocar em cada lugar. O objetivo é encontrar a combinação correta de peças para montar o quebra-cabeça.


## O passo a passo do algoritmo de backtracking:


Passo 1: Comece escolhendo uma peça qualquer do quebra-cabeça e coloque-a em um lugar vazio.


Passo 2: Agora, tente encontrar uma outra peça que se encaixe com a primeira peça que você colocou. Se você encontrar uma peça que se encaixe perfeitamente, coloque-a no lugar vazio ao lado da primeira peça.


Passo 3: Continue repetindo o Passo 2 para cada peça nova que você colocar no quebra-cabeça. Tente encontrar uma peça que se encaixe com as peças já colocadas.


Passo 4: Se você não conseguir encontrar uma peça que se encaixe com as peças já colocadas, volte para a última peça que você colocou e tente outra peça diferente no lugar dela. É como se você voltasse atrás no jogo.


Passo 5: Repita o Passo 4 até que todas as possibilidades sejam tentadas. Isso significa que você tentou todas as combinações possíveis de peças.


Passo 6: Se você tentou todas as possibilidades e ainda não encontrou a combinação correta, então volte mais uma vez, mas agora para a penúltima peça que você colocou. Tente outra peça diferente neste lugar e siga novamente para o Passo 5.


Passo 7: Continue voltando atrás e tentando novas combinações até que você encontre a combinação correta para montar o quebra-cabeça.


O algoritmo de backtracking é como se fosse um jogo de tentativa e erro, onde você vai testando diferentes possibilidades até encontrar a resposta correta.


## Para a resolução do nosso Sudoku o Algoritmo de backtracking funciona desta forma:


Preparação


1. Temos um tabuleiro de Sudoku que queremos resolver.
2. Cada célula do tabuleiro pode ter um número de 1 a 9.
3. No entanto, algumas células já têm números preenchidos inicialmente.
4. Nosso objetivo é preencher as células vazias de forma que nenhum número se repita em uma mesma linha, coluna ou subgrade (um quadrado 3x3 dentro do tabuleiro).


Tentativa e erro


1. Vamos começar preenchendo a primeira célula vazia com o número 1.
2. Em seguida, passamos para a próxima célula vazia e tentamos colocar o número 1 novamente.
3. Se o número 1 funcionar, passamos para a próxima célula vazia e repetimos o processo.
4. Se chegarmos a uma célula vazia em que nenhum número funcione, voltamos para a célula anterior e tentamos um número diferente.


Backtracking


1. Quando chegamos a uma célula em que nenhum número funciona, voltamos para a célula anterior e tentamos um número diferente lá.
2. Se chegarmos à célula inicial e não encontrarmos um número que funcione, voltamos para a célula anterior a essa e tentamos um número diferente lá também.
3. Continuamos voltando e tentando números diferentes até encontrarmos uma combinação que funcione ou até tentarmos todas as possibilidades.


Repetição


1. Continuamos preenchendo as células vazias e fazendo tentativas e erros.
2. Sempre que chegamos a uma célula em que nenhum número funciona, fazemos o backtracking e tentamos um número diferente na célula anterior.
3. Repetimos esse processo até preencher todas as células do tabuleiro ou até tentarmos todas as combinações possíveis.


Passo 5: Conclusão


1. Quando encontramos uma combinação que preenche todas as células do tabuleiro sem violar as regras do Sudoku, temos uma solução.
2. Todos os números estarão corretamente posicionados, sem repetições em linhas, colunas ou subgrades.
