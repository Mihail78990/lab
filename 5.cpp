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

    // Вывод информации
    virtual void display() const {
        cout << "Марка: " << brand 
             << ", Цилиндров: " << cylinders 
             << ", Мощность: " << power << " л.с.\n";
    }

    // Преобразование в строку
    virtual char* toString() const {
        char* buffer = new char[100];
        sprintf(buffer, "Марка: %s, Цилиндров: %d, Мощность: %d л.с.", 
                brand, cylinders, power);
        return buffer;
    }
};

class Lorry : public Car {
private:
    int loadCapacity; // грузоподъемность в кг

public:
    // Конструкторы
    Lorry() : Car(), loadCapacity(0) {}
    
    Lorry(const char* br, int cyl, int pwr, int load) 
        : Car(br, cyl, pwr), loadCapacity(load) {}

    Lorry(const Lorry& other) : Car(other), loadCapacity(other.loadCapacity) {}

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

    // Вывод информации
    void display() const override {
        cout << "Марка: " << brand 
             << ", Цилиндров: " << cylinders 
             << ", Мощность: " << power << " л.с."
             << ", Грузоподъемность: " << loadCapacity << " кг\n";
    }

    // Преобразование в строку
    char* toString() const override {
        char* buffer = new char[150];
        sprintf(buffer, "Марка: %s, Цилиндров: %d, Мощность: %d л.с., Грузоподъемность: %d кг", 
                brand, cylinders, power, loadCapacity);
        return buffer;
    }
};

int main() {
    // Создание объектов
    Car car1("Toyota", 4, 150);
    Lorry lorry1("Kamaz", 8, 300, 15000);
    Lorry lorry2("GAZ", 6, 200, 8000);

    // Демонстрация методов базового класса
    cout << "=== Информация о машинах ===\n";
    car1.display();
    lorry1.display();
    lorry2.display();

    // Демонстрация изменения мощности
    car1.setPower(180);
    cout << "\nПосле изменения мощности Toyota:\n";
    car1.display();

    // Демонстрация изменения грузоподъемности
    lorry1.setLoadCapacity(20000);
    cout << "\nПосле изменения грузоподъемности Kamaz:\n";
    lorry1.display();

    // Демонстрация изменения марки
    lorry2.setBrand("Урал");
    cout << "\nПосле изменения марки GAZ:\n";
    lorry2.display();

    // Принцип подстановки
    cout << "\n=== Принцип подстановки ===\n";
    Car* carPtr = &lorry1;
    cout << "Вызов display() через указатель Car* на Lorry:\n";
    carPtr->display();

    // Массив объектов
    cout << "\n=== Массив машин ===\n";
    Car* garage[3];
    garage[0] = new Car("BMW", 6, 250);
    garage[1] = new Lorry("MAN", 12, 500, 25000);
    garage[2] = new Car("Audi", 4, 180);

    for (int i = 0; i < 3; i++) {
        garage[i]->display();
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
