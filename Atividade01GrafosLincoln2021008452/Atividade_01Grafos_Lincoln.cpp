#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

typedef struct {
    int** matriz;
    int numVertices;
    int numArestas;
} Grafo;

Grafo* criaMatriz(int numVertices) {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->numVertices = numVertices;

    grafo->matriz = (int**)malloc(numVertices * sizeof(int*));
    for (int i = 0; i < numVertices; i++) {
        grafo->matriz[i] = (int*)malloc(numVertices * sizeof(int));
    }

    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            grafo->matriz[i][j] = 0;
        }
    }

    return grafo;
}

Grafo* criaMatrizIncidencia(int numVertices, int numArestas) {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->numVertices = numVertices;
    grafo->numArestas = numArestas;

    grafo->matriz = (int**)malloc(numVertices * sizeof(int*));
    for (int i = 0; i < numVertices; i++) {
        grafo->matriz[i] = (int*)malloc(numArestas * sizeof(int));
    }

    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numArestas; j++) {
            grafo->matriz[i][j] = 0;
        }
    }

    return grafo;
}

void adicionaAresta(Grafo* grafo, int u, int v) {
    grafo->matriz[u][v] = 1;
    grafo->matriz[v][u] = 1; // se o grafo for não-direcionado
}

void adicionaArestaIncidencia(Grafo* grafo, int u, int v, int aresta) {
    grafo->matriz[u][aresta] = 1;
    grafo->matriz[v][aresta] = 1;
}

void imprimeMatrizAdjacencias(Grafo* grafo) {
    printf("Matriz de adjacencias:\n");
    for (int i = 0; i < grafo->numVertices; i++) {
        for (int j = 0; j < grafo->numVertices; j++) {
            printf("%d ", grafo->matriz[i][j]);
        }
        printf("\n");
    }
}

void imprimeMatrizIncidencia(Grafo* grafo) {
    printf("Matriz de incidencia:\n");
    for (int i = 0; i < grafo->numVertices; i++) {
        for (int j = 0; j < grafo->numArestas; j++) {
            printf("%d ", grafo->matriz[i][j]);
        }
        printf("\n");
    }
}

void liberaMatriz(Grafo* grafo) {
    for (int i = 0; i < grafo->numVertices; i++) {
        free(grafo->matriz[i]);
    }
    free(grafo->matriz);
    free(grafo);
}

string verificaTipoGrafo(Grafo* grafo) {
    int numArestas = 0;
    int numLoops = 0;
    int numArestasRepetidas = 0;

    for (int i = 0; i < grafo->numVertices; i++) {
        for (int j = 0; j < grafo->numVertices; j++) {
            if (grafo->matriz[i][j] == 1) {
                numArestas++;
                if (i == j) {
                    numLoops++;
                }
                if (grafo->matriz[j][i] == 1 && i != j) {
                    numArestasRepetidas++;
                }
            }
        }
    }

    if (numArestasRepetidas > 0) {
        return "multigrafo";
    } else if (numLoops > 0) {
        return "pseudografo";
    } else {
        return "grafo simples";
    }
}

void dfs(Grafo* grafo, int vertice, bool* visitado) {
    visitado[vertice] = true;

    for (int i = 0; i < grafo->numVertices; i++) {
        if (grafo->matriz[vertice][i] == 1 && !visitado[i]) {
            dfs(grafo, i, visitado);
        }
    }
}

bool verificaConexo(Grafo* grafo) {
    bool* visitado = new bool[grafo->numVertices];
    for (int i = 0; i < grafo->numVertices; i++) {
        visitado[i] = false;
    }

    dfs(grafo, 0, visitado);

    for (int i = 0; i < grafo->numVertices; i++) {
        if (!visitado[i]) {
            return false;
        }
    }

    return true;
}



bool verificaCompleto(Grafo* grafo) {
    for (int i = 0; i < grafo->numVertices; i++) {
        for (int j = 0; j < grafo->numVertices; j++) {
            if (i != j && grafo->matriz[i][j] != 1) {
                return false;
            }
        }
    }

    return true;
}

int calculaOrdem(Grafo* grafo) {
    return grafo->numVertices;
}

int calculaTamanho(Grafo* grafo) {
    int tamanho = 0;
    for (int i = 0; i < grafo->numVertices; i++) {
        for (int j = i + 1; j < grafo->numVertices; j++) {
            if (grafo->matriz[i][j] == 1) {
                tamanho++;
            }
        }
    }

    return tamanho;
}

int calculaGrauVertice(Grafo* grafo, int vertice) {
    int grau = 0;
    for (int i = 0; i < grafo->numVertices; i++) {
        if (grafo->matriz[vertice][i] == 1) {
            grau++;
        }
    }

    return grau;
}

void imprimeGrausVertices(Grafo* grafo) {
    printf("Grau de cada vertice:\n");
    for (int i = 0; i < grafo->numVertices; i++) {
        int grau = calculaGrauVertice(grafo, i);
        printf("Vertice %d: %d\n", i, grau);
    }
}

int main() {
    char filename[100];
    FILE* file;

    printf("Digite o nome do arquivo: ");
    scanf("%s", filename);

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    int numVertices, numArestas;
    fscanf(file, "%d %d", &numVertices, &numArestas);

    Grafo* grafo = criaMatriz(numVertices);
    Grafo* grafoIncidencia = criaMatrizIncidencia(numVertices, numArestas);

    int u, v;
    for (int i = 0; i < numArestas; i++) {
        fscanf(file, "%d %d", &u, &v);
        adicionaAresta(grafo, u, v);
        adicionaArestaIncidencia(grafoIncidencia, u, v, i);
    }

    fclose(file);

    imprimeMatrizAdjacencias(grafo);
    cout << "\n";
    imprimeMatrizIncidencia(grafoIncidencia);
    cout << "\n";

    string tipoGrafo = verificaTipoGrafo(grafo);
    cout << "Tipo de grafo: " << tipoGrafo << endl;

    bool conexo = verificaConexo(grafo);
    if (conexo) {
        cout << "O grafo e conexo." << endl;
        cout << "\n";
    } else {
        cout << "O grafo e desconexo." << endl;
        cout << "\n";
    }

    bool completo = verificaCompleto(grafo);
    if (completo) {
        cout << "O grafo e completo." << endl;
        cout << "\n";
    } else {
        cout << "O grafo nao e completo." << endl;
        cout << "\n";
    }

    int ordem = calculaOrdem(grafo);
    cout << "Ordem do grafo: " << ordem << endl;
    cout << "\n";

    int tamanho = calculaTamanho(grafo);
    cout << "Tamanho do grafo: " << tamanho << endl;
    cout << "\n";

    imprimeGrausVertices(grafo);
    cout << "\n";

    liberaMatriz(grafo);
    liberaMatriz(grafoIncidencia);

    return 0;
}
