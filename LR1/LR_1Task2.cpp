#include <iostream>
#include <windows.h> // Для SetConsoleOutputCP
#include <locale>    // Для setlocale
using namespace std;

// Определяем макрос PR для вывода информации о указателе
#define PR(x) printf("x=%u, *x=%d, &x=%u\n", (unsigned int)(x), *(x), (unsigned int)(&x))

void demonstratePointerOperations() {
    // Работа с массивом целых чисел
    int mas[] = { 100, 200, 300 };
    int* ptr1, * ptr2;

    ptr1 = mas; // Указатель на первый элемент массива
    ptr2 = &mas[2]; // Указатель на третий элемент массива

    cout << "Работа с указателями на int:" << endl;
    PR(ptr1); // Вывод информации о ptr1
    ptr1++; // Увеличиваем указатель на следующий элемент
    PR(ptr1); // Вывод информации о ptr1
    PR(ptr2); // Вывод информации о ptr2
    ++ptr2; // Увеличиваем указатель на следующий элемент
    printf("ptr2 - ptr1 = %d\n", ptr2 - ptr1); // Разница между указателями

    // Работа с массивом символов (строками)
    char str[] = "Hello";
    char* ptr3 = str; // Указатель на строку

    cout << "\nРабота с указателями на char:" << endl;
    PR(ptr3); // Вывод информации о ptr3
    ptr3++; // Увеличиваем указатель на следующий символ
    PR(ptr3); // Вывод информации о ptr3
    printf("ptr3 - str = %d\n", ptr3 - str); // Разница между указателями

    // Работа с массивом двойных чисел
    double dmas[] = { 1.1, 2.2, 3.3 };
    double* ptr4 = dmas; // Указатель на первый элемент массива

    cout << "\nРабота с указателями на double:" << endl;
    PR(ptr4); // Вывод информации о ptr4
    ptr4++; // Увеличиваем указатель на следующий элемент
    PR(ptr4); // Вывод информации о ptr4
    printf("ptr4 - dmas = %d\n", ptr4 - dmas); // Разница между указателями
}

int main() {

    setlocale(LC_ALL, "Russian");

    demonstratePointerOperations(); // Вызов функции для демонстрации операций с указателями
    return 0; // Возвращаем 0 для успешного завершения программы
}