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

    // Оператор присваивания
    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            if (other.data) {
                data = new unsigned char[size];
                memcpy(data, other.data, size);
            } else {
                data = nullptr;
            }
        }
        return *this;
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

    // Дружественная функция для вывода
    friend ostream& operator<<(ostream& os, const Array& arr);
};

// Перегрузка оператора вывода для Array
ostream& operator<<(ostream& os, const Array& arr) {
    os << "Массив [" << arr.size << "]: ";
    for (int i = 0; i < arr.size; i++) {
        os << (int)arr.data[i] << " ";
    }
    return os;
}

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

    bool getSign() const { return sign; }
    int getDecimalDigits() const { return decimalDigits; }
    
    // Дружественная функция для вывода
    friend ostream& operator<<(ostream& os, const Fraction& frac);
};

// Перегрузка оператора вывода для Fraction
ostream& operator<<(ostream& os, const Fraction& frac) {
    os << "Дробь [" << frac.size << "], знак: " << (frac.sign ? "-" : "+")
       << ", дробных цифр: " << frac.decimalDigits << ": ";
    for (int i = frac.size - 1; i >= 0; i--) {
        os << (int)frac.data[i];
        if (i == frac.decimalDigits && frac.decimalDigits > 0) {
            os << ".";
        }
    }
    return os;
}

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
    
    // Дружественная функция для вывода
    friend ostream& operator<<(ostream& os, const BitString& bitStr);
};

// Перегрузка оператора вывода для BitString
ostream& operator<<(ostream& os, const BitString& bitStr) {
    os << "Битовая строка [" << bitStr.size << "]: ";
    for (int i = bitStr.size - 1; i >= 0; i--) {
        os << (int)bitStr.data[i];
    }
    os << " (двоичное)";
    return os;
}

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
    cout << array1 << endl;
    cout << array2 << endl;
    cout << fraction1 << endl;
    cout << fraction2 << endl;
    cout << bitStr1 << endl;
    cout << bitStr2 << endl;

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
    cout << sumArray << endl;

    cout << "\n2. Сложение Fraction + Fraction:\n";
    Array sumFraction = *arrays[2] + *arrays[3];
    cout << sumFraction << endl;

    cout << "\n3. Сложение BitString + BitString:\n";
    Array sumBitString = *arrays[4] + *arrays[5];
    cout << sumBitString << endl;

    // Попытка сложения разных типов (вызовет ошибку)
    cout << "\n4. Попытка сложения разных типов (Array + Fraction):\n";
    Array wrongSum = *arrays[0] + *arrays[2];
    cout << wrongSum << endl;

    // Массив указателей на базовый класс
    cout << "\n=== Работа с массивом указателей ===\n";
    for (int i = 0; i < 6; i++) {
        cout << "Элемент " << i << ": " << *arrays[i] << endl;
    }

    // Демонстрация полиморфизма
    cout << "\n=== Полиморфное поведение ===\n";
    Array* polyArray = &bitStr1;
    cout << "Вызов оператора << через указатель Array* на BitString:\n";
    cout << *polyArray << endl; // Выведет как Array (без двоичной специфики)

    // Динамическое создание объектов
    cout << "\n=== Динамическое создание объектов ===\n";
    Array* dynArray = new Fraction(3, 1, false, 7);
    cout << *dynArray << endl;
    
    Array* dynBitString = new BitString(5, 1);
    cout << *dynBitString << endl;

    // Для корректного вывода нужно явное приведение
    cout << "\n=== Явное приведение типов для правильного вывода ===\n";
    if (Fraction* fracPtr = dynamic_cast<Fraction*>(dynArray)) {
        cout << "Fraction: " << *fracPtr << endl;
    }
    
    if (BitString* bitPtr = dynamic_cast<BitString*>(dynBitString)) {
        cout << "BitString: " << *bitPtr << endl;
    }

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
