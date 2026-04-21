#include <iostream>
#include <chrono> // Standard library for time

int leer_numero() {
    int n;

    std::cout << "Enter an integer: ";

    // While the input fails OR is not followed by a newline
    while (!(std::cin >> n)) {
        std::cout << "Invalid input. Please enter a valid integer: ";
        
        // Clear the error flag so cin can be used again
        std::cin.clear(); 
        
        // Discard the invalid input in the buffer up to the next newline
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return n;
}

int main() {
    int n=0;
    char salir='n';

    do{
    n=0;
    while(n==0) {
        n = leer_numero();
    }

    // Start the timer
    auto start = std::chrono::high_resolution_clock::now();

    // Code to measure
    for(int i = 0; i < n; ++i); 

    // Stop the timer
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate duration in milliseconds
    std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cout << "Waited for " << elapsed.count() << " ms\n";

    std::cout << "Do you want to continue? (s/n): ";
    std::cin >> salir;
    } while (salir == 's' || salir == 'S');
    return 0;
}
