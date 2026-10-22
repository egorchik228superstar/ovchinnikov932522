#include "method.h"
#include <iostream>  .
#include <random>    
#include <chrono>  
#include <clocale>   
#include <vector>    





int main() {
    const int n = 4;
    int path[n] = { 0, 1, 2, 3 };
    int count = 0;

    do {
        for (int i = 0; i < n; i++) {
            std::cout << path[i] << " ";
        }

        std::cout << "\n";
        count++;
    } while (next_deykstra_permutation(path, n));

    std::cout << "Количество перестановок: " << count << "\n";

    return 0;
}