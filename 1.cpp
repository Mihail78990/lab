#include <iostream>
#include <cmath>

using namespace std;

struct Pair {
    double first;  
    int second;     
    
    // Метод инициализации
    bool init(double f, int s) {
        if (f == 0.0 && s <= 0) {
            cout << "Ошибка: 0 в неположительной степени!" << endl;
            return false;
        }
        first = f;
        second = s;
        return true;
    }
    // Ввод с клавиатуры
    bool read() {
        cout << "Введите дробное число (основание): ";
        cin >> first;
        cout << "Введите целое число (показатель степени): ";
        cin >> second;
        
        // Проверка корректности
        if (first == 0.0 && second <= 0) {
            cout << "Ошибка: 0 в неположительной степени!" << endl;
            return false;
        }
        return true;
    }
    // Вывод на экран
    void display() const {
        cout << "(" << first << ", " << second << ")";
    }
    // Возведение в степень
    bool power(double &result) const {
        if (first == 0.0) {
            if (second == 0) {
                result = 1.0; 
                return true;
            } else if (second > 0) {
                result = 0.0;
                return true;
            } else {
                cout << "Ошибка: деление на ноль!" << endl;
                return false;
            }
        }
        
        // Ручное вычисление степени
        if (second == 0) {
            result = 1.0;
        } else if (second > 0) {
            result = 1.0;
            for (int i = 0; i < second; i++) {
                result *= first;
            }
        } else {
            result = 1.0;
            for (int i = 0; i < -second; i++) {
                result *= first;
            }
            result = 1.0 / result;
        }
        return true;
    }
};

// Внешняя функция для создания структуры
bool make_Pair(double first, int second, Pair &result) {
    if (first == 0.0 && second <= 0) {
        cout << "Ошибка создания Pair: 0 в неположительной степени!" << endl;
        return false;
    }
    
    result.first = first;
    result.second = second;
    return true;
}

int main() {
    cout << "=== Демонстрация работы со структурой-парой ===\n\n";
    cout << "1. Создание объекта с помощью init:\n";
    Pair p1;
    if (p1.init(2.5, 3)) {
        cout << "Объект p1: ";
        p1.display();
        double power_result;
        if (p1.power(power_result)) {
            cout << "\nРезультат возведения в степень: " << power_result << endl;
        }
    }
    cout << endl;
    cout << "2. Создание объекта с помощью make_Pair:\n";
    Pair p2;
    if (make_Pair(-3.0, 4, p2)) {
        cout << "Объект p2: ";
        p2.display();
        double power_result;
        if (p2.power(power_result)) {
            cout << "\nРезультат возведения в степени: " << power_result << endl;
        }
    }
    cout << endl;
    cout << "3. Создание объекта с помощью ввода:\n";
    Pair p3;
    if (p3.read()) {
        cout << "Объект p3: ";
        p3.display();
        double power_result;
        if (p3.power(power_result)) {
            cout << "\nРезультат возведения в степень: " << power_result << endl;
        }
    }
    cout << endl;
    
    cout << "4. Демонстрация работы с массивом объектов:\n";
    const int SIZE = 3;
    Pair arr[SIZE];
  
    if (arr[0].init(4.0, 2)) {
        cout << "arr[0] инициализирован успешно" << endl;
    }
    
    if (make_Pair(0.5, -2, arr[1])) {
        cout << "arr[1] создан успешно" << endl;
    }
    
    cout << "Введите данные для третьего элемента массива:\n";
    if (arr[2].read()) {
        cout << "arr[2] введен успешно" << endl;
    }
    
    cout << "\nМассив объектов и результаты возведения в степень:\n";
    for (int i = 0; i < SIZE; i++) {
        cout << "arr[" << i << "] = ";
        arr[i].display();
        double power_result;
        if (arr[i].power(power_result)) {
            cout << " -> " << power_result << endl;
        } else {
            cout << " -> ошибка вычисления" << endl;
        }
    }
    cout << endl;
    
    cout << "5. Демонстрация различных случаев:\n";
    Pair test_cases[6];
    double test_results[6];
    bool test_success[6];
    // Тестовые случаи
    test_cases[0].init(3.0, 2);
    test_cases[1].init(2.0, -3);
    test_cases[2].init(-2.0, 4);
    test_cases[3].init(-2.0, 3);
    test_cases[4].init(0.0, 5);
    test_cases[5].init(7.5, 0);
    for (int i = 0; i < 6; i++) {
        test_success[i] = test_cases[i].power(test_results[i]);
    }
    // Вывод результатов тестов
    if (test_success[0]) cout << "3.0^2 = " << test_results[0] << endl;
    if (test_success[1]) cout << "2.0^(-3) = " << test_results[1] << endl;
    if (test_success[2]) cout << "(-2.0)^4 = " << test_results[2] << endl;
    if (test_success[3]) cout << "(-2.0)^3 = " << test_results[3] << endl;
    if (test_success[4]) cout << "0.0^5 = " << test_results[4] << endl;
    if (test_success[5]) cout << "7.5^0 = " << test_results[5] << endl;
    
    return 0;
}
