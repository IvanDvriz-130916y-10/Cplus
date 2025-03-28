#include <iostream>
#include <cstring>   // Для стандартных функций: strlen, strcpy, strcat, strcmp
#include <cstdlib>   // Для функций malloc, calloc, free

using namespace std;

// 1. Определение длины строки
// Вариант 1: классический подсчёт с индексом
int dlina1(const char* s)
{
    int len = 0;
    while (s[len] != '\0')
    {
        len++;
    }
    return len;
}

// Вариант 2: через указатель
int dlina2(const char* s)
{
    const char* p = s;
    while (*p != '\0')
        p++;
    return int(p - s);
}

// Вариант 3: рекурсивный способ
int dlina3(const char* s)
{
    if (*s == '\0')
        return 0;
    return 1 + dlina3(s + 1);
}

// 2. Функция копирования строки (аналог strcpy)
// dest должен быть достаточно большим массивом
void kopir(char* dest, const char* src)
{
    while (*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

// 3. Функция сравнения строк (аналог strcmp)
// Возвращает 0, если строки равны, положительное число, если первый символ различается и больше,
// или отрицательное число, если меньше.
int sravn(const char* s1, const char* s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return (unsigned char)(*s1) - (unsigned char)(*s2);
}

// 4. Функция конкатенации строк (аналог strcat)
// Дописывает строку src в конец строки dest; dest должна быть достаточно большой.
void konkat(char* dest, const char* src)
{
    // Сдвигаемся до конца dest
    while (*dest != '\0')
        dest++;
    // Копируем src в конец
    while (*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

// ================================
// Функции для демонстрации работы с динамической памятью
// ================================

// Демонстрация работы с динамически выделенными строками при помощи malloc()
void testWithMalloc()
{
    cout << "\n*** Тест с использованием malloc() ***\n";

    // Выделяем память для двух строк (100 байт каждая)
    char* str1 = (char*)malloc(100);
    char* str2 = (char*)malloc(100);
    if (!str1 || !str2)
    {
        cerr << "Ошибка выделения памяти (malloc)!" << endl;
        exit(1);
    }

    // Инициализируем строки с помощью наших функций копирования
    kopir(str1, "Hello, ");
    kopir(str2, "World!");

    // Выводим длины строк с использованием самописных функций
    cout << "Длина str1 (dlina1): " << dlina1(str1) << endl;
    cout << "Длина str2 (dlina2): " << dlina2(str2) << endl;
    cout << "Длина str1 (dlina3): " << dlina3(str1) << endl;

    // Выполняем конкатенацию: str1 = str1 + str2
    konkat(str1, str2);
    cout << "Результат конкатенации (str1): " << str1 << endl;

    // Сравнение строк:
    // Создадим копию строки str2 в другой динамической области памяти
    char* tmp = (char*)malloc(100);
    if (!tmp)
    {
        cerr << "Ошибка выделения памяти для tmp!" << endl;
        exit(1);
    }
    kopir(tmp, str2);
    int cmp = sravn(str2, tmp);
    cout << "Сравнение str2 и tmp (результат): " << cmp << endl;

    // Освобождаем память
    free(str1);
    free(str2);
    free(tmp);
}

// Демонстрация работы с динамически выделенными строками при помощи calloc()
// Функция calloc() отличается от malloc() тем, что инициализирует выделенную память нулями.
void testWithCalloc()
{
    cout << "\n*** Тест с использованием calloc() ***\n";

    // Выделяем память для двух строк (100 элементов по sizeof(char) каждая)
    char* str1 = (char*)calloc(100, sizeof(char));
    char* str2 = (char*)calloc(100, sizeof(char));
    if (!str1 || !str2)
    {
        cerr << "Ошибка выделения памяти (calloc)!" << endl;
        exit(1);
    }

    kopir(str1, "Dynamic ");
    kopir(str2, "String");

    cout << "Длина str1 (dlina1): " << dlina1(str1) << endl;
    cout << "Длина str2 (dlina2): " << dlina2(str2) << endl;

    konkat(str1, str2);
    cout << "Результат конкатенации (str1): " << str1 << endl;

    // Для демонстрации разницы: calloc и malloc.
    // При calloc память инициализирована нулями, а при malloc – нет.
    cout << "Память, выделенная calloc, инициализирована нулями, поэтому сразу после выделения можно ожидать пустую строку.\n";

    free(str1);
    free(str2);
}

// Демонстрация применения функций к массиву строк
void testArrayStrings()
{
    cout << "\n*** Тест работы с массивом строк ***\n";
    const int numStrings = 3;
    const int sizeStr = 100;
    // Создадим массив указателей на строки (динамически выделяемые строки через calloc)
    char* arr[numStrings];
    for (int i = 0; i < numStrings; i++)
    {
        arr[i] = (char*)calloc(sizeStr, sizeof(char));
        if (!arr[i])
        {
            cerr << "Ошибка создания строки в массиве!" << endl;
            exit(1);
        }
    }

    // Инициализируем строки
    kopir(arr[0], "Проверка");
    kopir(arr[1], "Тестирование прошло успешно!");
    kopir(arr[2], "Do you want?");

    // Выводим длины и содержимое строк из массива
    for (int i = 0; i < numStrings; i++)
    {
        cout << "arr[" << i << "] = \"" << arr[i] << "\"; Длина = " << dlina1(arr[i]) << endl;
    }

    // Применим конкатенацию: добавим ко второй строке текст
    konkat(arr[1], " - дополнение");
    cout << "\nПосле конкатенации:\n";
    for (int i = 0; i < numStrings; i++)
    {
        cout << "arr[" << i << "] = \"" << arr[i] << "\", длина = " << dlina1(arr[i]) << endl;
    }

    // Освобождаем память для каждой строки
    for (int i = 0; i < numStrings; i++)
    {
        free(arr[i]);
    }
}

// ================================
// main() – демонстрация работы всех функций
// ================================
int main(void)
{
    setlocale(LC_ALL, "ru");

    cout << "Лабораторная работа №4. Обработка строковых данных.\n";

    // Исходные статические строки (инициализированные при компиляции)
    char str1[] = "qwerty";
    char str2[] = "1234567890";

    cout << "\n--- Работа со статическими строками ---\n";
    // Использование стандартной функции strlen (из <cstring>)
    cout << "Стандартная strlen:\n";
    cout << "Длина str1 = " << strlen(str1) << ", str2 = " << strlen(str2) << endl;

    // Использование самописных функций определения длины (тремя способами)
    cout << "\nСамописные функции определения длины:\n";
    cout << "dlina1(str1) = " << dlina1(str1) << ", dlina1(str2) = " << dlina1(str2) << endl;
    cout << "dlina2(str1) = " << dlina2(str1) << ", dlina2(str2) = " << dlina2(str2) << endl;
    cout << "dlina3(str1) = " << dlina3(str1) << ", dlina3(str2) = " << dlina3(str2) << endl;

    // Демонстрация копирования
    // Для демонстрации создадим копии строк
    char kopia1[50], kopia2[50];
    // Перед копированием меняем содержимое, чтобы можно было проверить обмен.
    kopir(kopia1, str1);
    kopir(kopia2, str2);
    cout << "\nРезультат копирования:\n";
    cout << "kopia1 = \"" << kopia1 << "\", kopia2 = \"" << kopia2 << "\"" << endl;

    // Демонстрация сравнения строк
    int compRes = sravn(str1, "qwerty"); // должно быть 0
    cout << "\nРезультат сравнения:\n";
    cout << "sravn(str1, \"qwerty\") = " << compRes << endl;

    // Демонстрация конкатенации
    // Для этого создадим две новые строки-массивы с достаточным размером
    char conc1[100] = "Начало: ";
    char conc2[50] = "Конец.";
    konkat(conc1, conc2);
    cout << "\nРезультат конкатенации:\n";
    cout << "conc1 = \"" << conc1 << "\"" << endl;

    // -------------------------
    // Теперь – динамическое выделение памяти с использованием malloc() и calloc()
    // -------------------------
    testWithMalloc();
    testWithCalloc();

    // -------------------------
    // Работа с массивом строк
    // -------------------------
    testArrayStrings();

    cout << "\nРабота завершена. Нажмите любую клавишу для выхода..." << endl;
    system("pause");
    return 0;
}