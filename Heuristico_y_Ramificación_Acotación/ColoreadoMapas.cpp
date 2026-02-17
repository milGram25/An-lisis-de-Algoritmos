//Algoritmo de Coloreado de Mapas//
//Heurístico y Ramificación-Acotación//
//Equipo: García Romo Milton, González Rodríguez Carlos, Santana Christopher.

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <ctime>   
#include <cstdlib> 

using namespace std;

// Verifica si es seguro asignar un color
bool esSeguro(int vertice, int color, const vector<vector<int>>& grafo, const vector<int>& colores) {
    for (int vecino : grafo[vertice]) {
        if (colores[vecino] == color) return false;
    }
    return true;
}

// Algoritmo de búsqueda (Branch and Bound)
bool buscarSolucion(int idx, const vector<int>& orden, const vector<vector<int>>& grafo, vector<int>& colores, int numColores) {
    if (idx == orden.size()) return true;
    int vertice = orden[idx];

    for (int c = 1; c <= numColores; c++) {
        if (esSeguro(vertice, c, grafo, colores)) {
            colores[vertice] = c;
            if (buscarSolucion(idx + 1, orden, grafo, colores, numColores)) return true;
            colores[vertice] = 0;
        }
    }
    return false;
}

int main() {
    srand(time(0)); // Inicializa el generador de números aleatorios
    int n;

    cout << "Ingrese la cantidad de paises: ";
    cin >> n;

    if (n <= 0) return 0;

    // Generación de fronteras al azar
    vector<vector<int>> grafo(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            // Se genera una robabilidad del 30% de que haya una frontera entre i y j
            if ((rand() % 100) < 30) {
                grafo[i].push_back(j);
                grafo[j].push_back(i);
            }
        }
    }

    // Heurística: Ordenar países por cantidad de fronteras automáticamente
    vector<int> orden(n);
    iota(orden.begin(), orden.end(), 0);
    sort(orden.begin(), orden.end(), [&](int a, int b) {
        return grafo[a].size() > grafo[b].size();
    });

    vector<int> solucionFinal(n, 0);
    int numColores = 1;

    // Ejecución del algoritmo
    while (true) {
        fill(solucionFinal.begin(), solucionFinal.end(), 0);
        if (buscarSolucion(0, orden, grafo, solucionFinal, numColores)) break;
        numColores++;
    }

    cout << "\n--- Resultado del Coloreado Aleatorio ---" << endl;
    cout << "Numero minimo de colores encontrados: " << numColores << endl;
    cout << "------------------------------------------" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Pais " << i << " (Fronteras: " << grafo[i].size() << ") -> Color: " << solucionFinal[i] << endl;
    }

    return 0;
}