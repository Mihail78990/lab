#include <iostream>
using namespace std;

// Шаблонная функция compare
template <typename T>
bool compare(const T& a, const T& b) {
    return a == b;
}

int main() {
    // Примеры использования
    int x = 5, y = 5;
    cout << "compare(5, 5) = " << (compare(x, y) ? "true" : "false") << endl;

    double a = 3.14, b = 2.71;
    cout << "compare(3.14, 2.71) = " << (compare(a, b) ? "true" : "false") << endl;

    string s1 = "hello", s2 = "world";
    cout << "compare(\"hello\", \"world\") = " << (compare(s1, s2) ? "true" : "false") << endl;

    string s3 = "hello";
    cout << "compare(\"hello\", \"hello\") = " << (compare(s1, s3) ? "true" : "false") << endl;

    return 0;
}
