#include "method.h"
#include <iostream>  .
#include <random>    
#include <clocale>   
#include <vector>    

bool next_deykstra_permutation(int* path, int n) {
    
    int i = n - 2;

    while (i >= 1 && path[i] >= path[i + 1]) {
        i--;
    }

    
    if (i < 1) {
        return false;
    }

    
    int j = n - 1;

    while (path[j] <= path[i]) {
        j--;
    }

  
    int temp = path[i];
    path[i] = path[j];
    path[j] = temp;

   
    int left = i + 1;
    int right = n - 1;

    while (left < right) {
        temp = path[left];
        path[left] = path[right];
        path[right] = temp;

        left++;
        right--;
    }

    return true;
}   
