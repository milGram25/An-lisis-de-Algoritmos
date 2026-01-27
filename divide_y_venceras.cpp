#include <iostream>
using namespace std;

//Algoritmo QuickSort para ordenar el arreglo
void quicksort(int arr[], int n) {
    int pivote = arr[0];
    int menores[n], mayores[n];
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
        quicksort(menores, cuenta_menores);
    }
    if(cuenta_mayores > 1) {
        quicksort(mayores, cuenta_mayores);
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
}

void busqueda_binaria(int arr[], int n){
    int izquierda = 0;
    int derecha = n-1;
    cout << "\nIngrese el numero a buscar: ";
    int objetivo;
    cin >> objetivo;
    int resultado = -1;

    while (izquierda <= derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;
        if (arr[medio] == objetivo) {
            resultado = medio; // Elemento encontrado
        }
        if (arr[medio] < objetivo) {
            izquierda = medio + 1; // Buscar en la mitad derecha
        } else {
            derecha = medio - 1; // Buscar en la mitad izquierda
        }
    }

    if (resultado != -1) {
        cout << "Elemento encontrado en el índice: " << resultado << endl;
    } else {
        cout << "Elemento no encontrado." << endl;
    }
    return;
}

void menu(int arr[], int n){
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
                //Aun no funciona, no lo elijan
                cout << "Opcion 2 seleccionada: Nuevo arreglo\n";
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
    // Generar arreglo de numeros
    cout << "Ingrese el numero de elementos: ";
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100; // Numeros aleatorios entre 0 y 99
    }

    // Mostrar arreglo generado
    cout << "Arreglo generado: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    //Ordenar arreglo usando QuickSort
    quicksort(arr, n);
    cout << "Arreglo ordenado: ";
    for(int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    //Menu de opciones
    menu(arr, n);
    
}