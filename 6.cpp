#include <iostream>
#include <cstring>

using namespace std;

class Array {
protected:
    static const int MAX_SIZE = 100;
    unsigned char* data;
    int size;

public:
    // Конструкторы
    Array() : data(nullptr), size(0) {}
    
    Array(int n, unsigned char initValue = 0) : size(n) {
        if (n > 0 && n <= MAX_SIZE) {
            data = new unsigned char[n];
            for (int i = 0; i < n; i++) {
                data[i] = initValue;
            }
        } else {
            cerr << "Ошибка: недопустимый размер массива\n";
            data = nullptr;
            size = 0;
        }
    }

    // Конструктор копирования
    Array(const Array& other) : size(other.size) {
        if (other.data) {
            data = new unsigned char[size];
            memcpy(data, other.data, size);
        } else {
            data = nullptr;
        }
    }

    // Деструктор
    virtual ~Array() {
        delete[] data;
    }

    // Оператор индексирования
    unsigned char& operator[](int index) {
        if (index >= 0 && index < size) {
            return data[index];
        } else {
            cerr << "Ошибка: индекс " << index << " вне диапазона\n";
            static unsigned char dummy = 0;
            return dummy;
        }
    }

    const unsigned char& operator[](int index) const {
        if (index >= 0 && index < size) {
            return data[index];
        } else {
            cerr << "Ошибка: индекс " << index << " вне диапазона\n";
            static unsigned char dummy = 0;
            return dummy;
        }
    }

    // Методы доступа
    int getSize() const { return size; }
    static int getMaxSize() { return MAX_SIZE; }

    // Виртуальная функция сложения массивов
    virtual Array operator+(const Array& other) const {
        int resultSize = (size > other.size) ? size : other.size;
        Array result(resultSize);
        
        for (int i = 0; i < resultSize; i++) {
            unsigned char val1 = (i < size) ? data[i] : 0;
            unsigned char val2 = (i < other.size) ? other.data[i] : 0;
            result[i] = val1 + val2;
        }
        
        return result;
    }

    // Вывод массива
    virtual void display() const {
        cout << "Массив [" << size << "]: ";
        for (int i = 0; i < size; i++) {
            cout << (int)data[i] << " ";
        }
        cout << endl;
    }
};

// Производный класс Fraction
class Fraction : public Array {
private:
    bool sign; // true для отрицательных
    int decimalDigits; // количество цифр в дробной части

public:
    Fraction() : Array(), sign(false), decimalDigits(2) {}
    
    Fraction(int n, int decDigits = 2, bool isNegative = false, unsigned char initValue = 0)
        : Array(n, initValue), sign(isNegative), decimalDigits(decDigits) {
        if (decDigits < 0) {
            cerr << "Ошибка: количество дробных цифр не может быть отрицательным\n";
            decimalDigits = 2;
        }
    }

    // Переопределение сложения с проверкой на переполнение
    Array operator+(const Array& other) const override {
        const Fraction* otherFraction = dynamic_cast<const Fraction*>(&other);
        if (!otherFraction) {
            cerr << "Ошибка: сложение возможно только с объектами Fraction\n";
            return Array();
        }

        int resultSize = (size > other.size) ? size : other.size;
        Fraction result(resultSize, decimalDigits);
        
        int carry = 0;
        for (int i = 0; i < resultSize; i++) {
            unsigned char val1 = (i < size) ? data[i] : 0;
            unsigned char val2 = (i < other.size) ? other.data[i] : 0;
            
            int sum = val1 + val2 + carry;
            result[i] = sum % 10;
            carry = sum / 10;
        }
        
        // Если есть перенос, увеличиваем размер
        if (carry > 0 && resultSize < MAX_SIZE) {
            Fraction newResult(resultSize + 1, decimalDigits);
            for (int i = 0; i < resultSize; i++) {
                newResult[i] = result[i];
            }
            newResult[resultSize] = carry;
            return newResult;
        }
        
        return result;
    }

    // Дополнительный метод для работы с дробями
    void setDecimalDigits(int digits) {
        if (digits >= 0) {
            decimalDigits = digits;
        }
    }

    void display() const override {
        cout << "Дробь [" << size << "], знак: " << (sign ? "-" : "+")
             << ", дробных цифр: " << decimalDigits << ": ";
        for (int i = size - 1; i >= 0; i--) {
            cout << (int)data[i];
            if (i == decimalDigits && decimalDigits > 0) {
                cout << ".";
            }
        }
        cout << endl;
    }
};

// Производный класс BitString
class BitString : public Array {
public:
    BitString() : Array() {}
    
    BitString(int n, unsigned char initValue = 0) : Array(n, initValue) {
        // Проверяем, что значения только 0 или 1
        for (int i = 0; i < size; i++) {
            if (data[i] > 1) {
                data[i] = initValue % 2;
            }
        }
    }

    // Переопределение сложения с бинарной логикой
    Array operator+(const Array& other) const override {
        const BitString* otherBitString = dynamic_cast<const BitString*>(&other);
        if (!otherBitString) {
            cerr << "Ошибка: сложение возможно только с объектами BitString\n";
            return Array();
        }

        int resultSize = (size > other.size) ? size : other.size;
        BitString result(resultSize);
        
        int carry = 0;
        for (int i = 0; i < resultSize; i++) {
            unsigned char val1 = (i < size) ? data[i] : 0;
            unsigned char val2 = (i < other.size) ? other.data[i] : 0;
            
            int sum = val1 + val2 + carry;
            result[i] = sum % 2;
            carry = sum / 2;
        }
        
        // Если есть перенос, добавляем еще один бит
        if (carry > 0 && resultSize < MAX_SIZE) {
            BitString newResult(resultSize + 1);
            for (int i = 0; i < resultSize; i++) {
                newResult[i] = result[i];
            }
            newResult[resultSize] = carry;
            return newResult;
        }
        
        return result;
    }

    // Дополнительные битовые операции
    BitString operator&(const BitString& other) const {
        int resultSize = (size > other.size) ? size : other.size;
        BitString result(resultSize);
        
        for (int i = 0; i < resultSize; i++) {
            unsigned char val1 = (i < size) ? data[i] : 0;
            unsigned char val2 = (i < other.size) ? other.data[i] : 0;
            result[i] = val1 & val2;
        }
        
        return result;
    }

    void display() const override {
        cout << "Битовая строка [" << size << "]: ";
        for (int i = size - 1; i >= 0; i--) {
            cout << (int)data[i];
        }
        cout << " (двоичное)" << endl;
    }
};

int main() {
    cout << "=== Демонстрация виртуальных методов ===\n\n";

    // Создание объектов разных типов
    Array array1(5, 10);
    Array array2(3, 20);
    
    Fraction fraction1(4, 2, false, 5);
    Fraction fraction2(3, 2, false, 3);
    
    BitString bitStr1(4, 1);
    BitString bitStr2(3, 1);

    // Заполнение данными
    for (int i = 0; i < array1.getSize(); i++) array1[i] = i + 1;
    for (int i = 0; i < array2.getSize(); i++) array2[i] = i + 10;
    
    for (int i = 0; i < fraction1.getSize(); i++) fraction1[i] = i;
    for (int i = 0; i < fraction2.getSize(); i++) fraction2[i] = i + 1;
    
    bitStr1[0] = 1; bitStr1[1] = 0; bitStr1[2] = 1; bitStr1[3] = 1;
    bitStr2[0] = 1; bitStr2[1] = 1; bitStr2[2] = 0;

    // Вывод созданных объектов
    cout << "Исходные объекты:\n";
    array1.display();
    array2.display();
    fraction1.display();
    fraction2.display();
    bitStr1.display();
    bitStr2.display();

    // Демонстрация виртуального сложения
    cout << "\n=== Сложение через указатели на базовый класс ===\n";
    
    Array* arrays[6];
    arrays[0] = &array1;
    arrays[1] = &array2;
    arrays[2] = &fraction1;
    arrays[3] = &fraction2;
    arrays[4] = &bitStr1;
    arrays[5] = &bitStr2;

    // Сложение объектов одного типа
    cout << "\n1. Сложение Array + Array:\n";
    Array sumArray = *arrays[0] + *arrays[1];
    sumArray.display();

    cout << "\n2. Сложение Fraction + Fraction:\n";
    Array sumFraction = *arrays[2] + *arrays[3];
    sumFraction.display();

    cout << "\n3. Сложение BitString + BitString:\n";
    Array sumBitString = *arrays[4] + *arrays[5];
    sumBitString.display();

    // Попытка сложения разных типов (вызовет ошибку)
    cout << "\n4. Попытка сложения разных типов (Array + Fraction):\n";
    Array wrongSum = *arrays[0] + *arrays[2];
    wrongSum.display();

    // Массив указателей на базовый класс
    cout << "\n=== Работа с массивом указателей ===\n";
    for (int i = 0; i < 6; i++) {
        cout << "Элемент " << i << ": ";
        arrays[i]->display();
    }

    // Демонстрация полиморфизма
    cout << "\n=== Полиморфное поведение ===\n";
    Array* polyArray = &bitStr1;
    cout << "Вызов display() через указатель Array* на BitString:\n";
    polyArray->display();

    // Динамическое создание объектов
    cout << "\n=== Динамическое создание объектов ===\n";
    Array* dynArray = new Fraction(3, 1, false, 7);
    dynArray->display();
    
    Array* dynBitString = new BitString(5, 1);
    dynBitString->display();

    // Проверка работы оператора []
    cout << "\n=== Проверка оператора индексирования ===\n";
    cout << "array1[2] = " << (int)array1[2] << endl;
    cout << "bitStr1[1] = " << (int)bitStr1[1] << endl;
    
    // Проверка на выход за границы
    cout << "\n=== Проверка границ массива ===\n";
    cout << "Попытка доступа к array1[10]: ";
    unsigned char val = array1[10];
    cout << (int)val << endl;

    // Очистка памяти
    delete dynArray;
    delete dynBitString;

    return 0;
}
