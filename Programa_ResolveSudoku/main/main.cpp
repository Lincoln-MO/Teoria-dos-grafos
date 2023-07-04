// Lincoln Martins de Oliveira                                                  2021008452                      Data: 29/06/2023
// Vitor Sérgio Teixeira Silva                                                  2021008855                      Data: 29/06/2023
// Breve comentario sobre o codigo: 
// Coordena a execução das etapas necessárias para resolver um jogo de Sudoku utilizando os algoritmos implementados.
//----------------------------------------------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <locale.h>
#include <bits/stdc++.h>

#include "/home/vitorsergio/Área de Trabalho/Programa_ResolveSudoku/src/Graph.cpp"
#include "/home/vitorsergio/Área de Trabalho/Programa_ResolveSudoku/src/Sudoku.cpp"

using namespace std;

int main() {
    clock_t start, end;
    // Verifica o tempo de execução
    start = clock();
    setlocale(LC_ALL, "Portuguese_Brazil"); // Definir locale a partir da variável de ambiente LANG

    // Caminho completo dos arquivos de entrada
    string fileDirectory = "/home/vitorsergio/Área de Trabalho/Programa_ResolveSudoku/data/";

    Sudoku sudoku; // Cria uma instância da classe Sudoku

    int Backtracking_ou_WelshPowell;

    // Lê os dados do arquivo e implanta na instância do Sudoku
    bool read = sudoku.loadBoardFromFile(fileDirectory+"sudoku_data_5.txt");
    cout << "Qual algoritimo voce gostaria de usar? ([0] para o algoritimo Welsh Powell, [1] para o algoritimo Backtracking):" << endl;
    cin >> Backtracking_ou_WelshPowell;

    if (read) {

        cout << "Numero de pre-cores do grafo: " << endl;
        cout << sudoku.getPreColorSize() << endl << endl;

        cout << "Conjunto de cores unicas: " << endl;
        sudoku.getUniqueColors();
        cout << endl << endl;

        cout  << "Tabuleiro pre-colorido: ";
        sudoku.showFullBoardwelshPowell();

        if (!Backtracking_ou_WelshPowell){
            // Aplica o algoritmo para colorir Welsh Powell
            sudoku.welshPowellAlgorithm();

            cout << "\nTabuleiro com a resolucao completa ou parcial utilizando o Welsh Powell:";
            sudoku.showFullBoardwelshPowell();

        }else{
            // Aplica o algoritmo Backtracking
            sudoku.backtrackingAlgorithm();

            cout << "\nTabuleiro com a resolucao completa ou parcial utilizando o Backtracking:";
            sudoku.showFullBoardwelshPowell();
        }

    } else cout << "Impossivel ler os dados do arquivo. Verifique se o nome/caminho do mesmo esta correto!";
    end = clock();
    // Verifica o tempo de execução
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "\nO tempo gasto pelo programa é: " << fixed 
         << time_taken << setprecision(5);
    cout << " sec " << endl;
}