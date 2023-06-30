// Lincoln Martins de Oliveira                                                  2021008452                      Data: 29/06/2023
// Breve comentario sobre o codigo: 
// Coordena a execução das etapas necessárias para resolver um jogo de Sudoku utilizando os algoritmos implementados.
//----------------------------------------------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <locale.h>

#include "D:\Documentos\Desktop\Programa_ResolveSudoku\src\graph.cpp"
#include "D:\Documentos\Desktop\Programa_ResolveSudoku\src\sudoku.cpp"

using namespace std;

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil"); // Definir locale a partir da variável de ambiente LANG

    // Caminho completo dos arquivos de entrada
    string fileDirectory = "D:\\Documentos\\Desktop\\Programa_ResolveSudoku\\data\\";

    Sudoku sudoku; // Cria uma instância da classe Sudoku

    int Backtracking_ou_WelshPowell;

    // Lê os dados do arquivo e implanta na instância do Sudoku
    bool read = sudoku.loadBoardFromFile(fileDirectory+"sudoku_data_10.txt");
    cout << "Qual algoritimo voce gostaria de usar (0 para o algoritimo Welsh Powell, 1 para o algoritimo Backtracking):" << endl;
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

            cout << "Tabuleiro com a resolucao completa ou parcial utilizando o Welsh Powell:";
            sudoku.showFullBoardwelshPowell();

        }else{
            // Aplica o algoritmo Backtracking
            sudoku.backtrackingAlgorithm();

            cout << "Tabuleiro com a resolucao completa ou parcial utilizando o Backtracking:";
            sudoku.showFullBoardwelshPowell();
        }

    } else cout << "Impossivel ler os dados do arquivo. Verifique se o nome/caminho do mesmo esta correto!";

}