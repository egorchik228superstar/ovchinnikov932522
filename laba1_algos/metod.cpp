#include "metod.h"
#include <iostream>

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