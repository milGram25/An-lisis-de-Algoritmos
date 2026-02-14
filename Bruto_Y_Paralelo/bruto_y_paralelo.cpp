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

int entrada(){
    char input;
    cin >> input;
    if(isdigit(input)) {
        return input - '0';
    }
    return -1;
}

auto iniciarTemporizador(){
    return chrono::high_resolution_clock::now();
}

void tiempoEjecución(chrono::high_resolution_clock::time_point comienzo){
    auto terminar = chrono::high_resolution_clock::now();
    auto duracion = chrono::duration_cast<chrono::microseconds>(terminar - comienzo);
    cout << "Tiempo de ejecución: " << duracion.count() << " microsegundos" << endl;
}

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

void paralelo(int pin) {
    int hilos = thread::hardware_concurrency(); // Use all available cores
    int rango = 10000 / hilos;
    vector<promise<int>> promesas(hilos);
    vector<future<int>> futuros;
    vector<thread> trabajadores;

    auto comienzo = iniciarTemporizador();

    for (int i = 0; i < hilos; i++) {
        int inicio = i * rango;
        int final = (i == hilos - 1) ? 10000 : (i + 1) * rango;
        futuros.push_back(promesas[i].get_future());
        trabajadores.emplace_back(buscar, pin, inicio, final, ref(promesas[i]));
    }

    for (auto& t : trabajadores) {
        if (t.joinable()) t.join();
    }

    if (encontrado.load() != -1) {
        cout << "Pin encontrado (Paralelo): " << encontrado.load() << endl;
    }

    cout << "Busqueda paralela terminada." << endl;
    tiempoEjecución(comienzo);
}

void bruto(int pin){ 
    int intentos = 0;
    int adivinanza = 0;

    auto comienzo = iniciarTemporizador();   
    
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