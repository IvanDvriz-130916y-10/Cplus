#include <iostream>
#include <locale>
#include <codecvt>

using namespace std;

// Объявление функций
void obmen(int, int);
void obmen2(int*, int*);
void obmen3(int&, int&);

int main(void)
{
    // Устанавливаем локаль для поддержки русских символов
    setlocale(LC_ALL, "Russian");

    int a = 1, b = 2;
    cout << "До обмена: a=" << a << " b=" << b << endl;

    // Вызов функции obmen
    obmen(a, b);
    cout << "После обмена 1: a=" << a << " b=" << b << endl;

    // Вызов функции obmen2
    obmen2(&a, &b);
    cout << "После обмена 2: a=" << a << " b=" << b << endl;

    // Вызов функции obmen3
    obmen3(a, b);
    cout << "После обмена 3: a=" << a << " b=" << b << endl;

    return 0;
}

void obmen(int x, int y) {
    int a = x, b = y;
    a = a + b;
    b = a - b;
    a = a - b;
}

void obmen2(int* x, int* y) {
    int buf;
    buf = *x;
    *x = *y;
    *y = buf;
}

void obmen3(int& x, int& y) {
    int buff;
    buff = x;
    x = y;
    y = buff;
}