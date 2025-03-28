#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
using namespace std;

// Функция для подсчёта символов, строк и слов в заданном текстовом файле.
void CountCharactersInFile(const string& filename)
{
    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "Ошибка открытия файла \"" << filename << "\" для чтения!" << endl;
        return;
    }

    string line;
    size_t totalChars = 0;
    size_t totalWords = 0;
    size_t totalLines = 0;

    while (getline(inputFile, line)) {
        totalLines++;
        totalChars += line.size();
        // Для подсчёта слов используем istringstream
        istringstream iss(line);
        string word;
        while (iss >> word) {
            totalWords++;
        }
    }
    inputFile.close();

    cout << "\nРезультаты анализа файла \"" << filename << "\":" << endl;
    cout << "Количество строк: " << totalLines << endl;
    cout << "Общее количество символов: " << totalChars << endl;
    cout << "Количество слов: " << totalWords << endl;
}

// Функция для поиска подстроки в текстовом файле и подсчёта количества вхождений.
void SearchSubstringInFile(const string& filename)
{
    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "Ошибка открытия файла \"" << filename << "\" для чтения!" << endl;
        return;
    }

    // Считываем весь файл в строку
    stringstream buffer;
    buffer << inputFile.rdbuf();
    string content = buffer.str();
    inputFile.close();

    // Запрашиваем подстроку для поиска
    cout << "\nВведите подстроку для поиска: ";
    string substring;
    getline(cin, substring);

    if (substring.empty()) {
        cout << "Подстрока пуста, поиск не выполнен." << endl;
        return;
    }

    size_t pos = 0;
    size_t count = 0;
    while ((pos = content.find(substring, pos)) != string::npos) {
        count++;
        pos += substring.length();
    }

    cout << "Подстрока \"" << substring << "\" встречается в файле " << count << " раз(а)." << endl;
}

// Функция для шифрования текста (шифр Цезаря) из входного файла и сохранения результата в выходной файл.
void EncryptFile(const string& inputFilename, const string& outputFilename)
{
    ifstream inputFile(inputFilename);
    if (!inputFile) {
        cerr << "Ошибка открытия файла \"" << inputFilename << "\" для чтения!" << endl;
        return;
    }

    // Считываем весь текст из файла
    stringstream buffer;
    buffer << inputFile.rdbuf();
    string content = buffer.str();
    inputFile.close();

    // Запрашиваем ключ шифрования
    int shift;
    cout << "\nВведите сдвиг (целое число) для шифрования: ";
    cin >> shift;
    // Если пользователь ввёл отрицательное число или число больше 26 – можно привести его к корректному диапазону
    shift = shift % 26;   // для латинского алфавита

    // Шифрование текста (шифр Цезаря, для латинских букв)
    for (size_t i = 0; i < content.size(); i++) {
        char ch = content[i];
        // Зашифровываем для латинских букв (заглавные и строчные)
        if (ch >= 'A' && ch <= 'Z') {
            content[i] = char((ch - 'A' + shift + 26) % 26 + 'A');
        }
        else if (ch >= 'a' && ch <= 'z') {
            content[i] = char((ch - 'a' + shift + 26) % 26 + 'a');
        }
        // Если требуется шифровать и кириллицу, то можно добавить дополнительную обработку.
        // Пример для русских букв (кириллица, кодировка Windows-1251, зависит от настроек системы)
        else if (ch >= 'А' && ch <= 'Я') {
            content[i] = char((ch - 'А' + shift + 32) % 32 + 'А');
        }
        else if (ch >= 'а' && ch <= 'я') {
            content[i] = char((ch - 'а' + shift + 32) % 32 + 'а');
        }
    }

    // Записываем зашифрованный текст в выходной файл
    ofstream outputFile(outputFilename);
    if (!outputFile) {
        cerr << "Ошибка открытия файла \"" << outputFilename << "\" для записи!" << endl;
        return;
    }
    outputFile << content;
    outputFile.close();

    cout << "\nЗашифрованный текст записан в файл \"" << outputFilename << "\"." << endl;
}

// Функция для показа главного меню
void ShowMenu() {
    cout << "\n==============================" << endl;
    cout << "Лабораторная работа №5 (Ввод-вывод, работа с файлами)" << endl;
    cout << "1. Подсчет символов, строк и слов в файле" << endl;
    cout << "2. Поиск подстроки в файле" << endl;
    cout << "3. Шифрование файла (шифр Цезаря)" << endl;
    cout << "4. Выход" << endl;
    cout << "Выберите пункт меню: ";
}

int main()
{
    // Устанавливаем локаль для корректного отображения кириллицы.
    setlocale(LC_ALL, "ru");

    const string inputFilename = "input.txt";      // имя входного файла для операций чтения
    const string outputFilename = "encrypted.txt";   // имя файла для записи зашифрованного текста

    int choice = 0;
    do {
        ShowMenu();
        cin >> choice;
        // очистка буфера ввода после ввода числа
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (choice) {
        case 1:
            CountCharactersInFile(inputFilename);
            break;
        case 2:
            SearchSubstringInFile(inputFilename);
            break;
        case 3:
            EncryptFile(inputFilename, outputFilename);
            break;
        case 4:
            cout << "Выход из программы." << endl;
            break;
        default:
            cout << "Неверный выбор! Попробуйте ещё раз." << endl;
        }
    } while (choice != 4);

    return 0;
}