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
    std::vector<int> greedyRoute;

    solveExact(matrix, start, minCost, maxCost,
        minRoute, maxRoute, count);

    long long greedyCost = solveGreedy(matrix, start, greedyRoute);

    std::cout << "Minimum: " << minCost << '\n';
    printRoute(minRoute, start);

    std::cout << "Maximum: " << maxCost << '\n';
    printRoute(maxRoute, start);

    std::cout << "Greedy: " << greedyCost << '\n';
    printRoute(greedyRoute, start);

    std::cout << "Quality: "
        << solutionQuality(minCost, maxCost, greedyCost)
        << "%\n";

    return 0;
}