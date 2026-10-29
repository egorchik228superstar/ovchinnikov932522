#include "metod.h"
#include <iostream>

int main()
{
    Matrix matrix = {
        { 0, 10, 5, 17 },
        { 6, 0, 1, 1 },
        { 9, 10, 0, 4 },
        { 16, 3, 7, 0 }
    };

    int start = 0;

    long long minCost = 0;
    long long maxCost = 0;
    long long count = 0;

    std::vector<int> minRoute;
    std::vector<int> maxRoute;

    solveExact(matrix, start, minCost, maxCost,
        minRoute, maxRoute, count);

    printMatrix(matrix);

    std::cout << "\nMinimum: " << minCost << '\n';
    printRoute(minRoute, start);

    std::cout << "Maximum: " << maxCost << '\n';
    printRoute(maxRoute, start);

    std::cout << "Routes checked: " << count << '\n';

    return 0;
}