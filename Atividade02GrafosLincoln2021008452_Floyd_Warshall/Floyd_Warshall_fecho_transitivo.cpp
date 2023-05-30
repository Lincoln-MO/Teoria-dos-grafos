#include <iostream>
#include <vector>
#include <climits>

#define INF INT_MAX

using namespace std;

vector<vector<int>> floydWarshall(const vector<vector<int>>& graph) {
    int num_vertices = graph.size();
    vector<vector<int>> dist(num_vertices, vector<int>(num_vertices, INF));

    // Inicialização das distâncias conhecidas
    for (int u = 0; u < num_vertices; u++) {
        for (int v = 0; v < num_vertices; v++) {
            if (u == v) {
                dist[u][v] = 0; // faz o tratamento da diagonal da matriz preenchida com zeros.
            } else if (graph[u][v] != 0) {
                dist[u][v] = graph[u][v];
            }
        }
    }

    // Calcula as distâncias mínimas
    for (int k = 0; k < num_vertices; k++) {
        for (int i = 0; i < num_vertices; i++) {
            for (int j = 0; j < num_vertices; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    //dist[i][j] = dist[i][k] + dist[k][j];
                    dist[i][j] = 1;
                }
            }
        }
    }

    return dist;
}

// Função auxiliar para imprimir a matriz de distâncias
void printMatrix(const vector<vector<int>>& matrix) {
    int num_vertices = matrix.size();
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            if (matrix[i][j] == INF) {
                cout << "INF ";
            } else {
                cout << matrix[i][j] << " ";
            }
        }
        cout << endl;
    }
}

int main() {
    // Exemplo de utilização
    vector<vector<int>> graph = {
        {0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };

    vector<vector<int>> result = floydWarshall(graph);

    // Imprime a matriz de fecho transitivo
    printMatrix(result);

    return 0;
}



/*Em uma matriz de fecho transitivo resultante do algoritmo de Floyd-Warshall, o valor 'dist[u][v]' 
será infinito se não houver caminho direcionado do vértice 'u' para o vértice 'v'. Caso contrário, se 'dist[u][v]' 
for diferente de infinito, significa que existe um caminho direcionado entre os vértices 'u' e 'v'.*/