#pragma once

#include <vector>
#include <random>

using Matrix = std::vector<std::vector<int>>;

Matrix createMatrix(int n, int low, int high,
    std::mt19937& generator);

void printMatrix(const Matrix& matrix);

bool nextPermutation(std::vector<int>& order);

long long routeCost(const Matrix& matrix,
    const std::vector<int>& order, int start);

void solveExact(const Matrix& matrix, int start,
    long long& minCost, long long& maxCost,
    std::vector<int>& minRoute,
    std::vector<int>& maxRoute,
    long long& count);

void printRoute(const std::vector<int>& order, int start);