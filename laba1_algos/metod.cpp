#include "metod.h"
#include <iostream>
#include <chrono>

Matrix createMatrix(int n, int low, int high,
    std::mt19937& generator)
{
    Matrix matrix(n, std::vector<int>(n, 0));
    std::uniform_int_distribution<int> distribution(low, high);

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (i != j)
                matrix[i][j] = distribution(generator);
        }
    }

    return matrix;
}

void printMatrix(const Matrix& matrix)
{
    for (const auto& row : matrix)
    {
        for (int value : row)
            std::cout << value << '\t';

        std::cout << '\n';
    }
}

bool nextPermutation(std::vector<int>& order)
{
    int i = static_cast<int>(order.size()) - 2;

    while (i >= 0 && order[i] >= order[i + 1])
        --i;

    if (i < 0)
        return false;

    int j = static_cast<int>(order.size()) - 1;

    while (order[j] <= order[i])
        --j;

    int temp = order[i];
    order[i] = order[j];
    order[j] = temp;

    int left = i + 1;
    int right = static_cast<int>(order.size()) - 1;

    while (left < right)
    {
        temp = order[left];
        order[left] = order[right];
        order[right] = temp;

        ++left;
        --right;
    }

    return true;
}

long long routeCost(const Matrix& matrix,
    const std::vector<int>& order, int start)
{
    long long cost = 0;
    int current = start;

    for (int city : order)
    {
        cost += matrix[current][city];
        current = city;
    }

    cost += matrix[current][start];

    return cost;
}

void solveExact(const Matrix& matrix, int start,
    long long& minCost, long long& maxCost,
    std::vector<int>& minRoute,
    std::vector<int>& maxRoute,
    long long& count)
{
    int n = static_cast<int>(matrix.size());
    std::vector<int> order;

    for (int city = 0; city < n; ++city)
    {
        if (city != start)
            order.push_back(city);
    }

    count = 0;

    do
    {
        long long cost = routeCost(matrix, order, start);

        if (count == 0 || cost < minCost)
        {
            minCost = cost;
            minRoute = order;
        }

        if (count == 0 || cost > maxCost)
        {
            maxCost = cost;
            maxRoute = order;
        }

        ++count;

    } while (nextPermutation(order));
}

void printRoute(const std::vector<int>& order, int start)
{
    std::cout << start + 1;

    for (int city : order)
        std::cout << " -> " << city + 1;

    std::cout << " -> " << start + 1 << '\n';
}

long long solveGreedy(const Matrix& matrix, int start,
    std::vector<int>& route)
{
    int n = static_cast<int>(matrix.size());
    std::vector<bool> visited(n, false);

    route.clear();

    long long cost = 0;
    int current = start;
    visited[start] = true;

    for (int step = 1; step < n; ++step)
    {
        int nearest = -1;

        for (int city = 0; city < n; ++city)
        {
            if (!visited[city])
            {
                if (nearest == -1 ||
                    matrix[current][city] < matrix[current][nearest])
                {
                    nearest = city;
                }
            }
        }

        cost += matrix[current][nearest];
        route.push_back(nearest);
        visited[nearest] = true;
        current = nearest;
    }

    cost += matrix[current][start];

    return cost;
}

double solutionQuality(long long minCost, long long maxCost,
    long long greedyCost)
{
    if (minCost == maxCost)
        return 100.0;

    return 100.0 * (maxCost - greedyCost) / (maxCost - minCost);
}

void runExperiment(const Matrix& matrix, int start, int test)
{
    long long minCost = 0;
    long long maxCost = 0;
    long long count = 0;

    std::vector<int> minRoute;
    std::vector<int> maxRoute;
    std::vector<int> greedyRoute;

    auto begin = std::chrono::steady_clock::now();

    solveExact(matrix, start, minCost, maxCost,
        minRoute, maxRoute, count);

    auto end = std::chrono::steady_clock::now();

    double exactTime =
        std::chrono::duration<double, std::milli>(end - begin).count();

    begin = std::chrono::steady_clock::now();

    long long greedyCost = solveGreedy(matrix, start, greedyRoute);

    end = std::chrono::steady_clock::now();

    double greedyTime =
        std::chrono::duration<double, std::milli>(end - begin).count();

    std::cout << "\nRun #" << test << '\n';

    std::cout << "Exact  | Min: " << minCost
        << " | Max: " << maxCost
        << " | Time: " << exactTime << " ms\n";

    std::cout << "Greedy | Cost: " << greedyCost
        << " | Time: " << greedyTime << " ms\n";

    std::cout << "Quality: "
        << solutionQuality(minCost, maxCost, greedyCost)
        << "%\n";

    std::cout << "Best route: ";
    printRoute(minRoute, start);

    std::cout << "Worst route: ";
    printRoute(maxRoute, start);

    std::cout << "Greedy route: ";
    printRoute(greedyRoute, start);

    std::cout << "Routes checked: " << count << '\n';
}

void runExperiments()
{
    std::mt19937 generator(42);
    std::vector<int> sizes = { 4, 6, 8, 10 };

    int low = 10;
    int high = 100;
    int start = 0;

    for (int n : sizes)
    {
        std::cout << "\n========================================\n";
        std::cout << "N = " << n
            << " | Costs: " << low << ".." << high
            << " | Start: " << start + 1 << '\n';
        std::cout << "========================================\n";

        for (int test = 1; test <= 4; ++test)
        {
            Matrix matrix = createMatrix(n, low, high, generator);
            runExperiment(matrix, start, test);
        }
    }
}

void runGrowthExperiment()
{
    std::mt19937 generator(123);

    std::cout << "\nCosts: 10..100 | Start: 1\n";
    std::cout << "N\tRoutes\tTime_ms\n";

    for (int n = 4; n <= 13; ++n)
    {
        Matrix matrix = createMatrix(n, 10, 100, generator);

        long long minCost = 0;
        long long maxCost = 0;
        long long count = 0;

        std::vector<int> minRoute;
        std::vector<int> maxRoute;

        auto begin = std::chrono::steady_clock::now();

        solveExact(matrix, 0, minCost, maxCost,
            minRoute, maxRoute, count);

        auto end = std::chrono::steady_clock::now();

        double time =
            std::chrono::duration<double, std::milli>(end - begin).count();

        std::cout << n << '\t' << count << '\t' << time << '\n';

        // Следующий размер не запускаем, если текущий занял более 5 секунд.
        if (time >= 5000.0)
        {
            std::cout << "Further growth stopped.\n";
            break;
        }
    }
}