// Lincoln Martins de Oliveira                                                  2021008452                      Data: 29/06/2023
// Breve comentario sobre o codigo: 
// Contém a definição da classe Sudoku, que é responsável pela resolução do jogo de Sudoku usando técnicas de coloração de grafos.
//----------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef RESOLVE_SUDOKU_WITH_COLORING_SUDOKU_HPP
#define RESOLVE_SUDOKU_WITH_COLORING_SUDOKU_HPP

#include <tuple>
#include <vector>
#include <set>

#include "graph.hpp"

/*
 * Todo:
 * - Obter a instancia de Grafo e garantir que seja a unica [v] [v]
 * - Obter uma cor em uma dada posição [v] [v]
 * - Implementar o Welsh Powell para coloração [v] [v] 
 * - Implementar o Dsatur para coloração [] [] 
 * - Mostrar o tabuleiro [v] [v]
 * - Mostrar o tabuleiro pré-colorido dos dados do arquivo [v] [v]
 * - Lê o arquivo no formato index -> value [v] [v]
 * - Retorna o número de cores iniciais do arquivo [v]
 * */

class Sudoku {

private:

    Graph graph;

    set<int> indexConstants;
    int colors[81];
    vector<tuple<int, int> > numbers;

    /**
     * Pré-colorindo o grafo
     * O vetor de cores (colors) recebe no indice correspondente de toda a coluna esquerda os valores ques estão à direita
     * Isso faz referência aos dados padrões do arquivo, onde mesmo é composto por index e value
     * */
    void preColoring (vector<tuple<int, int> > numbersAux);

    /**
     * Esta função é responsável por inicializar as cores para o tabuleiro do Sudoku. Ela é chamada durante a pré-coloração do grafo.
     * */
    void startColors ();

    /**
     * Obter o número total de cores do grafo
     * */
    int getColorsSize() const;

public:
    Sudoku();
    Sudoku(vector<tuple<int, int> > numbers);
    ~Sudoku() = default;

    /**
     * Garante uma instância Singleton para grafo
     * */
    const Graph& getGraph() const;

    /**
     *	Retorna a cor numa posição n
    */
    int getColorAt(int n) const;

    /**
     *	Implementação do algoritmo DSatur para coloração junto com o backtracking
     *  (DSATUR, que significa "Grau de Saturação", é um algoritmo de coloração de grafos usado para colorir os vértices de um grafo de forma que vértices adjacentes não tenham a mesma cor.)
     */
    bool backtrackingAlgorithm();

    /**
     *	Retorna a cor numa posição n
    */
    bool backtrackingHelper(vector<int>& uncolored, int index);

    /**
     *	Retorna a cor numa posição n
    */
    set<int> getAvailableColors(int vertex);

    /**
     *	Retorna a cor numa posição n
    */
    bool isSafeColor(int vertex, int color);

    /**
    *	Implementação do algoritmo Welsh Powell para coloração
    *  (O algoritmo Welsh-Powell funciona da seguinte maneira:
    *   1-  Ordena-se os vértices do grafo em ordem decrescente de grau, ou seja, o vértice com o maior grau vem primeiro.
    *   2-  Atribui-se a cor 1 ao primeiro vértice da lista ordenada.
    *   3-  Percorre-se a lista de vértices, a partir do segundo vértice, e atribui-se a menor cor possível que não esteja sendo usada por nenhum de seus vértices adjacentes.
    *   4-  Repete-se o passo 3 até que todos os vértices tenham sido coloridos.)
    */
    bool welshPowellAlgorithm();

    /**
     *	Mostra o board do sudoku
    */
    void showFullBoardwelshPowell() const;
    
    /**
     *	Esta função exibe o tabuleiro completo do Sudoku após a aplicação do algoritmo DSatur para coloração. Ela mostra a disposição dos números coloridos no tabuleiro.
    */
    void showFullBoardDSatur() const;

    /**
     *	Retorna o número inicial de cores
    */
    int getPreColorSize() const;

    /**
     *	Pré carrega as cores vindo do arquivo
    */
    bool loadBoardFromFile(const string& name);

    /**
     *	Gera as arestas do grafo baseado no arquivo
    */
    void generateGraph();

    /**
     *	Método para obter uma linha/coluna referente ao índice do grafo, para pôr no tabuleiro
     *	Garante a logica da posição dos números na matriz ou nas submatrizes do tabuleiro
    */
    int getRowQuadrant(int i) const;

    /**
     *	Esta função retorna o quadrante de coluna ao qual o índice "i" pertence no tabuleiro do Sudoku. Ela é usada para mapear a posição correta dos números no tabuleiro ou nas submatrizes do Sudoku.
    */
    int getColumnQuadrant(int i) const;

    /**
     *	Verifica se um vértice esta colorido
    */
    bool isColored (int index) const;

    /**
     *	Obtém as cores únicas usadas no Grafo
    */
    void getUniqueColors() const;
};

#endif //RESOLVE_SUDOKU_WITH_COLORING_SUDOKU_HPP
