#include <iostream>
#include <cstring>

using namespace std;

class Car {
protected:
    char* brand;
    int cylinders;
    int power; // мощность в л.с.

public:
    // Конструктор без аргументов
    Car() : brand(nullptr), cylinders(0), power(0) {}

    // Конструктор инициализации
    Car(const char* br, int cyl, int pwr) : cylinders(cyl), power(pwr) {
        brand = new char[strlen(br) + 1];
        strcpy(brand, br);
    }

    // Конструктор копирования
    Car(const Car& other) : cylinders(other.cylinders), power(other.power) {
        brand = new char[strlen(other.brand) + 1];
        strcpy(brand, other.brand);
    }

    // Деструктор
    virtual ~Car() {
        delete[] brand;
    }

    // Оператор присваивания
    Car& operator=(const Car& other) {
        if (this != &other) {
            delete[] brand;
            cylinders = other.cylinders;
            power = other.power;
            brand = new char[strlen(other.brand) + 1];
            strcpy(brand, other.brand);
        }
        return *this;
    }

    // Методы доступа
    const char* getBrand() const { return brand; }
    int getCylinders() const { return cylinders; }
    int getPower() const { return power; }

    // Изменение мощности
    void setPower(int pwr) {
        if (pwr >= 0) {
            power = pwr;
        } else {
            cerr << "Ошибка: мощность не может быть отрицательной\n";
        }
    }

    // Преобразование в строку
    virtual char* toString() const {
        char* buffer = new char[100];
        sprintf(buffer, "Марка: %s, Цилиндров: %d, Мощность: %d л.с.", 
                brand, cylinders, power);
        return buffer;
    }

    // Дружественная функция для перегрузки оператора вывода
    friend ostream& operator<<(ostream& os, const Car& car);
};

// Перегрузка оператора вывода для Car
ostream& operator<<(ostream& os, const Car& car) {
    os << "Марка: " << car.brand 
       << ", Цилиндров: " << car.cylinders 
       << ", Мощность: " << car.power << " л.с.";
    return os;
}

class Lorry : public Car {
private:
    int loadCapacity; // грузоподъемность в кг

public:
    // Конструкторы
    Lorry() : Car(), loadCapacity(0) {}
    
    Lorry(const char* br, int cyl, int pwr, int load) 
        : Car(br, cyl, pwr), loadCapacity(load) {}

    Lorry(const Lorry& other) : Car(other), loadCapacity(other.loadCapacity) {}

    // Оператор присваивания
    Lorry& operator=(const Lorry& other) {
        if (this != &other) {
            Car::operator=(other);
            loadCapacity = other.loadCapacity;
        }
        return *this;
    }

    // Методы доступа
    int getLoadCapacity() const { return loadCapacity; }

    // Изменение марки
    void setBrand(const char* br) {
        delete[] brand;
        brand = new char[strlen(br) + 1];
        strcpy(brand, br);
    }

    // Изменение грузоподъемности
    void setLoadCapacity(int load) {
        if (load >= 0) {
            loadCapacity = load;
        } else {
            cerr << "Ошибка: грузоподъемность не может быть отрицательной\n";
        }
    }

    // Преобразование в строку
    char* toString() const override {
        char* buffer = new char[150];
        sprintf(buffer, "Марка: %s, Цилиндров: %d, Мощность: %d л.с., Грузоподъемность: %d кг", 
                brand, cylinders, power, loadCapacity);
        return buffer;
    }

    // Дружественная функция для перегрузки оператора вывода
    friend ostream& operator<<(ostream& os, const Lorry& lorry);
};

// Перегрузка оператора вывода для Lorry
ostream& operator<<(ostream& os, const Lorry& lorry) {
    os << static_cast<const Car&>(lorry)
       << ", Грузоподъемность: " << lorry.loadCapacity << " кг";
    return os;
}

int main() {
    // Создание объектов
    Car car1("Toyota", 4, 150);
    Lorry lorry1("Kamaz", 8, 300, 15000);
    Lorry lorry2("GAZ", 6, 200, 8000);

    // Демонстрация оператора вывода
    cout << "=== Информация о машинах ===\n";
    cout << car1 << endl;
    cout << lorry1 << endl;
    cout << lorry2 << endl;

    // Демонстрация изменения мощности
    car1.setPower(180);
    cout << "\nПосле изменения мощности Toyota:\n";
    cout << car1 << endl;

    // Демонстрация изменения грузоподъемности
    lorry1.setLoadCapacity(20000);
    cout << "\nПосле изменения грузоподъемности Kamaz:\n";
    cout << lorry1 << endl;

    // Демонстрация изменения марки
    lorry2.setBrand("Урал");
    cout << "\nПосле изменения марки GAZ:\n";
    cout << lorry2 << endl;

    // Принцип подстановки
    cout << "\n=== Принцип подстановки ===\n";
    Car* carPtr = &lorry1;
    cout << "Вызов оператора << через указатель Car* на Lorry:\n";
    cout << *carPtr << endl;  // Выведет только информацию Car (без грузоподъемности)

    // Массив объектов
    cout << "\n=== Массив машин ===\n";
    Car* garage[3];
    garage[0] = new Car("BMW", 6, 250);
    garage[1] = new Lorry("MAN", 12, 500, 25000);
    garage[2] = new Car("Audi", 4, 180);

    for (int i = 0; i < 3; i++) {
        cout << *garage[i] << endl;
    }

    // Преобразование в строку
    cout << "\n=== Преобразование в строку ===\n";
    char* str = lorry1.toString();
    cout << "Строковое представление lorry1: " << str << endl;
    delete[] str;

    // Очистка памяти
    for (int i = 0; i < 3; i++) {
        delete garage[i];
    }

    return 0;
}
