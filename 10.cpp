#include <iostream>
using namespace std;

// Constexpr лямбда для проверки простоты числа
constexpr auto isPrime = [](int n) constexpr {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
};

int main() {
    // Проверка на этапе компиляции
    constexpr bool prime7 = isPrime(7);
    constexpr bool prime10 = isPrime(10);
    constexpr bool prime1 = isPrime(1);
    constexpr bool prime2 = isPrime(2);
    constexpr bool prime997 = isPrime(997); // большое простое число
    
    // Вывод результатов
    cout << "7 is prime: " << (prime7 ? "true" : "false") << endl;
    cout << "10 is prime: " << (prime10 ? "true" : "false") << endl;
    cout << "1 is prime: " << (prime1 ? "true" : "false") << endl;
    cout << "2 is prime: " << (prime2 ? "true" : "false") << endl;
    cout << "997 is prime: " << (prime997 ? "true" : "false") << endl;
    
    // Проверка во время выполнения (тоже работает)
    int num;
    cout << "\nEnter a number to check: ";
    cin >> num;
    cout << num << " is prime: " << (isPrime(num) ? "true" : "false") << endl;
    
    return 0;
}
