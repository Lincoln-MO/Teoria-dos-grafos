// Lincoln Martins de Oliveira                                                  2021008452                      Data: 29/06/2023
// Breve comentario sobre o codigo: 
// Contém a definição da classe Graph, que representa um grafo não direcionado. Um grafo é uma estrutura de dados composta por um conjunto de vértices (ou nós) conectados por arestas.
// O objetivo do algoritmo é fornecer métodos para manipular e interagir com esse grafo.
//----------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef RESOLVE_SUDOKU_WITH_COLORING_GRAPH_HPP
#define RESOLVE_SUDOKU_WITH_COLORING_GRAPH_HPP

#include <vector>
#include <iostream>
#include <set>

using namespace std;

/*
 * Todo:
 * - Adicionar novo vértice [v] [v]
 * - Adicionar n vertices [v] [v]
 * - verificar se é adjacente [v] [v]
 * - adicionar uma aresta [v] [v]
 * - obter um dado vértice [v] [v]
 * - obter o grau do vértice [v] [v]
 * - mostrar o grafo [v] [v]
 * */

class Graph {

private:
    vector<set<int> > vertex;

    // Empurra para trás um dado vértice para um novo vértice
    void pushBackEdge(int vertexIndex, int vertexTarget);

    /**
     *	Obtém o tamanho do grafo
    */
    int getGraphSize() const;

public:
    Graph() = default;
    Graph(vector<set<int> > vertices);
    ~Graph() = default;

    /**
     * Adiciona um novo vértice e retorna o número do vértice
     * */
    int newVertex();

    /**
     * Adicionar n vértices ao grafo
     * */
    void newManyVertex(int n);

    /**
     * Obter um vértice por um índice específico
     * */
    const set<int>& getVertex(unsigned int vertexIndex) const;

    /**
     *	Obtém o grau de um vértice específico
    */
    int getVertexDegree(unsigned int vertexIndex) const;

    /**
     * Adicionar uma aresta entre dois vértices
     * */
    void addEdge(int v1, int v2);

    /**
     * Verificar se um vértice é adjacente a outro na lista
     * */
    bool isAdjacent(const set<int>& v1, int v2) const;

    /**
     *	Mostra o grafo
    */
    void showGraph() const;

    /**
     *	Retorna o grau de um vértice em um grafo.
    */
    int getDegree(int vertex);
};

#endif //RESOLVE_SUDOKU_WITH_COLORING_GRAPH_HPP
