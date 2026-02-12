#include <iostream>
#include <sstream>
#include <future>
#include <atomic>
#include <iomanip>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

atomic<bool> encontrado(false);

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

int main(){
    int hilos = 1;
    int rango = 10000/hilos;
    vector<future<int>> futuros;
    vector<promise<int>> promesas(hilos);

    srand(time(nullptr));

    int pin = rand() % 10000;
    auto comienzo = chrono::high_resolution_clock::now();

    for(int i = 0; i < hilos; i++){
        int inicio = i * rango;
        int final = (i == hilos - 1) ? 10000 : (i + 1) * rango;

        futuros.push_back(promesas[i].get_future());
        thread t(buscar, pin, inicio, final, ref(promesas[i]));
        t.detach();
    }

    while(!encontrado.load()){}

    auto terminar = chrono::high_resolution_clock::now();
    auto duracion = chrono::duration_cast<chrono::microseconds>(terminar - comienzo);

    cout << "Valor encontrado: " << futuros[0].get() << endl;
    cout << "Tiempo de ejecución: " << duracion.count() << " microsegundos" << endl;
}