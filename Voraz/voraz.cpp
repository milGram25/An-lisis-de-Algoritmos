#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

//EQUIPO:
// - Milton García Romo
// - Carlos González Rodríguez
// - Christopher Santana

// Algoritmo Voraz (Greedy)

//Ordenar x cantidad de tareas por su 'y' tiempo de finalizacion ('y' numero que sea entre 1-100)

// Estructura para representar una tarea
struct Tarea {
    int id;
    int tiempo;
};

// Función para comparar tareas por tiempo de finalización
bool compararTareas(const Tarea& a, const Tarea& b) {
    return a.tiempo < b.tiempo;
}

void algoritmoVoraz(vector<Tarea>& tareas) {
    // Ordenar las tareas por tiempo de finalización
    sort(tareas.begin(), tareas.end(), compararTareas);

    cout << "\nOrden de Tareas Basado en el Algoritmo Voraz (De la más rápida a la más lenta):"<<endl;
    
    int tiempoAcumulado = 0; 
    int tiempoEsperaTotal = 0;
    
    for (int i = 0; i < tareas.size(); i++) {
        tiempoAcumulado += tareas[i].tiempo;
        tiempoEsperaTotal += tiempoAcumulado - tareas[i].tiempo;

        cout << "Tarea ID: " << tareas[i].id 
        << ", Tiempo de Ejecución: " << tareas[i].tiempo 
        << ", Tiempo de Espera Acumulado: " << tiempoAcumulado - tareas[i].tiempo << endl;
    }

    cout << "\nTiempo de Espera Total: " << tiempoEsperaTotal << endl;
}

int main () {
    
    srand(time(0)); // Semilla para números aleatorios
    int n;

    cout << "Ingrese el numero de tareas que tiene pendiente:" << endl;
    cin >> n;
    cout << endl;

    //Generar tareas aleatorias
    vector<Tarea> tareas(n);
    for (int i = 0; i < n; i++) {
        tareas[i].id = i + 1; // IDs de tareas comienzan desde 1
        tareas[i].tiempo = rand() % 100 + 1; // Tiempo aleatorio entre 1 y 100

        cout << "Tarea ID: " << tareas[i].id 
             << ", Tiempo de Ejecución: " << tareas[i].tiempo << endl;
    }

    algoritmoVoraz(tareas);
}