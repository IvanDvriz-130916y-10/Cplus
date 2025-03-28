#include <iostream>
#include <windows.h> // ��� SetConsoleOutputCP
#include <locale>    // ��� setlocale
using namespace std;

// ���������� ������ PR ��� ������ ���������� � ���������
#define PR(x) printf("x=%u, *x=%d, &x=%u\n", (unsigned int)(x), *(x), (unsigned int)(&x))

void demonstratePointerOperations() {
    // ������ � �������� ����� �����
    int mas[] = { 100, 200, 300 };
    int* ptr1, * ptr2;

    ptr1 = mas; // ��������� �� ������ ������� �������
    ptr2 = &mas[2]; // ��������� �� ������ ������� �������

    cout << "������ � ����������� �� int:" << endl;
    PR(ptr1); // ����� ���������� � ptr1
    ptr1++; // ����������� ��������� �� ��������� �������
    PR(ptr1); // ����� ���������� � ptr1
    PR(ptr2); // ����� ���������� � ptr2
    ++ptr2; // ����������� ��������� �� ��������� �������
    printf("ptr2 - ptr1 = %d\n", ptr2 - ptr1); // ������� ����� �����������

    // ������ � �������� �������� (��������)
    char str[] = "Hello";
    char* ptr3 = str; // ��������� �� ������

    cout << "\n������ � ����������� �� char:" << endl;
    PR(ptr3); // ����� ���������� � ptr3
    ptr3++; // ����������� ��������� �� ��������� ������
    PR(ptr3); // ����� ���������� � ptr3
    printf("ptr3 - str = %d\n", ptr3 - str); // ������� ����� �����������

    // ������ � �������� ������� �����
    double dmas[] = { 1.1, 2.2, 3.3 };
    double* ptr4 = dmas; // ��������� �� ������ ������� �������

    cout << "\n������ � ����������� �� double:" << endl;
    PR(ptr4); // ����� ���������� � ptr4
    ptr4++; // ����������� ��������� �� ��������� �������
    PR(ptr4); // ����� ���������� � ptr4
    printf("ptr4 - dmas = %d\n", ptr4 - dmas); // ������� ����� �����������
}

int main() {

    setlocale(LC_ALL, "Russian");

    demonstratePointerOperations(); // ����� ������� ��� ������������ �������� � �����������
    return 0; // ���������� 0 ��� ��������� ���������� ���������
}