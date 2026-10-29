#include "metod.h"
#include <iostream>
#include <clocale>

int main()
{
    setlocale(LC_ALL, "");

    std::cout << std::fixed;
    std::cout.precision(6);

    std::cout << "1 - Пример из лекции\n";
    std::cout << "2 - Сравнение точного алгоритма и эвристики\n";
    std::cout << "3 - Исследование роста времени перебора\n";
    std::cout << "Выберите режим: ";

    int mode;

    if (!(std::cin >> mode))
    {
        std::cout << "Ошибка ввода.\n";
        return 1;
    }

    if (mode == 1)
    {
        Matrix matrix = {
            { 0, 10, 5, 17 },
            { 6, 0, 1, 1 },
            { 9, 10, 0, 4 },
            { 16, 3, 7, 0 }
        };

        int start;

        std::cout << "Введите начальный город (от 1 до 4): ";

        if (!(std::cin >> start) || start < 1 || start > 4)
        {
            std::cout << "Некорректный номер начального города.\n";
            return 1;
        }

        std::cout << "\nМатрица стоимостей:\n";
        printMatrix(matrix);

        runExperiment(matrix, start - 1, 1);
    }
    else if (mode == 2)
    {
        runExperiments();
    }
    else if (mode == 3)
    {
        runGrowthExperiment();
    }
    else
    {
        std::cout << "Такого режима нет.\n";
        return 1;
    }

    return 0;
}