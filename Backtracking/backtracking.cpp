#include <iostream>
using namespace std;

const int N = 9;

// Función para imprimir el tablero
void imprimirSudoku(int tablero[N][N]) {
    cout << "Tablero de Sudoku:" << endl;
    for (int fila = 0; fila < N; fila++) {
        for (int col = 0; col < N; col++) {
            cout << tablero[fila][col] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Revisar si se puede colocar un número en una celda
bool esSeguro(int tablero[N][N], int fila, int col, int num) {
    // Verificar fila
    for (int x = 0; x < N; x++)
        if (tablero[fila][x] == num) return false;

    // Verificar columna
    for (int x = 0; x < N; x++)
        if (tablero[x][col] == num) return false;

    // Verificar subcuadriculas
    int inicioFila = fila - fila % 3;
    int inicioCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (tablero[i + inicioFila][j + inicioCol] == num) return false;

    return true;
}

// Algoritmo de backtracking
bool resolverSudoku(int tablero[N][N]) {
    for (int fila = 0; fila < N; fila++) {
        for (int col = 0; col < N; col++) {
            if (tablero[fila][col] == 0) { // celda vacía
                for (int num = 1; num <= 9; num++) {
                    if (esSeguro(tablero, fila, col, num)) {
                        tablero[fila][col] = num;
                        if (resolverSudoku(tablero)) return true;
                        tablero[fila][col] = 0; // backtrack
                    }
                }
                return false; // no hay número válido
            }
        }
    }
    return true; // tablero completo
}

int main() {
    int tablero[N][N] = {
        {0,3,0, 0,7,0, 0,0,0},
        {6,0,0, 1,9,5, 0,0,0},
        {0,9,8, 0,0,0, 5,6,0},
        {8,0,0, 0,6,0, 0,0,3},
        {4,0,0, 8,0,3, 0,0,1},
        {7,0,0, 0,2,0, 0,0,6},
        {0,6,0, 0,0,0, 2,8,0},
        {0,0,0, 4,1,9, 0,0,5},
        {0,0,0, 0,8,0, 0,7,9}
    };

    imprimirSudoku(tablero);

    cout << endl << "Resolviendo el Sudoku...\n" << endl;

    if (resolverSudoku(tablero))
        imprimirSudoku(tablero);
    else
        cout << "El tablero no tiene solución" << endl;


    return 0;
}