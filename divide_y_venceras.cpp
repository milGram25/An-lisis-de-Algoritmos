#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

int entrada_numero(){
    char entrada;
    cin >> entrada;
    if (isdigit(entrada)) {
        return entrada - '0';
    }
    return -1;
}

void mostrar_arreglo(vector<int> arr, int n){
    cout << "Arreglo generado: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

//Algoritmo QuickSort para ordenar el arreglo
vector<int> quicksort(vector<int> arr, int n) {
    int pivote = arr[0];
    vector<int> menores(n);
    vector<int> mayores(n);
    int cuenta_menores = 0;
    int cuenta_mayores = 0;

    // Dividir el arreglo en menores y mayores que el pivote
    for(int i = 1; i < n; i++) {
        if(arr[i] < pivote) {
            menores[cuenta_menores] = arr[i];
            cuenta_menores++;
        } else {
            mayores[cuenta_mayores] = arr[i];
            cuenta_mayores++;
        }
    }

    // Llamadas recursivas para ordenar los subarreglos
    if(cuenta_menores > 1) {
        menores =quicksort(menores, cuenta_menores);
    }
    if(cuenta_mayores > 1) {
        mayores = quicksort(mayores, cuenta_mayores);
    }

    // Combinar los resultados
    int index = 0;
    for(int i = 0; i < cuenta_menores; i++) {
        arr[index] = menores[i];
        index++;
    }
    arr[index] = pivote;
    index++;
    for(int i = 0; i < cuenta_mayores; i++) {
        arr[index] = mayores[i];
        index++;
    }

    return arr;
}

vector<int> generar_arreglo(){
    cout << "Ingrese el numero de elementos: ";
    int n = entrada_numero();
    if (n <= 0) {
        cout << "Entrada invalida. Usando valor por defecto de 10.\n";
        n = 10;
    }
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100; // Numeros aleatorios entre 0 y 99
    }
    mostrar_arreglo(arr, n);
    return arr;
}

vector<int> iniciar_quicksort(vector<int> arr, int n){
    arr = quicksort(arr, n);
    cout << "Arreglo ordenado: ";
    for(int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    return arr;
}

void busqueda_binaria(vector<int> arr, int n){
    int izquierda = 0;
    int derecha = n-1;
    cout << "\nIngrese el numero a buscar: ";
    int objetivo = entrada_numero();

    if (objetivo == -1) {
        cout << "Entrada invalida.\n";
        return;
    }
    
    int resultado = -1;

    while (izquierda <= derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;
        if (arr[medio] == objetivo) {
            resultado = medio; // Elemento encontrado
            break;
        }
        if (arr[medio] < objetivo) {
            izquierda = medio + 1; // Buscar en la mitad derecha
        } else {
            derecha = medio - 1; // Buscar en la mitad izquierda
        }
    }

    if (resultado != -1) {
        cout << "Elemento encontrado en la posicion: " << resultado+1 << endl;
    } else {
        cout << "Elemento no encontrado." << endl;
    }
    return;
}

void menu(vector<int> arr, int n){
    int opcion;
    do{
        cout << "Menu de opciones:\n";
        cout << "1. Buscar elemento usando Busqueda Binaria\n";
        cout << "2. Nuevo arreglo\n";
        cout << "3. Salir\n";
        cin >> opcion;
        switch(opcion){
            case 1:
                cout << "Opcion 1 seleccionada: Busqueda Binaria\n";
                busqueda_binaria(arr, n);
                break;
            case 2:
                cout << "Opcion 2 seleccionada: Nuevo arreglo\n";
                arr = generar_arreglo();
                n = arr.size();
                iniciar_quicksort(arr, n);
                break;
            case 3:
                cout << "Saliendo del programa.\n";
                return;
            default:
                cout << "Opcion invalida. Intente de nuevo.\n";
        }
    } while (true);
}
int main(){
    srand(time(0)); // Semilla para numeros aleatorios

    // Generar arreglo de numeros
    vector<int> arr = generar_arreglo();
    int n = arr.size();

    //Ordenar arreglo usando QuickSort
    arr = iniciar_quicksort(arr, n);

    //Menu de opciones
    menu(arr, n);
    
}