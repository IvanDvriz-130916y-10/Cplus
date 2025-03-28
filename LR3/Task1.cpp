#include <iostream>
#include <cstdlib>    // для функции exit()
#include <functional> // для std::greater при сортировке
#include <vector>
#include <algorithm>  // для std::sort (при сортировке в задаче 4)
using namespace std;

// Функция для вывода массива
void printArray(const int arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// ------------------------------
// 1. Сортировка методом «мини-макса» (выборочная сортировка)
// ------------------------------
void sortMinMax(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int imin = i; // индекс минимального элемента для текущей позиции
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[imin]) {
                imin = j;
            }
        }
        if (imin != i) {
            int temp = arr[i];
            arr[i] = arr[imin];
            arr[imin] = temp;
        }
    }
}

// ------------------------------
// 2. Сортировка пузырьком
// ------------------------------
void bubbleSort(int arr[], int n) {
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) { // для сортировки по возрастанию
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

// ------------------------------
// 3. Быстрая сортировка (quick sort)
// ------------------------------
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // выбираем опорный элемент
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// ------------------------------
// 4. Сортировка: четные по возрастанию, нечетные – по убыванию
// ------------------------------
void sortEvenAscOddDesc(const int arr[], int n) {
    vector<int> even;
    vector<int> odd;
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0)
            even.push_back(arr[i]);
        else
            odd.push_back(arr[i]);
    }
    sort(even.begin(), even.end());
    sort(odd.begin(), odd.end(), greater<int>());

    cout << "Четные (возрастание): ";
    for (int num : even)
        cout << num << " ";
    cout << "\nНечетные (убывание): ";
    for (int num : odd)
        cout << num << " ";
    cout << endl;
}

// ------------------------------
// 5. Сортировка подмассива по возрастанию на интервале [start, end)
// ------------------------------
void subarraySortAscending(int arr[], int start, int end) {
    // Стандартная пузырьковая сортировка на подмассиве индексов [start, end)
    for (int i = start; i < end - 1; i++) {
        for (int j = start; j < end - 1 - (i - start); j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// ------------------------------
// 6. Сортировка подмассива по убыванию на интервале [start, end)
// ------------------------------
void subarraySortDescending(int arr[], int start, int end) {
    // Пузырьковая сортировка для подмассива [start, end) в обратном порядке
    for (int i = start; i < end - 1; i++) {
        for (int j = start; j < end - 1 - (i - start); j++) {
            if (arr[j] < arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// ------------------------------
// main()
// ------------------------------
int main() {
    setlocale(LC_ALL, "ru");

    const int SIZE = 12;
    int origArr[SIZE] = { 2, 5, 8, 1, 4, 6, 3, -5, -9, 13, 0, 4 };
    int n = SIZE;
    int choice;

    while (true) {
        cout << "\nЛабораторная работа №3. Меню:" << endl;
        cout << "1. Сортировка методом «мини-макса» (выборочная сортировка)" << endl;
        cout << "2. Сортировка методом пузырька" << endl;
        cout << "3. Быстрая сортировка (quick sort)" << endl;
        cout << "4. Сортировка: четные по возрастанию, нечетные по убыванию" << endl;
        cout << "5. Сортировка подмассива по возрастанию (индексы от 1 до N2)" << endl;
        cout << "6. Сортировка подмассива по убыванию (индексы от 1 до N2)" << endl;
        cout << "7. Выход" << endl;
        cout << "Введите номер пункта меню: ";
        cin >> choice;

        if (choice == 7)
            break;

        // Для каждой операции работаем с копией исходного массива
        int arr[SIZE];
        for (int i = 0; i < n; i++)
            arr[i] = origArr[i];

        switch (choice) {
        case 1:
            cout << "\nИсходный массив:" << endl;
            printArray(arr, n);
            sortMinMax(arr, n);
            cout << "Отсортированный методом мини-макса:" << endl;
            printArray(arr, n);
            break;
        case 2:
            cout << "\nИсходный массив:" << endl;
            printArray(arr, n);
            bubbleSort(arr, n);
            cout << "Отсортированный методом пузырька:" << endl;
            printArray(arr, n);
            break;
        case 3:
            cout << "\nИсходный массив:" << endl;
            printArray(arr, n);
            quickSort(arr, 0, n - 1);
            cout << "Отсортированный методом быстрой сортировки:" << endl;
            printArray(arr, n);
            break;
        case 4:
            cout << "\nИсходный массив:" << endl;
            printArray(arr, n);
            cout << "\nСортировка: четные - по возрастанию, нечетные - по убыванию:" << endl;
            sortEvenAscOddDesc(arr, n);
            break;
        case 5: {
            int N2;
            cout << "\nИсходный массив:" << endl;
            printArray(arr, n);
            cout << "Введите N2 (верхняя граница индексов подмассива, начиная с индекса 1). N2 должно быть от 2 до " << n << ": ";
            cin >> N2;
            if (N2 < 2 || N2 > n) {
                cout << "Неверно указан интервал. Он должен быть от 2 до " << n << "!" << endl;
                break;
            }
            // Здесь сортируем подмассив с индексами от 1 до N2-1
            subarraySortAscending(arr, 1, N2);
            cout << "Массив после сортировки подмассива по возрастанию (индексы 1 до " << N2 - 1 << "):" << endl;
            printArray(arr, n);
            break;
        }
        case 6: {
            int N2;
            cout << "\nИсходный массив:" << endl;
            printArray(arr, n);
            cout << "Введите N2 (верхняя граница индексов подмассива, начиная с индекса 1). N2 должно быть от 2 до " << n << ": ";
            cin >> N2;
            if (N2 < 2 || N2 > n) {
                cout << "Неверно указан интервал. Он должен быть от 2 до " << n << "!" << endl;
                break;
            }
            subarraySortDescending(arr, 1, N2);
            cout << "Массив после сортировки подмассива по убыванию (индексы 1 до " << N2 - 1 << "):" << endl;
            printArray(arr, n);
            break;
        }
        default:
            cout << "\nНеверный выбор! Попробуйте снова." << endl;
        }
    }

    cout << "\nПрограмма завершена. Нажмите любую клавишу для выхода...\n";
    system("pause");
    return 0;
}