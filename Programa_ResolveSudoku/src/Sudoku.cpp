// Lincoln Martins de Oliveira                                                  2021008452                      Data: 29/06/2023
// Breve comentario sobre o codigo: 
//O arquivo "sudoku.cpp" contém a implementação dos métodos da classe Sudoku, que é responsável por resolver o jogo de Sudoku usando técnicas de coloração de grafos.
//----------------------------------------------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <algorithm>
#include "D:\Documentos\Desktop\Programa_ResolveSudoku\includes\sudoku.hpp"

using namespace std;

Sudoku::Sudoku() {

    // Iniciliza o tabuleiro com todas as 81 posições com uma única cor (color 0)
    this->startColors();

    // Gera o grafo a partir da lógica de conexões do tabuleiro do Sudoku
    this->generateGraph();
}

//Funçõo para inicilizar o tabuleiro com todas as 81 posições com uma única cor (color 0)
void Sudoku::startColors() {
    for (int i = 0; i < 81; i++)
        this->colors[i] = 0;
}

// Construtor que recebe números pré-coloridos no formato index -> value
Sudoku::Sudoku(vector<tuple<int, int> > numbers) {

    // Iniciliza o tabuleiro com todas as 81 posições com uma única cor (color 0)
    this->startColors();

    /*
     * Pré-colore o grafo
     * O vetor de cores (colors) recebe no indice correspondente à toda a coluna da esquerda, os valores que estão à direita
     * Isso faz referência aos dados padrões do arquivo, onde mesmo é composto por linhas no formato {index value}
     * */

    // Pré-colore os números do tabuleiro no formato index -> value
    this->preColoring(numbers);

    // Gera o grafo a partir da lógica de conexões do tabuleiro do Sudoku
    this->generateGraph();
}

// Retorna o grafo do Sudoku
const Graph& Sudoku::getGraph() const {
    return this->graph;
}

// Retorna a cor em uma posição específica do tabuleiro
int Sudoku::getColorAt(int n) const {
    return this->colors[n];
}

// Retorna o tamanho do vetor de cores
int Sudoku::getColorsSize () const {
    return sizeof(this->colors) / 4;
}

// Obtém as cores únicas presentes no tabuleiro
void Sudoku::getUniqueColors() const {
    // (n * (n-1)) / 2
    cout << "[";
    for (int i = 0; i < this->getColorsSize(); i++) {
        int j;
        for (j = 0; j < i; j++)
            if (this->colors[i] == this->colors[j])
                break;

        if (i == j)
            cout << this->colors[i] << ", ";
    }
    cout << "]";
}

// Verifica se uma posição no tabuleiro está colorida
bool Sudoku::isColored(int index) const {
    return this->colors[index] > 0;
}

// Retorna o número de pré-coloridos no tabuleiro
int Sudoku::getPreColorSize() const {
    return this->indexConstants.size();
}

// Pré-colora os números do tabuleiro
void Sudoku::preColoring(vector<tuple<int, int> > numbersAux) {
    for (int i = 0; i < numbersAux.size(); i++) {
        // Pré-colorindo
        this->colors[get<0>(numbersAux.at(i))] = get<1>(numbersAux.at(i));
        this->indexConstants.insert(get<0>(numbersAux.at(i)));
    }
}

// Gera o grafo a partir da lógica de conexões do tabuleiro do Sudoku
void Sudoku::generateGraph() {

    // Aloca 81 vértices para o grafo numerados de 0 a 80
    this->graph.newManyVertex(81);

    static int j, quadrantColumn, quadrantRow;

    for (int i = 0; i < 81; i++) {

        quadrantRow = this->getRowQuadrant(i);
        quadrantColumn = this->getColumnQuadrant(i);

        j = i + 1; // Conexões entre as colunas

        while (this->getColumnQuadrant(j) == quadrantColumn) {
            if (this->getRowQuadrant(j) == quadrantRow) {
                this->graph.addEdge(i, j);
                j++;
            } else {
                j += 6;
            }
        }

        j = i + 1; // Conexões entre linhas

        // Evita repetições das arestas
        while (this->getRowQuadrant(j) == quadrantRow) j++;

        while (j % 9 > i % 9) {
            this->graph.addEdge(i, j);
            j++;
        }

        j = i + 9; // Conexões das linhas

        // Evita repetições das arestas
        while (this->getColumnQuadrant(j) == quadrantColumn) j += 9;

        while (j < 81) {
            this->graph.addEdge(i, j);
            j += 9;
        }
    }
}

// Função para obter o quadrante da linha em que um índice se encontra
int Sudoku::getRowQuadrant(int i) const {
    return (i % 9) / 3;
}

// Função para obter o quadrante da coluna em que um índice se encontra
int Sudoku::getColumnQuadrant(int i) const {
    return (i / 9) / 3;
}

// Função para carregar o tabuleiro a partir de um arquivo
bool Sudoku::loadBoardFromFile(const string& name) {
    ifstream file;
    string lines;

    int index, colors, j = 0;
    vector<tuple<int, int> > numbers;

    file.open(name);
    if (!file.is_open())
        return false;

    while (!file.eof() && j < 81) {
        getline(file, lines);
        sscanf(lines.c_str(), "%d %d", &index, &colors);
        numbers.emplace_back(make_tuple(index, colors));
        j++;
    }

    // Pré-colore os números do tabuleiro no formato index -> value
    this->preColoring(numbers);

    file.close(); // Fecha o arquivo

    return true;
}

// Função para executar o algoritmo de Welsh-Powell
bool Sudoku::welshPowellAlgorithm() {
    vector<set<int>> possible_colors(81, set<int>());
    vector<int> uncolored;

    for (int i = 0; i < 81; i++) {
        if (this->indexConstants.find(i) == this->indexConstants.end()) {
            // Marca o vértice como não colorido
            uncolored.push_back(i);

            // Marca uma possível cor para o vértice
            for (int j = 1; j <= 9; j++)
                possible_colors.at(i).insert(j);
        }
    }

    // Para cada vértice pré-colorido
    for (auto i = this->indexConstants.begin(); i != this->indexConstants.end(); i++) {
        // obtém seus adjacentes
        set<int> neighbors = this->graph.getVertex(*i);

        // Para cada vizinho deste vértice pré-colorido
        for (auto j = neighbors.begin(); j != neighbors.end(); j++) {

            auto eraser = possible_colors.at(*j).find(this->colors[*i]);

            if (eraser != possible_colors.at(*j).end())
                possible_colors.at(*j).erase(eraser);
        }
    }

    // Ordenar os vértices na crescente, mediante uma expressão lambda, considerando a quantidade possivel de cores
    sort(uncolored.begin(), uncolored.end(), [possible_colors](const int& i, const int& j) -> bool {
        return possible_colors.at(i).size() < possible_colors.at(j).size();
    });

    // Iterar as possibilidades concretas de cores
    for (int i = 1; i < uncolored.size() + 1; i++) {

        if (possible_colors.at(uncolored.at(i-1)).size() == 0)
            return false;

        this->colors[uncolored.at(i-1)] = *(possible_colors.at(uncolored.at(i-1)).begin());

        set<int> neighbors = this->getGraph().getVertex(uncolored.at(i-1));

        for (auto j = neighbors.begin(); j != neighbors.end(); j++) {

            auto eraser = possible_colors.at(*j).find(this->colors[uncolored.at(i-1)]);

            if (eraser != possible_colors.at(*j).end())
                possible_colors.at(*j).erase(eraser);
        }
    }

    return true;
}

// Função para executar o algoritmo de backtracking
bool Sudoku::backtrackingAlgorithm() {
    vector<int> uncolored;
    for (int i = 0; i < 81; i++) {
        if (!isColored(i)) {
            uncolored.push_back(i);
        }
    }

    return backtrackingHelper(uncolored, 0);
}

// Função auxiliar para realizar a recursão no algoritmo de backtracking
bool Sudoku::backtrackingHelper(vector<int>& uncolored, int index) {
    if (index >= uncolored.size()) {
        return true;  // Todas as variáveis foram atribuídas
    }

    int vertex = uncolored[index];
    set<int> availableColors = getAvailableColors(vertex);

    for (int color : availableColors) {
        if (isSafeColor(vertex, color)) {
            colors[vertex] = color;

            if (backtrackingHelper(uncolored, index + 1)) {
                return true;
            }

            colors[vertex] = 0;  // Desfaz a atribuição se não for uma solução válida
        }
    }

    return false;  // Nenhuma cor válida encontrada, retrocede para tentar outra cor
}

// Função auxiliar para obter as cores disponíveis para um vértice específico
set<int> Sudoku::getAvailableColors(int vertex) {
    set<int> availableColors;
    // Preenche um vetor de cores de 1 a 9
    for (int i = 1; i <= 9; i++) {
        availableColors.insert(i);
    }

    // Remove as cores que estão sendo usadas pelos vértices adjacentes
    set<int> neighbors = graph.getVertex(vertex);
    for (int neighbor : neighbors) {
        if (isColored(neighbor)) {
            // Encontra a posição da cor usada no vetor de cores disponíveis e a remove
            availableColors.erase(colors[neighbor]);
        }
    }

    return availableColors;
}

// Função auxiliar para verificar se uma cor é segura para um vértice específico
bool Sudoku::isSafeColor(int vertex, int color) {
    set<int> neighbors = graph.getVertex(vertex);
    for (int neighbor : neighbors) {
        if (isColored(neighbor) && colors[neighbor] == color) {
            return false;  // Cor inválida se o vizinho tiver a mesma cor
        }
    }

    return true;
}

//Funcao para imprimir o sudoku resolvido por Welsh-Powell
void Sudoku::showFullBoardwelshPowell() const {

    cout << endl;
    cout << "  ----------------------- " << endl;

    for (int i = 0; i < 81; i++) {

        if (i % 9 == 0 && i != 0){
            cout << " |" << endl;

            if ((i / 9) % 3 == 0)
                cout << "  ----------------------- " << endl;
        }

        if (i % 3 == 0)
            cout << " |";

        if (this->colors[i] == 0)
            cout << "  ";
        else
            cout << " " << this->colors[i];
    }

    cout << " |" << endl;
    cout << "  ----------------------- " << endl;
}

//Funcao para imprimir o sudoku resolvido por DSatur e backtracking
void Sudoku::showFullBoardDSatur() const {
    cout << "Tabuleiro completo: " << endl;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int vertexIndex = i * 9 + j;

            if (this->indexConstants.find(vertexIndex) != this->indexConstants.end()) {
                // Exibir valor pré-colorido
                cout << this->colors[vertexIndex] << " ";
            } else {
                // Exibir valor atribuído pelo algoritmo DSatur
                cout << this->colors[vertexIndex] << " ";
            }

            if (j == 2 || j == 5) {
                cout << "| ";
            }
        }

        cout << endl;

        if (i == 2 || i == 5) {
            cout << "------+-------+------" << endl;
        }
    }
}