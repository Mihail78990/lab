#include <iostream>
#include <cmath>
using namespace std
class Complex {
private:
    double real;
    double imag;

public:
    // Конструкторы
    Complex() : real(0.0), imag(0.0) {}
    Complex(double r, double i) : real(r), imag(i) {}
    Complex(const Complex &other) : real(other.real), imag(other.imag) {}

    // Геттеры
    double getReal() const { return real; }
    double getImag() const { return imag; }

    // Перегрузка операторов как дружественных функций
    friend Complex operator+(const Complex &a, const Complex &b);
    friend Complex operator-(const Complex &a, const Complex &b);
    friend Complex operator*(const Complex &a, const Complex &b);
    friend Complex operator/(const Complex &a, const Complex &b);
    friend bool operator==(const Complex &a, const Complex &b);
    friend std::ostream& operator<<(std::ostream &out, const Complex &c);

    // Сопряжение
    Complex conj() const {
        return Complex(real, -imag);
    }
};

// Реализация операторов
Complex operator+(const Complex &a, const Complex &b) {
    return Complex(a.real + b.real, a.imag + b.imag);
}

Complex operator-(const Complex &a, const Complex &b) {
    return Complex(a.real - b.real, a.imag - b.imag);
}

Complex operator*(const Complex &a, const Complex &b) {
    return Complex(a.real * b.real - a.imag * b.imag,
                   a.real * b.imag + a.imag * b.real);
}

Complex operator/(const Complex &a, const Complex &b) {
    double denominator = b.real * b.real + b.imag * b.imag;
    if (denominator == 0) {
        cerr << "Ошибка: деление на ноль!" << endl;
        return Complex();
    }
    return Complex((a.real * b.real + a.imag * b.imag) / denominator,
                   (a.imag * b.real - a.real * b.imag) / denominator);
}

bool operator==(const Complex &a, const Complex &b) {
    return (a.real == b.real) && (a.imag == b.imag);
}

std::ostream& operator<<(std::ostream &out, const Complex &c) {
    out << c.real << (c.imag >= 0 ? "+" : "") << c.imag << "i";
    return out;
}

int main() {
    // Создание объектов
    Complex a;
    Complex b(2.5, 3.5);
    Complex c(b);

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;

    // Демонстрация перегруженных операторов
    Complex sum = b + c;
    cout << "b + c = " << sum << endl;

    Complex diff = b - Complex(1, 1);
    cout << "b - (1+1i) = " << diff << endl;

    Complex prod = b * c;
    cout << "b * c = " << prod << endl;

    Complex quot = b / Complex(1, 2);
    cout << "b / (1+2i) = " << quot << endl;

    cout << "b == c? " << (b == c ? "Да" : "Нет") << endl;

    Complex conj = b.conj();
    cout << "Сопряженное для b = " << conj << endl;

    return 0;
}
