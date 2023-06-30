// Lincoln Martins de Oliveira                                                  2021008452                      Data: 29/06/2023
// Breve comentario sobre o codigo:
//contém a implementação dos métodos da classe Graph, definida no arquivo "graph.hpp". 
//Essa implementação define o comportamento dos métodos e as operações realizadas em um grafo não direcionado. 
//----------------------------------------------------------------------------------------------------------------------------------------------------------
#include <iomanip>
#include "D:\Documentos\Desktop\Programa_ResolveSudoku\includes\graph.hpp"

// Construtor da classe Graph
Graph::Graph(vector<set<int> > vertex) : vertex(std::move(vertex)) {  }

// Adiciona um novo vértice ao grafo e retorna seu índice
int Graph::newVertex() {
    this->vertex.emplace_back(set<int>());
    return this->vertex.size() - 1;
}

// Adiciona vários novos vértices ao grafo
void Graph::newManyVertex(int n) {
    for (int i = 0; i < n; i++)
        this->newVertex();
}

// Obtém o conjunto de vértices adjacentes a um determinado vértice
const set<int>& Graph::getVertex(unsigned int vertexIndex) const {
    return this->vertex.at(vertexIndex);
}

// Obtém o grau de um determinado vértice (quantidade de vértices adjacentes a ele)
int Graph::getVertexDegree(unsigned int vertexIndex) const {
    return this->vertex.at(vertexIndex).size();
}

// Insere uma aresta entre dois vértices do grafo
void Graph::pushBackEdge(int vertexIndex, int vertexTarget) {
    this->vertex[vertexIndex].insert(vertexTarget);
}

// Verifica se dois vértices são adjacentes
bool Graph::isAdjacent(const set<int>& v1, int v2) const {
    return v1.find(v2) != v1.end();
}

// Adiciona uma aresta entre dois vértices
void Graph::addEdge(int v1, int v2) {
    if (v1 >= this->vertex.size() || v2 >= this->vertex.size())
        return;

    if (!this->isAdjacent(this->getVertex(v1), v2))
        pushBackEdge(v1, v2);

    if (!this->isAdjacent(this->getVertex(v2), v1))
        pushBackEdge(v2, v1);
}

// Mostra o grafo na forma de uma lista de adjacências
void Graph::showGraph() const {

    for (unsigned int i = 0; i < this->getGraphSize(); i++) {
        cout << "v[" << i << "] -> ";

        for (auto j = this->vertex.at(i).begin(); j != this->vertex.at(i).end(); j++) {
            if (j != this->vertex.at(i).begin())
                cout << ", ";

            cout << setw(2) << *j;
        }

        cout << endl;
    }
}

// Obtém o tamanho do grafo (número de vértices)
int Graph::getGraphSize() const {
    return this->vertex.size();
}