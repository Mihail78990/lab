#include <iostream>
#include <cmath>

using namespace std;

// 1. Без спецификации исключений
double triangleArea1(double a, double b, double c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        throw "Стороны треугольника должны быть положительными";
    }
    
    if (a + b <= c || a + c <= b || b + c <= a) {
        throw "Треугольник с такими сторонами не существует";
    }
    
    double p = (a + b + c) / 2.0;
    double area = sqrt(p * (p - a) * (p - b) * (p - c));
    
    // Проверка на корректность вычислений
    double temp = p * (p - a) * (p - b) * (p - c);
    if (temp < 0 || area != area) { // area != area проверяет на NaN
        throw "Ошибка вычисления площади";
    }
    
    return area;
}

// 2. Со спецификацией throw() (не генерирует исключения)
double triangleArea2(double a, double b, double c) throw() {
    // В этой версии мы не генерируем исключения, а возвращаем специальное значение
    if (a <= 0 || b <= 0 || c <= 0) {
        return -1.0; // Код ошибки: отрицательная сторона
    }
    
    if (a + b <= c || a + c <= b || b + c <= a) {
        return -2.0; // Код ошибки: треугольник не существует
    }
    
    double p = (a + b + c) / 2.0;
    double temp = p * (p - a) * (p - b) * (p - c);
    
    if (temp < 0) {
        return -3.0; // Код ошибки: ошибка вычисления
    }
    
    double area = sqrt(temp);
    
    if (area != area) { // Проверка на NaN
        return -4.0; // Код ошибки: NaN результат
    }
    
    return area;
}

// 3. С собственным исключением - пустой класс
class TriangleError {};

double triangleArea3(double a, double b, double c) throw(TriangleError) {
    if (a <= 0 || b <= 0 || c <= 0) {
        throw TriangleError();
    }
    
    if (a + b <= c || a + c <= b || b + c <= a) {
        throw TriangleError();
    }
    
    double p = (a + b + c) / 2.0;
    double temp = p * (p - a) * (p - b) * (p - c);
    
    if (temp < 0) {
        throw TriangleError();
    }
    
    double area = sqrt(temp);
    
    if (area != area) { // Проверка на NaN
        throw TriangleError();
    }
    
    return area;
}

// 4. С собственным исключением - класс с полями
class TriangleException {
private:
    double sideA, sideB, sideC;
    const char* message;
    
public:
    TriangleException(double a, double b, double c, const char* msg)
        : sideA(a), sideB(b), sideC(c), message(msg) {}
    
    const char* getMessage() const { return message; }
    double getSideA() const { return sideA; }
    double getSideB() const { return sideB; }
    double getSideC() const { return sideC; }
    
    void printDetails() const {
        cout << "Ошибка: " << message << endl;
        cout << "Стороны: a=" << sideA << ", b=" << sideB << ", c=" << sideC << endl;
    }
};

double triangleArea4(double a, double b, double c) throw(TriangleException) {
    if (a <= 0 || b <= 0 || c <= 0) {
        throw TriangleException(a, b, c, "Стороны треугольника должны быть положительными");
    }
    
    if (a + b <= c || a + c <= b || b + c <= a) {
        throw TriangleException(a, b, c, "Треугольник с такими сторонами не существует");
    }
    
    double p = (a + b + c) / 2.0;
    double temp = p * (p - a) * (p - b) * (p - c);
    
    if (temp < 0) {
        throw TriangleException(a, b, c, "Ошибка вычисления площади");
    }
    
    double area = sqrt(temp);
    
    if (area != area) { // Проверка на NaN
        throw TriangleException(a, b, c, "Некорректный результат (NaN)");
    }
    
    return area;
}

// 5. С собственным исключением - наследник от базового класса
class BaseException {
public:
    virtual const char* what() const { return "Базовое исключение"; }
    virtual ~BaseException() {}
};

class TriangleBaseException : public BaseException {
private:
    double sideA, sideB, sideC;
    const char* errorMsg;
    
public:
    TriangleBaseException(double a, double b, double c, const char* msg)
        : sideA(a), sideB(b), sideC(c), errorMsg(msg) {}
    
    const char* what() const override { return errorMsg; }
    double getSideA() const { return sideA; }
    double getSideB() const { return sideB; }
    double getSideC() const { return sideC; }
    
    void printDetails() const {
        cout << "TriangleBaseException: " << errorMsg << endl;
        cout << "Стороны: a=" << sideA << ", b=" << sideB << ", c=" << sideC << endl;
    }
};

double triangleArea5(double a, double b, double c) throw(TriangleBaseException) {
    if (a <= 0 || b <= 0 || c <= 0) {
        throw TriangleBaseException(a, b, c, "Стороны треугольника должны быть положительными");
    }
    
    if (a + b <= c || a + c <= b || b + c <= a) {
        throw TriangleBaseException(a, b, c, "Треугольник с такими сторонами не существует");
    }
    
    double p = (a + b + c) / 2.0;
    double temp = p * (p - a) * (p - b) * (p - c);
    
    if (temp < 0) {
        throw TriangleBaseException(a, b, c, "Ошибка вычисления площади");
    }
    
    double area = sqrt(temp);
    
    if (area != area) { // Проверка на NaN
        throw TriangleBaseException(a, b, c, "Некорректный результат (NaN)");
    }
    
    return area;
}

// 6. С разными типами исключений
class MathException {
public:
    virtual const char* what() const { return "Математическая ошибка"; }
};

class InvalidArgument : public MathException {
private:
    const char* msg;
public:
    InvalidArgument(const char* message) : msg(message) {}
    const char* what() const override { return msg; }
};

class CalculationError : public MathException {
private:
    const char* msg;
public:
    CalculationError(const char* message) : msg(message) {}
    const char* what() const override { return msg; }
};

double triangleArea6(double a, double b, double c) throw(InvalidArgument, CalculationError) {
    if (a <= 0 || b <= 0 || c <= 0) {
        throw InvalidArgument("Стороны треугольника должны быть положительными");
    }
    
    if (a + b <= c || a + c <= b || b + c <= a) {
        throw InvalidArgument("Треугольник с такими сторонами не существует");
    }
    
    double p = (a + b + c) / 2.0;
    double temp = p * (p - a) * (p - b) * (p - c);
    
    if (temp < 0) {
        throw CalculationError("Отрицательное подкоренное выражение");
    }
    
    double area = sqrt(temp);
    
    if (area != area) { // Проверка на NaN
        throw CalculationError("Результат вычисления - NaN");
    }
    
    return area;
}

// Функция для проверки на переполнение (без использования limits)
bool checkForOverflow(double a, double b, double c) {
    // Проверяем, не слишком ли большие числа
    const double MAX_VALUE = 1e150;
    
    if (a > MAX_VALUE || b > MAX_VALUE || c > MAX_VALUE) {
        return true;
    }
    
    // Проверяем переполнение при сложении
    double sum = a + b;
    if (sum == a || sum == b) { // Если сумма равна одному из слагаемых
        return true;
    }
    
    sum = a + c;
    if (sum == a || sum == c) {
        return true;
    }
    
    sum = b + c;
    if (sum == b || sum == c) {
        return true;
    }
    
    return false;
}

// Функция для демонстрации работы
void testTriangleArea(int testCase, double a, double b, double c) {
    cout << "\n=== Тест " << testCase << ": a=" << a << ", b=" << b << ", c=" << c << " ===" << endl;
    
    // 1. Без спецификации исключений
    try {
        double area = triangleArea1(a, b, c);
        cout << "1. Без спецификации: Площадь = " << area << endl;
    } catch (const char* msg) {
        cout << "1. Без спецификации: Ошибка - " << msg << endl;
    } catch (...) {
        cout << "1. Без спецификации: Неизвестная ошибка" << endl;
    }
    
    // 2. Со спецификацией throw()
    double area2 = triangleArea2(a, b, c);
    if (area2 < 0) {
        cout << "2. Со спецификацией throw(): Ошибка (код " << area2 << ")" << endl;
    } else {
        cout << "2. Со спецификацией throw(): Площадь = " << area2 << endl;
    }
    
    // 3. С пустым классом исключения
    try {
        double area3 = triangleArea3(a, b, c);
        cout << "3. С пустым классом исключения: Площадь = " << area3 << endl;
    } catch (const TriangleError&) {
        cout << "3. С пустым классом исключения: Ошибка TriangleError" << endl;
    }
    
    // 4. С классом исключения с полями
    try {
        double area4 = triangleArea4(a, b, c);
        cout << "4. С классом исключения с полями: Площадь = " << area4 << endl;
    } catch (const TriangleException& e) {
        cout << "4. С классом исключения с полями: ";
        e.printDetails();
    }
    
    // 5. С наследником от базового класса
    try {
        double area5 = triangleArea5(a, b, c);
        cout << "5. С наследником от базового класса: Площадь = " << area5 << endl;
    } catch (const TriangleBaseException& e) {
        cout << "5. С наследником от базового класса: " << e.what() << endl;
    } catch (const BaseException& e) {
        cout << "5. С наследником от базового класса: " << e.what() << endl;
    }
    
    // 6. С разными типами исключений
    try {
        double area6 = triangleArea6(a, b, c);
        cout << "6. С разными типами исключений: Площадь = " << area6 << endl;
    } catch (const InvalidArgument& e) {
        cout << "6. С разными типами исключений: InvalidArgument - " << e.what() << endl;
    } catch (const CalculationError& e) {
        cout << "6. С разными типами исключений: CalculationError - " << e.what() << endl;
    } catch (const MathException& e) {
        cout << "6. С разными типами исключений: MathException - " << e.what() << endl;
    }
}

int main() {
    cout << "=== Демонстрация обработки исключений для функции площади треугольника ===\n";
    
    // Тест 1: Корректный треугольник (египетский)
    testTriangleArea(1, 3.0, 4.0, 5.0);
    
    // Тест 2: Отрицательная сторона
    testTriangleArea(2, -3.0, 4.0, 5.0);
    
    // Тест 3: Несуществующий треугольник
    testTriangleArea(3, 1.0, 2.0, 10.0);
    
    // Тест 4: Нулевая сторона
    testTriangleArea(4, 0.0, 4.0, 5.0);
    
    // Тест 5: Равносторонний треугольник
    testTriangleArea(5, 5.0, 5.0, 5.0);
    
    // Тест 6: Большие числа (проверка на возможные ошибки)
    testTriangleArea(6, 1000000.0, 1000000.0, 1000000.0);
    
    // Дополнительная демонстрация вложенных try-catch блоков
    cout << "\n=== Демонстрация вложенных try-catch блоков ===" << endl;
    
    try {
        cout << "Внешний блок: начинаем вычисления..." << endl;
        
        try {
            double area = triangleArea4(1.0, 2.0, 10.0);
            cout << "Внутренний блок: Площадь = " << area << endl;
        } catch (const TriangleException& e) {
            cout << "Внутренний блок перехватил: ";
            e.printDetails();
            cout << "Пробрасываем исключение дальше..." << endl;
            throw; // Повторная генерация исключения
        }
        
        cout << "Эта строка не будет выполнена" << endl;
        
    } catch (const TriangleException& e) {
        cout << "Внешний блок перехватил исключение: " << e.getMessage() << endl;
    }
    
    // Демонстрация catch(...)
    cout << "\n=== Демонстрация catch(...) для любых исключений ===" << endl;
    
    try {
        triangleArea1(-1, -2, -3);
    } catch (...) {
        cout << "catch(...) перехватил любое исключение" << endl;
    }
    
    // Демонстрация принципа подстановки с иерархией исключений
    cout << "\n=== Демонстрация иерархии исключений ===" << endl;
    
    try {
        triangleArea6(0, 4, 5);
    } catch (const InvalidArgument& e) {
        cout << "1. Поймали InvalidArgument: " << e.what() << endl;
    } catch (const MathException& e) {
        cout << "2. Поймали MathException: " << e.what() << endl;
    } catch (...) {
        cout << "3. Поймали что-то другое" << endl;
    }
    
    // Демонстрация с массивом тестов
    cout << "\n=== Тестирование через массив параметров ===" << endl;
    
    struct TestCase {
        double a, b, c;
        const char* description;
    };
    
    TestCase tests[] = {
        {3, 4, 5, "Египетский треугольник"},
        {1, 1, 1, "Равносторонний треугольник"},
        {-1, 2, 3, "Отрицательная сторона"},
        {1, 1, 3, "Несуществующий треугольник"},
        {0, 4, 5, "Нулевая сторона"}
    };
    
    for (int i = 0; i < 5; i++) {
        cout << "\nТест " << (i+1) << ": " << tests[i].description << endl;
        
        try {
            double area = triangleArea5(tests[i].a, tests[i].b, tests[i].c);
            cout << "  Площадь = " << area << endl;
        } catch (const BaseException& e) {
            cout << "  Ошибка: " << e.what() << endl;
        } catch (...) {
            cout << "  Неизвестная ошибка" << endl;
        }
    }
    
    // Проверка функции на переполнение
    cout << "\n=== Проверка на переполнение ===" << endl;
    double hugeValue = 1e160;
    
    if (checkForOverflow(hugeValue, hugeValue, hugeValue)) {
        cout << "Обнаружено возможное переполнение для значений: " 
             << hugeValue << ", " << hugeValue << ", " << hugeValue << endl;
    }
    
    // Демонстрация разных способов перехвата исключений
    cout << "\n=== Разные способы перехвата исключений ===" << endl;
    
    // По значению
    try {
        triangleArea1(0, 4, 5);
    } catch (const char* msg) {
        cout << "Перехват по значению: " << msg << endl;
    }
    
    // По ссылке
    try {
        triangleArea4(0, 4, 5);
    } catch (const TriangleException& e) {
        cout << "Перехват по ссылке: " << e.getMessage() << endl;
    }
    
    cout << "\n=== Программа завершена успешно ===" << endl;
    return 0;
}
