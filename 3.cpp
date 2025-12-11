#include <iostream>
#include <cmath>
using namespace std
class Complex {
private:
    double real; // действительная часть
    double imag; // мнимая часть

public:
    // 1. Конструктор без аргументов
    Complex() : real(0.0), imag(0.0) {}

    // 2. Конструктор инициализации
    Complex(double r, double i) : real(r), imag(i) {}

    // 3. Конструктор копирования
    Complex(const Complex &other) : real(other.real), imag(other.imag) {}

    // Методы доступа
    double getReal() const { return real; }
    double getImag() const { return imag; }

    // Сложение
    Complex add(const Complex &c) const {
        return Complex(real + c.real, imag + c.imag);
    }

    // Вычитание
    Complex sub(const Complex &c) const {
        return Complex(real - c.real, imag - c.imag);
    }

    // Умножение
    Complex mul(const Complex &c) const {
        return Complex(real * c.real - imag * c.imag,
                       real * c.imag + imag * c.real);
    }

    // Деление
    Complex div(const Complex &c) const {
        double denominator = c.real * c.real + c.imag * c.imag;
        if (denominator == 0) {
            cerr << "Ошибка: деление на ноль!" << std::endl;
            return Complex();
        }
        return Complex((real * c.real + imag * c.imag) / denominator,
                       (imag * c.real - real * c.imag) / denominator);
    }

    // Сравнение
    bool equ(const Complex &c) const {
        return (real == c.real) && (imag == c.imag);
    }

    // Сопряжение
    Complex conj() const {
        return Complex(real, -imag);
    }

    // Вывод на экран
    void display() const {
        std::cout << real << (imag >= 0 ? "+" : "") << imag << "i" << std::endl;
    }
};

int main() {
    // Демонстрация конструкторов
    Complex c1;                     // конструктор без аргументов
    Complex c2(3.0, 4.0);           // конструктор инициализации
    Complex c3(c2);                 // конструктор копирования

    std::cout << "c1 = "; c1.display();
    std::cout << "c2 = "; c2.display();
    std::cout << "c3 = "; c3.display();

    // Демонстрация операций
    Complex sum = c2.add(c3);
    std::cout << "c2 + c3 = "; sum.display();

    Complex diff = c2.sub(Complex(1, 1));
    std::cout << "c2 - (1+1i) = "; diff.display();

    Complex prod = c2.mul(c3);
    std::cout << "c2 * c3 = "; prod.display();

    Complex quot = c2.div(Complex(1, 2));
    cout << "c2 / (1+2i) = "; quot.display();

    cout << "c2 == c3? " << (c2.equ(c3) ? "Да" : "Нет") << std::endl;

    Complex conj = c2.conj();
    cout << "Сопряженное для c2 = "; conj.display();

    return 0;
}
