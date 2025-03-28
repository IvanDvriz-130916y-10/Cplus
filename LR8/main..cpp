#define _CRT_SECURE_NO_WARNINGS  // Если хотите отключить предупреждения, можно определить этот макрос

#include <iostream>
#include <fstream>
#include <cstring>    // Для функций работы со строками: strlen, strcpy_s, strcat_s.
#include <cstdlib>    // Для функции exit.
#include <iomanip>    // Для манипуляторов потоков.
#include <limits>     // Для numeric_limits.
using namespace std;

// =====================================================================
// КЛАСС STROKA
// =====================================================================

class Stroka {
private:
    char* str;
    size_t length;

    // Вспомогательная функция для копирования строки
    void copyData(const char* source) {
        if (source) {
            length = strlen(source);
            str = new char[length + 1];
            // Используем безопасную функцию strcpy_s
            strcpy_s(str, length + 1, source);
        }
        else {
            length = 0;
            str = new char[1];
            str[0] = '\0';
        }
    }
public:
    // Конструкторы и деструктор
    Stroka() : str(nullptr), length(0) {
        copyData("");
    }
    Stroka(const char* s) : str(nullptr), length(0) {
        copyData(s);
    }
    Stroka(const Stroka& other) : str(nullptr), length(0) {
        copyData(other.str);
    }
    ~Stroka() {
        delete[] str;
    }

    // Оператор присваивания
    Stroka& operator=(const Stroka& other) {
        if (this != &other) {
            delete[] str;
            copyData(other.str);
        }
        return *this;
    }

    // Геттер для доступа к строке
    const char* c_str() const { return str; }

    // Метод для шифрования (шифр Цезаря)
    // сдвиг (ключ) можно задать как параметр.
    Stroka Encrypt(int shift) const {
        char* buff = new char[length + 1];
        strcpy_s(buff, length + 1, str);
        for (size_t i = 0; i < length; i++) {
            // Если символ – буква латинского алфавита (учитываем и регистр)
            if (buff[i] >= 'A' && buff[i] <= 'Z') {
                buff[i] = char((buff[i] - 'A' + shift) % 26 + 'A');
            }
            else if (buff[i] >= 'a' && buff[i] <= 'z') {
                buff[i] = char((buff[i] - 'a' + shift) % 26 + 'a');
            }
            // Прочие символы оставляем без изменений.
        }
        Stroka result(buff);
        delete[] buff;
        return result;
    }

    // Перегрузка оператора ввода и вывода
    friend ostream& operator<<(ostream& os, const Stroka& s);
    friend istream& operator>>(istream& is, Stroka& s);
};

// Перегрузка оператора вывода: позволяет выводить объект Stroka через cout << s;
ostream& operator<<(ostream& os, const Stroka& s) {
    os << s.str;
    return os;
}

// Перегрузка оператора ввода: позволяет вводить объект Stroka через cin >> s;
// Для чтения всей строки (включая пробелы) будем использовать getline из потока.
istream& operator>>(istream& is, Stroka& s) {
    char buffer[256];
    // Считываем строку до символа новой строки.
    is.getline(buffer, 256);
    // Переприсваиваем объекту s новую строку.
    s = buffer;
    return is;
}

// =====================================================================
// ФУНКЦИЯ ДЛЯ РАБОТЫ С ФАЙЛОВЫМИ ПОТОКАМИ
// =====================================================================

// Функция демонстрирует запись объектов Stroka в файл и их последующее чтение.
void FileStreamDemo() {
    cout << "\n*** Демонстрация работы с файловыми потоками ***\n";
    // Создаем несколько объектов класса Stroka.
    Stroka s1("Здравствуйте, Hello");
    Stroka s2("Текст успешно записан!");
    Stroka s3("Прошу выберите другой пункт");

    // Записываем строки в текстовый файл
    ofstream outFile("stroki.txt");
    if (!outFile) {
        cerr << "Ошибка открытия файла для записи!" << endl;
        return;
    }
    outFile << s1 << endl;
    outFile << s2 << endl;
    outFile << s3 << endl;
    outFile.close();
    cout << "Текст записан в файл stroki.txt" << endl;

    // Чтение строк из файла
    ifstream inFile("stroki.txt");
    if (!inFile) {
        cerr << "Ошибка открытия файла для чтения!" << endl;
        return;
    }
    cout << "\nСодержимое файла:" << endl;
    Stroka temp;
    while (!inFile.eof()) {
        // Для корректного чтения сначала сбрасываем состояние
        inFile.clear();
        // Используем getline для чтения всей строки
        char buf[256];
        inFile.getline(buf, 256);
        // Если строка пустая – прерываем
        if (strlen(buf) == 0)
            break;
        temp = buf;
        cout << temp << endl;
    }
    inFile.close();
}

// =====================================================================
// ФУНКЦИЯ ШИФРОВАНИЯ С ИСПОЛЬЗОВАНИЕМ ПОТОКОВ
// =====================================================================

// Функция запрашивает строку и ключ шифрования от пользователя, выполняет шифрование
// и выводит результат как в консоль, так и записывает в файл.
void EncryptorDemo() {
    cout << "\n*** Программа-шифратор (шифр Цезаря) с использованием потоков ***\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // очистка буфера ввода
    cout << "Введите текст для шифрования: ";

    Stroka input;
    char buffer[256];
    cin.getline(buffer, 256);
    input = buffer;

    int shift;
    cout << "Введите сдвиг (ключ шифрования, целое число): ";
    cin >> shift;

    // Выполняем шифрование
    Stroka encrypted = input.Encrypt(shift);

    // Выводим результат в консоль
    cout << "\nЗашифрованный текст: " << encrypted << endl;

    // Записываем результат в файл
    ofstream outFile("encrypted.txt");
    if (!outFile) {
        cerr << "Ошибка открытия файла для записи зашифрованного текста!" << endl;
        return;
    }
    outFile << encrypted;
    outFile.close();
    cout << "Зашифрованный текст записан в файл encrypted.txt" << endl;
}

// =====================================================================
// ФУНКЦИЯ ДЛЯ ИЛЛЮСТРАЦИИ МЕТОДОВ УПРАВЛЕНИЯ СОСТОЯНИЕМ ПОТОКОВ
// =====================================================================

void StreamStateDemo() {
    cout << "\n*** Демонстрация работы с состоянием потоков ***\n";
    // Создадим поток для чтения из несуществующего файла, чтобы вызвать ошибку.
    ifstream fakeFile("nonexistent.txt");
    if (!fakeFile) {
        // Выводим сообщение об ошибке. Теперь можно проверить флаги потока.
        cout << "Поток ifstream в аварийном состоянии: "
            << (fakeFile.fail() ? "failbit установлен" : "failbit не установлен") << endl;
    }

    // Пример изменения формата вывода:
    cout << "\nДо изменения формата: " << 1234.5678 << endl;
    // Устанавливаем флаг фиксированной записи и точность 2.
    cout.setf(ios::fixed);
    cout.precision(2);
    cout << "После изменения формата (fixed, precision=2): " << 1234.5678 << endl;

    // Сбрасываем флаги форматирования:
    cout.unsetf(ios::fixed);
    cout.precision(6);
    cout << "После сброса формата: " << 1234.5678 << endl;

    // Пример управления состоянием потока ввода:
    cout << "\nВведите любое число: ";
    int num;
    cin >> num;
    if (cin.fail()) {
        cout << "Ошибка ввода. Сброс состояния потока." << endl;
        cin.clear();   // сбросить флаг ошибки
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // очистить буфер
    }
    else {
        cout << "Введено число: " << num << endl;
    }
}

// =====================================================================
// ГЛАВНАЯ ФУНКЦИЯ (меню)
// =====================================================================

void ShowMenu() {
    cout << "\n==============================" << endl;
    cout << "Лабораторная работа №8 (потоки)" << endl;
    cout << "1. Ввод/вывод объекта Stroka с использованием операторов << и >>" << endl;
    cout << "2. Работа с файловыми потоками (запись и чтение Stroka)" << endl;
    cout << "3. Шифратор (шифр Цезаря) с использованием потоков" << endl;
    cout << "4. Демонстрация управления состоянием потоков" << endl;
    cout << "5. Выход" << endl;
    cout << "Выберите пункт меню: ";
}

int main() {
    // Устанавливаем локаль для корректного вывода кириллицы.
    setlocale(LC_ALL, "ru");

    int choice = 0;
    do {
        ShowMenu();
        cin >> choice;
        // Очистка символа новой строки после ввода числа.
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (choice) {
        case 1: {
            cout << "\n*** Демонстрация операторов << и >> для класса Stroka ***\n";
            cout << "Введите строку (все, что вводится до нажатия Enter): ";
            Stroka s;
            // Используем перегруженный оператор ввода.
            cin >> s;
            cout << "Полученная строка: " << s << endl;
            break;
        }
        case 2: {
            FileStreamDemo();
            break;
        }
        case 3: {
            EncryptorDemo();
            break;
        }
        case 4: {
            StreamStateDemo();
            break;
        }
        case 5: {
            cout << "Выход из программы." << endl;
            break;
        }
        default:
            cout << "Неверный выбор! Попробуйте ещё раз." << endl;
        }
    } while (choice != 5);

    return 0;
}