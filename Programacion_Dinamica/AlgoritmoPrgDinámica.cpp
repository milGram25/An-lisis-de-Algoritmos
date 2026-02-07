#include <iostream>
#include <vector>

using namespace std;

// Equipo: 
// - Milton García Romo
// - Carlos González Rodríguez 
// - Christopher Santana

// Problema de Corte de Varillas (Rod Cutting Problem):
//      Determina la mejor manera de cortar una varilla de longitud n para 
//      maximizar el valor total obtenido, dado un conjunto de precios para cada longitud de corte.

// Programación Dinámica (Top-Down con Memoización)


// Función que calcula el máximo valor de venta
// n = longitud de la varilla
// prices = arreglo con precios (prices[i-1] es el precio de longitud i)
int rodCutting(int n, vector<int>& prices) {
    // dp[i] almacena el máximo valor para una varilla de longitud i
    vector<int> dp(n + 1, 0);
    
    // Calculamos para cada longitud desde 1 hasta n
    for (int i = 1; i <= n; i++) {
        int maxValue = 0;
        
        // Probamos todos los posibles primeros cortes
        // j es el tamaño del primer pedazo que cortamos
        for (int j = 1; j <= i; j++) {
            // prices[j-1] = precio del pedazo de tamaño j
            // dp[i-j] = máximo valor del resto de la varilla
            maxValue = max(maxValue, prices[j-1] + dp[i-j]);
        }
        
        // Guardamos el máximo valor para longitud i
        dp[i] = maxValue;
    }
    
    // Retornamos el máximo valor para longitud n
    return dp[n];
}

int main() {
    // Arreglo de precios: prices[0]=precio de longitud 1, prices[1]=precio de longitud 2, etc.
    vector<int> prices = {1, 5, 8, 9, 10, 17, 17, 20};
    
    // Longitud de la varilla
    int n;

    cout << "Ingrese la longitud de la varilla:" << endl;
    cin >> n;
    
    // Calculamos el máximo valor
    int resultado = rodCutting(n, prices);
    
    // Mostramos el resultado
    cout << "Máximo valor: " << resultado << endl;
    
    return 0;
}