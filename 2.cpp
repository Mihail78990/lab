#include <iostream>
#include <string>
#include <cmath>
using namespace std;
// Способ 1: Структура с внешними функциями
struct ComplexStruct {
    double real;      
    double imag;   
    // Метод инициализации
    void init(double r = 0, double i = 0) {
        real = r;
        imag = i;
    }
    // Ввод с клавиатуры
    void read() {
        cout << "Введите действительную часть: ";
        cin >> real;
        cout << "Введите мнимую часть: ";
        cin >> imag;
    }
    // Вывод на экран
    void display() const {
        if (imag >= 0)
            cout << real << " + " << imag << "i";
        else
            cout << real << " - " << -imag << "i";
    }
    // Преобразование в строку
    string toString() const {
        if (imag == 0) return to_string(real);
        if (real == 0) {
            if (imag > 0) return to_string(imag) + "i";
            else return "-" + to_string(-imag) + "i";
        }
        string sign = imag > 0 ? " + " : " - ";
        return to_string(real) + sign + to_string(abs(imag)) + "i";
    }
};

// Внешние функции для работы со структурой ComplexStruct
ComplexStruct add(const ComplexStruct& a, const ComplexStruct& b) {
    ComplexStruct result;
    result.init(a.real + b.real, a.imag + b.imag);
    return result;
}

ComplexStruct sub(const ComplexStruct& a, const ComplexStruct& b) {
    ComplexStruct result;
    result.init(a.real - b.real, a.imag - b.imag);
    return result;
}

ComplexStruct mul(const ComplexStruct& a, const ComplexStruct& b) {
    ComplexStruct result;
    result.init(a.real * b.real - a.imag * b.imag, 
                a.real * b.imag + a.imag * b.real);
    return result;
}

ComplexStruct div(const ComplexStruct& a, const ComplexStruct& b) {
    double denominator = b.real * b.real + b.imag * b.imag;
    if (denominator == 0) {
        cout << "Ошибка: деление на ноль!" << endl;
        ComplexStruct zero;
        zero.init(0, 0);
        return zero;
    }
    ComplexStruct result;
    result.init((a.real * b.real + a.imag * b.imag) / denominator,
                (a.imag * b.real - a.real * b.imag) / denominator);
    return result;
}
bool equ(const ComplexStruct& a, const ComplexStruct& b) {
    return a.real == b.real && a.imag == b.imag;
}
ComplexStruct conj(const ComplexStruct& a) {
    ComplexStruct result;
    result.init(a.real, -a.imag);
    return result;
}
// Способ 2: Класс с закрытыми полями
class ComplexClass {
private:
    double real;      
    double imag;      
public:
    // Конструкторы
    ComplexClass(double r = 0, double i = 0) {
        init(r, i);
    }
    // Метод инициализации
    void init(double r = 0, double i = 0) {
        real = r;
        imag = i;
    }
    // Ввод с клавиатуры
    void read() {
        cout << "Введите действительную часть: ";
        cin >> real;
        cout << "Введите мнимую часть: ";
        cin >> imag;
    }
    // Вывод на экран
    void display() const {
        if (imag >= 0)
            cout << real << " + " << imag << "i";
        else
            cout << real << " - " << -imag << "i";
    }
    // Преобразование в строку
    string toString() const {
        if (imag == 0) return to_string(real);
        if (real == 0) {
            if (imag > 0) return to_string(imag) + "i";
            else return "-" + to_string(-imag) + "i";
        }  
        string sign = imag > 0 ? " + " : " - ";
        return to_string(real) + sign + to_string(abs(imag)) + "i";
    }
    // Геттеры
    double getReal() const { return real; }
    double getImag() const { return imag; }
    // Операции как методы класса
    ComplexClass add(const ComplexClass& other) const {
        return ComplexClass(real + other.real, imag + other.imag);
    }
    
    ComplexClass sub(const ComplexClass& other) const {
        return ComplexClass(real - other.real, imag - other.imag);
    }
    ComplexClass mul(const ComplexClass& other) const {
        return ComplexClass(real * other.real - imag * other.imag,
                           real * other.imag + imag * other.real);
    }
    ComplexClass div(const ComplexClass& other) const {
        double denominator = other.real * other.real + other.imag * other.imag;
        if (denominator == 0) {
            cout << "Ошибка: деление на ноль!" << endl;
            return ComplexClass(0, 0);
        }
        
        return ComplexClass((real * other.real + imag * other.imag) / denominator,
                           (imag * other.real - real * other.imag) / denominator);
    }
    
    bool equ(const ComplexClass& other) const {
        return real == other.real && imag == other.imag;
    }
    
    ComplexClass conj() const {
        return ComplexClass(real, -imag);
    }
};

// Функция для демонстрации работы со структурой
void demonstrateStruct() {
    cout << "=== РАБОТА СО СТРУКТУРОЙ ===" << endl;
    
    // Создание объектов различными способами
    ComplexStruct c1, c2, c3;
    c1.init(3, 4);      // инициализация методом init
    c2.init(-2, 5);
    
    cout << "Введите третье комплексное число:" << endl;
    c3.read();
    
    // Демонстрация операций
    cout << "\nc1 = "; c1.display();
    cout << "\nc2 = "; c2.display();
    cout << "\nc3 = "; c3.display();
    cout << endl;
    
    cout << "\nОперации:" << endl;
    ComplexStruct result;
    
    result = add(c1, c2);
    cout << "c1 + c2 = "; result.display(); cout << endl;
    
    result = sub(c1, c2);
    cout << "c1 - c2 = "; result.display(); cout << endl;
    
    result = mul(c1, c2);
    cout << "c1 * c2 = "; result.display(); cout << endl;
    
    result = div(c1, c2);
    cout << "c1 / c2 = "; result.display(); cout << endl;
    
    cout << "c1 == c2: " << (equ(c1, c2) ? "да" : "нет") << endl;
    
    result = conj(c1);
    cout << "conj(c1) = "; result.display(); cout << endl;
    
    // Демонстрация toString
    cout << "\nПреобразование в строку:" << endl;
    cout << "c1: " << c1.toString() << endl;
    cout << "c2: " << c2.toString() << endl;
    cout << "c3: " << c3.toString() << endl;
}

// Функция для демонстрации работы с классом
void demonstrateClass() {
    cout << "\n=== РАБОТА С КЛАССОМ ===" << endl;
    
    // Создание объектов различными способами
    ComplexClass c1(3, 4);           // через конструктор
    ComplexClass c2(-2, 5);
    ComplexClass c3;
    c3.init(1, -1);                 // через метод init
    
    ComplexClass c4;
    cout << "Введите четвертое комплексное число:" << endl;
    c4.read();
    
    // Демонстрация операций
    cout << "\nc1 = "; c1.display();
    cout << "\nc2 = "; c2.display();
    cout << "\nc3 = "; c3.display();
    cout << "\nc4 = "; c4.display();
    cout << endl;
    
    cout << "\nОперации:" << endl;
    
    ComplexClass result = c1.add(c2);
    cout << "c1 + c2 = "; result.display(); cout << endl;
    result = c1.sub(c2);
    cout << "c1 - c2 = "; result.display(); cout << endl;
    result = c1.mul(c2);
    cout << "c1 * c2 = "; result.display(); cout << endl;
    result = c1.div(c2);
    cout << "c1 / c2 = "; result.display(); cout << endl;
    cout << "c1 == c2: " << (c1.equ(c2) ? "да" : "нет") << endl;
    result = c1.conj();
    cout << "c1.conj() = "; result.display(); cout << endl;
    // Демонстрация toString
    cout << "\nПреобразование в строку:" << endl;
    cout << "c1: " << c1.toString() << endl;
    cout << "c2: " << c2.toString() << endl;
    cout << "c3: " << c3.toString() << endl;
    cout << "c4: " << c4.toString() << endl;
    // Демонстрация цепочки операций
    cout << "\nЦепочка операций: ((c1 + c2) * c3).conj()" << endl;
    result = c1.add(c2).mul(c3).conj();
    cout << "Результат: "; result.display(); 
    cout << " (" << result.toString() << ")" << endl;
}
int main() {
    demonstrateStruct();
    demonstrateClass();
    cout << "\n=== РАБОТА С МАССИВАМИ ===" << endl;
    // Массив структур
    ComplexStruct structArray[3];
    structArray[0].init(1, 2);
    structArray[1].init(3, -4);
    structArray[2].init(0, 5);
    
    cout << "Массив структур:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "structArray[" << i << "] = " << structArray[i].toString();
        cout << " -> сопряженное: " << conj(structArray[i]).toString() << endl;
    }
    // Массив классов
    ComplexClass classArray[3];
    classArray[0].init(2, -3);
    classArray[1].init(-1, -1);
    classArray[2].init(4, 0);
    cout << "\nМассив классов:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "classArray[" << i << "] = " << classArray[i].toString();
        cout << " -> сопряженное: " << classArray[i].conj().toString() << endl;
    }
    // Демонстрация операций с массивами
    cout << "\nОперации с элементами массивов:" << endl;
    ComplexStruct structSum = add(structArray[0], structArray[1]);
    cout << "structArray[0] + structArray[1] = " << structSum.toString() << endl;
    
    ComplexClass classMul = classArray[0].mul(classArray[1]);
    cout << "classArray[0] * classArray[1] = " << classMul.toString() << endl;
    return 0;
}
