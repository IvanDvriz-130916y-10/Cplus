#include "Stroka.h"
#include <iostream>

// ���������� ���������� ������� ��� ������ �� ��������

// ���������� ����� ������ (������ strlen)
int Stroka::my_strlen(const char* s) {
    int len = 0;
    while (s[len] != '\0')
        len++;
    return len;
}

// �������� ������ src � dest (������ strcpy)
void Stroka::my_strcpy(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// ���������� ������ src � ����� ������ dest (������ strcat)
void Stroka::my_strcat(char* dest, const char* src) {
    int i = my_strlen(dest);
    int j = 0;
    while (src[j] != '\0') {
        dest[i + j] = src[j];
        j++;
    }
    dest[i + j] = '\0';
}

// ���������� ��� ������ (������ strcmp). ���������� 0, ���� ������ �����.
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
// ���������� ������������� � �����������
// =====================

// ����������� �� ���������: �������� ������ ��� 80 ��������
Stroka::Stroka() : capacity(80) {
    str = new char[capacity];
    str[0] = '\0';
}

// ����������� � ���������� (������������� �� C-������)
Stroka::Stroka(const char* s) {
    capacity = my_strlen(s) + 1;
    str = new char[capacity];
    my_strcpy(str, s);
}

// ���������� �����������
Stroka::Stroka(const Stroka& s) {
    capacity = s.capacity;
    str = new char[capacity];
    my_strcpy(str, s.str);
}

// ����������� � ���������� ������ ��������� ������� (���� ������ �������� ������ ����� ������, ���������� ������ �����)
Stroka::Stroka(int size) : capacity(size) {
    if (size < 1) capacity = 1;
    str = new char[capacity];
    str[0] = '\0';
}

// ���������� ��� ������������ ������������ ������
Stroka::~Stroka() {
    delete[] str;
}

// =====================
// ������������� ���������
// =====================

// �������� ������������
Stroka& Stroka::operator=(const Stroka& s) {
    if (this != &s) {
        delete[] str;
        capacity = s.capacity;
        str = new char[capacity];
        my_strcpy(str, s.str);
    }
    return *this;
}

// �������� ���������. �������� �������, ���������� ����������� �������� ������� � � ����� ������� ������ ����������� ������ s.
// ���� ����� ������������, ����������� ����������������� ������.
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

// �������� ���������: ���������� 1, ���� ������ �����, ����� 0.
int Stroka::operator==(const Stroka& s) const {
    return (my_strcmp(str, s.str) == 0) ? 1 : 0;
}

// =====================
// ������ ������
// =====================

// ���������� ����� ������ ��� ������������ ������� '\0'
int Stroka::dlina() const {
    return my_strlen(str);
}

// ���� ������ �� ������������ �������� ������.
// ����� ���������� ������� getLine, ����� ����� ���� ������� ������, ���������� �������.
// ��������������, ��� ���������� ������ ���������� (capacity �������� �������� ������).
void Stroka::vvod() {
    std::cin.getline(str, capacity);
}

// ����� ������ � ����������� �������� �����
void Stroka::vyvod() const {
    std::cout << str;
}