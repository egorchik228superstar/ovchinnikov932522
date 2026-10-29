#include "metod.h"
#include <iostream>

Matrix createMatrix(int n, int low, int high, std::mt19937& generator)
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