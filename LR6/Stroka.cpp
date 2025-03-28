#include "Stroka.h"
#include <iostream>

// Реализация самописных функций для работы со строками

// Определяет длину строки (аналог strlen)
int Stroka::my_strlen(const char* s) {
    int len = 0;
    while (s[len] != '\0')
        len++;
    return len;
}

// Копирует строку src в dest (аналог strcpy)
void Stroka::my_strcpy(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// Дописывает строку src в конец строки dest (аналог strcat)
void Stroka::my_strcat(char* dest, const char* src) {
    int i = my_strlen(dest);
    int j = 0;
    while (src[j] != '\0') {
        dest[i + j] = src[j];
        j++;
    }
    dest[i + j] = '\0';
}

// Сравнивает две строки (аналог strcmp). Возвращает 0, если строки равны.
int Stroka::my_strcmp(const char* s1, const char* s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i])
            return s1[i] - s2[i];
        i++;
    }
    return s1[i] - s2[i];
}

// =====================
// Реализация конструкторов и деструктора
// =====================

// Конструктор по умолчанию: выделяет память под 80 символов
Stroka::Stroka() : capacity(80) {
    str = new char[capacity];
    str[0] = '\0';
}

// Конструктор с параметром (инициализация по C-строке)
Stroka::Stroka(const char* s) {
    capacity = my_strlen(s) + 1;
    str = new char[capacity];
    my_strcpy(str, s);
}

// Копирующий конструктор
Stroka::Stroka(const Stroka& s) {
    capacity = s.capacity;
    str = new char[capacity];
    my_strcpy(str, s.str);
}

// Конструктор с выделением памяти заданного размера (если размер передачи больше длины строки, изначально строка пуста)
Stroka::Stroka(int size) : capacity(size) {
    if (size < 1) capacity = 1;
    str = new char[capacity];
    str[0] = '\0';
}

// Деструктор для освобождения динамической памяти
Stroka::~Stroka() {
    delete[] str;
}

// =====================
// Перегруженные операторы
// =====================

// Оператор присваивания
Stroka& Stroka::operator=(const Stroka& s) {
    if (this != &s) {
        delete[] str;
        capacity = s.capacity;
        str = new char[capacity];
        my_strcpy(str, s.str);
    }
    return *this;
}

// Оператор сцепления. Согласно условию, происходит модификация текущего объекта – в конец текущей строки добавляется строка s.
// Если места недостаточно, выполняется перераспределение памяти.
Stroka& Stroka::operator+(const Stroka& s) {
    int currLength = my_strlen(str);
    int addLength = my_strlen(s.str);
    if (currLength + addLength + 1 > capacity) {
        int newCapacity = currLength + addLength + 1;
        char* newStr = new char[newCapacity];
        my_strcpy(newStr, str);
        delete[] str;
        str = newStr;
        capacity = newCapacity;
    }
    my_strcat(str, s.str);
    return *this;
}

// Оператор сравнения: возвращает 1, если строки равны, иначе 0.
int Stroka::operator==(const Stroka& s) const {
    return (my_strcmp(str, s.str) == 0) ? 1 : 0;
}

// =====================
// Методы класса
// =====================

// Возвращает длину строки без завершающего символа '\0'
int Stroka::dlina() const {
    return my_strlen(str);
}

// Ввод строки из стандартного входного потока.
// Метод использует функцию getLine, чтобы можно было вводить строку, содержащую пробелы.
// Предполагается, что выделенная память достаточна (capacity является размером буфера).
void Stroka::vvod() {
    std::cin.getline(str, capacity);
}

// Вывод строки в стандартный выходной поток
void Stroka::vyvod() const {
    std::cout << str;
}