
#pragma once

#include <vector>
#include <random>

using Matrix = std::vector<std::vector<int>>;

Matrix createMatrix(int n, int low, int high, std::mt19937& generator);
void printMatrix(const Matrix& matrix);