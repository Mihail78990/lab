#include <iostream>
#include <string>
using namespace std;

// Шаблонная функция compare
template <typename T>
int compare(const T& a, const T& b) {
    if (a < b) return -1;
    if (b < a) return 1;
    return 0;
}

int main() {
    // Примеры использования
    int x = 5, y = 5;
    cout << "compare(5, 5) = " << compare(x, y) << endl;

    double a = 3.14, b = 2.71;
    cout << "compare(3.14, 2.71) = " << compare(a, b) << endl;
    
    double c = 2.5, d = 3.5;
    cout << "compare(2.5, 3.5) = " << compare(c, d) << endl;

    string s1 = "hello", s2 = "world";
    cout << "compare(\"hello\", \"world\") = " << compare(s1, s2) << endl;

    string s3 = "hello";
    cout << "compare(\"hello\", \"hello\") = " << compare(s1, s3) << endl;
    
    // Дополнительные примеры
    cout << "\nДополнительные примеры:\n";
    cout << "compare(10, 5) = " << compare(10, 5) << endl;
    cout << "compare(1, 100) = " << compare(1, 100) << endl;
    cout << "compare(\"apple\", \"banana\") = " << compare(string("apple"), string("banana")) << endl;
    cout << "compare(\"zebra\", \"apple\") = " << compare(string("zebra"), string("apple")) << endl;

    return 0;
}
