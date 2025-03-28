#include <iostream>
#include <iomanip>   // для setw и setprecision
#include <vector>
using namespace std;

// Функция для ввода матрицы (размер задается пользователем)
// Используем стандартный контейнер vector для хранения матрицы
void inputMatrix(vector<vector<double>>& matrix, int rows, int cols) {
    cout << "Введите элементы матрицы (" << rows << "x" << cols << "):\n";
    for (int i = 0; i < rows; i++) {
        vector<double> row;
        for (int j = 0; j < cols; j++) {
            double value;
            cout << "Элемент [" << i + 1 << "][" << j + 1 << "]: ";
            cin >> value;
            row.push_back(value);
        }
        matrix.push_back(row);
    }
}

// Функция для вывода матрицы с форматированием
void printMatrix(const vector<vector<double>>& matrix) {
    cout << "\nВывод матрицы:\n";
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            // setw(10) задаёт ширину поля, setprecision(4) – количество значащих цифр
            cout << setw(10) << setprecision(4) << elem << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

// Функция для нахождения минимального элемента матрицы
double findMin(const vector<vector<double>>& matrix) {
    // Инициализируем минимум первым элементом
    double minVal = matrix[0][0];
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            if (elem < minVal)
                minVal = elem;
        }
    }
    return minVal;
}

// Функция для нахождения максимального элемента матрицы
double findMax(const vector<vector<double>>& matrix) {
    double maxVal = matrix[0][0];
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            if (elem > maxVal)
                maxVal = elem;
        }
    }
    return maxVal;
}

// Функция для вычисления суммы всех элементов матрицы
double sumMatrix(const vector<vector<double>>& matrix) {
    double sum = 0.0;
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            sum += elem;
        }
    }
    return sum;
}

// Функция для вычисления среднего арифметического всех элементов матрицы
double averageMatrix(const vector<vector<double>>& matrix) {
    int rows = matrix.size();
    int cols = (rows > 0) ? matrix[0].size() : 0;
    int totalElements = rows * cols;
    double sum = sumMatrix(matrix);
    return (totalElements > 0) ? (sum / totalElements) : 0.0;
}

int main() {
    // Локаль для корректного вывода русских символов (при необходимости)
    setlocale(LC_ALL, "ru");

    int rows, cols;
    cout << "2. ЛАБОРАТОРНАЯ РАБОТА 2\n";
    cout << "Цель работы: приобретение навыков работы с матрицами и обработки данных.\n\n";

    cout << "Введите количество строк матрицы: ";
    cin >> rows;
    cout << "Введите количество столбцов матрицы: ";
    cin >> cols;

    // Создаем матрицу
    vector<vector<double>> matrix;
    inputMatrix(matrix, rows, cols);

    // Вывод матрицы с использованием форматирования
    printMatrix(matrix);

    // Вычисление характеристик матрицы
    double minVal = findMin(matrix);
    double maxVal = findMax(matrix);
    double sum = sumMatrix(matrix);
    double avg = averageMatrix(matrix);

    // Вывод результатов с форматированием
    cout << "Минимальный элемент матрицы: " << setprecision(4) << minVal << "\n";
    cout << "Максимальный элемент матрицы: " << setprecision(4) << maxVal << "\n";
    cout << "Сумма всех элементов матрицы: " << setprecision(4) << sum << "\n";
    cout << "Среднее арифметическое элементов матрицы: " << setprecision(4) << avg << "\n";

    cout << "\nНажмите любую клавишу для выхода...\n";
    system("pause");
    return 0;
}