#ifndef STROKA_H
#define STROKA_H

#include <iostream>
using namespace std;

class Stroka {
private:
    char* str;     // динамический массив для хранения символов строки
    int capacity;  // выделенный объём памяти (в байтах, включая завершающий нуль)

    // Самописные функции для работы со строками (аналог функций из lab4)
    static int my_strlen(const char* s);
    static void my_strcpy(char* dest, const char* src);
    static void my_strcat(char* dest, const char* src);
    static int my_strcmp(const char* s1, const char* s2);

public:
    // Конструкторы:
    Stroka();                          // конструктор по умолчанию (выделяет 80 символов)
    Stroka(const char* s);             // конструктор с параметром (инициализация по C-строке)
    Stroka(const Stroka& s);           // копирующий конструктор
    Stroka(int size);                  // конструктор с выделением памяти заданного размера

    // Деструктор:
    ~Stroka();

    // Перегруженные операторы:
    Stroka& operator=(const Stroka& s); // оператор присваивания
    Stroka& operator+(const Stroka& s); // оператор сцепления (конкатенации) – добавляет строку s к текущей
    int operator==(const Stroka& s) const; // оператор сравнения. Возвращает 1, если строки равны, и 0 в противном случае

    // Методы класса:
    int dlina() const;         // возвращает длину строки (без учёта завершающего нуля)
    void vvod();               // ввод строки из стандартного входного потока
    void vyvod() const;        // вывод строки в стандартный выходной поток
};

#endif