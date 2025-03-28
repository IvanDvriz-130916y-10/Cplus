#include <iostream>
#include <locale>
#include <codecvt>

using namespace std;

// ���������� �������
void obmen(int, int);
void obmen2(int*, int*);
void obmen3(int&, int&);

int main(void)
{
    // ������������� ������ ��� ��������� ������� ��������
    setlocale(LC_ALL, "Russian");

    int a = 1, b = 2;
    cout << "�� ������: a=" << a << " b=" << b << endl;

    // ����� ������� obmen
    obmen(a, b);
    cout << "����� ������ 1: a=" << a << " b=" << b << endl;

    // ����� ������� obmen2
    obmen2(&a, &b);
    cout << "����� ������ 2: a=" << a << " b=" << b << endl;

    // ����� ������� obmen3
    obmen3(a, b);
    cout << "����� ������ 3: a=" << a << " b=" << b << endl;

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