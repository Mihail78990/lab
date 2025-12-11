#include <iostream>
using namespace std;

// =========== C++11 версия (рекурсия) ===========
// Базовый случай для одного аргумента
template<typename T>
T maxOf_11(T arg) {
    return arg;
}

// Рекурсивный случай для нескольких аргументов
template<typename First, typename... Rest>
auto maxOf_11(First first, Rest... rest) {
    auto maxRest = maxOf_11(rest...);
    return (first > maxRest) ? first : maxRest;
}

// =========== C++17 версия (fold expression) ===========
template<typename... Args>
auto maxOf_17(Args... args) {
    return (args > ...);
}

int main() {
    // Тест 1: целые числа
    cout << "maxOf_11(1, 5, 3, 9, 2) = " << maxOf_11(1, 5, 3, 9, 2) << endl;
    cout << "maxOf_17(1, 5, 3, 9, 2) = " << maxOf_17(1, 5, 3, 9, 2) << endl;

    // Тест 2: числа с плавающей точкой
    cout << "maxOf_11(3.14, 2.71, 1.41) = " << maxOf_11(3.14, 2.71, 1.41) << endl;
    cout << "maxOf_17(3.14, 2.71, 1.41) = " << maxOf_17(3.14, 2.71, 1.41) << endl;

    // Тест 3: символы (сравнение по ASCII)
    cout << "maxOf_11('a', 'z', 'm') = " << maxOf_11('a', 'z', 'm') << endl;
    cout << "maxOf_17('a', 'z', 'm') = " << maxOf_17('a', 'z', 'm') << endl;

    // Тест 4: один аргумент
    cout << "maxOf_11(42) = " << maxOf_11(42) << endl;
    cout << "maxOf_17(42) = " << maxOf_17(42) << endl;

    return 0;
}
