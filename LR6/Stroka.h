#ifndef STROKA_H
#define STROKA_H

#include <iostream>
using namespace std;

class Stroka {
private:
    char* str;     // ������������ ������ ��� �������� �������� ������
    int capacity;  // ���������� ����� ������ (� ������, ������� ����������� ����)

    // ���������� ������� ��� ������ �� �������� (������ ������� �� lab4)
    static int my_strlen(const char* s);
    static void my_strcpy(char* dest, const char* src);
    static void my_strcat(char* dest, const char* src);
    static int my_strcmp(const char* s1, const char* s2);

public:
    // ������������:
    Stroka();                          // ����������� �� ��������� (�������� 80 ��������)
    Stroka(const char* s);             // ����������� � ���������� (������������� �� C-������)
    Stroka(const Stroka& s);           // ���������� �����������
    Stroka(int size);                  // ����������� � ���������� ������ ��������� �������

    // ����������:
    ~Stroka();

    // ������������� ���������:
    Stroka& operator=(const Stroka& s); // �������� ������������
    Stroka& operator+(const Stroka& s); // �������� ��������� (������������) � ��������� ������ s � �������
    int operator==(const Stroka& s) const; // �������� ���������. ���������� 1, ���� ������ �����, � 0 � ��������� ������

    // ������ ������:
    int dlina() const;         // ���������� ����� ������ (��� ����� ������������ ����)
    void vvod();               // ���� ������ �� ������������ �������� ������
    void vyvod() const;        // ����� ������ � ����������� �������� �����
};

#endif