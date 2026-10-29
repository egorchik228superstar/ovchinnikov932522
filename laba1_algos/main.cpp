#include "metod.h"

int main()
{
    std::mt19937 generator(42);

    Matrix matrix = createMatrix(4, 10, 100, generator);
    printMatrix(matrix);

    return 0;
}