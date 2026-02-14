#include <iostream>
#include <sstream>
#include <future>
#include <atomic>
#include <iomanip>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

atomic<int> encontrado(-1);

//Validacion de entrada de digito
int entrada(){
    char input;
    cin >> input;
    if(isdigit(input)) {
        return input - '0';
    }
    return -1;
}

//Temporizador de ejecución
auto iniciarTemporizador(){
    return chrono::high_resolution_clock::now();
}

//Calculo del tiempo de ejecución
void tiempoEjecución(chrono::high_resolution_clock::time_point comienzo){
    auto terminar = chrono::high_resolution_clock::now();
    auto duracion = chrono::duration_cast<chrono::microseconds>(terminar - comienzo);
    cout << "Tiempo de ejecución: " << duracion.count() << " microsegundos" << endl;
}

//Funcion de busqueda para el algoritmo paralelo
void buscar(int pin, int inicio, int final, promise<int>& resultado){
    for (int i = inicio; i < final; i++){
        if(encontrado.load()) return;

        if(i == pin){
            encontrado.store(true);
            resultado.set_value(i);
            return;
        }
    }
}

//Funcion del algoritmo paralelo
void paralelo(int pin) {
    int hilos = thread::hardware_concurrency(); // Usar el número de hilos disponibles en el sistema
    int rango = 10000 / hilos;
    vector<promise<int>> promesas(hilos);
    vector<future<int>> futuros;
    vector<thread> trabajadores;

    auto comienzo = iniciarTemporizador();

    // Crear hilos para buscar en rangos específicos
    for (int i = 0; i < hilos; i++) {
        int inicio = i * rango;
        int final = (i == hilos - 1) ? 10000 : (i + 1) * rango;
        futuros.push_back(promesas[i].get_future());
        trabajadores.emplace_back(buscar, pin, inicio, final, ref(promesas[i]));
    }

    // Esperar a que todos los hilos terminen
    for (auto& t : trabajadores) {
        if (t.joinable()) t.join();
    }

    // Verificar si se encontró el pin
    if (encontrado.load() != -1) {
        cout << "Pin encontrado (Paralelo): " << encontrado.load() << endl;
    }

    cout << "Busqueda paralela terminada." << endl;
    tiempoEjecución(comienzo);
}

//Funcion del algoritmo de fuerza bruta
void bruto(int pin){ 
    int intentos = 0;
    int adivinanza = 0;

    auto comienzo = iniciarTemporizador();   
    
    //Iterar a través de todas las posibles combinaciones de 4 dígitos (0000 a 9999)
    for (int i = 0; i <= 9999; i++) {
        intentos++;     
        adivinanza = i;
        
        if (adivinanza == pin) {
            cout << "Pin encontrado: " << adivinanza << endl;
            break;
        }
    }

    tiempoEjecución(comienzo);
}

//Funcion del menu para ejecutar ambos algoritmos
void menu(){
    int pin = rand() % 10000;

    cout << "Algoritmo paralelo" << endl;
    paralelo(pin);

    cout << "Algoritmo de fuerza bruta" << endl;
    bruto(pin);
}

int main(){
    srand(time(0));
    menu();
}