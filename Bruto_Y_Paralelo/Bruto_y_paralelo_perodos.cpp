#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

int main() {
    srand(time(0));
    
    int pin = 1000 + rand() % 9000;
    auto start = chrono::high_resolution_clock::now();
    cout << "Pin: " << pin << endl;
    
    int intentos = 0;
    int adivinanza = 0;
    
    for (int i = 0; i <= 9999; i++) {
        intentos++;     
        adivinanza = i;
        
        if (adivinanza == pin) {
            cout << "Pin encontrado" << endl;
           
            break;
        } else {
            
        }
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Tiempo de ejecucion: " << duration.count() << " microsegundos" << endl;
    
    return 0;
}
