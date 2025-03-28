#include <iostream>
#include <cstdlib>    // ��� ������� exit()
#include <functional> // ��� std::greater ��� ����������
#include <vector>
#include <algorithm>  // ��� std::sort (��� ���������� � ������ 4)
using namespace std;

// ������� ��� ������ �������
void printArray(const int arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// ------------------------------
// 1. ���������� ������� �����-����� (���������� ����������)
// ------------------------------
void sortMinMax(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int imin = i; // ������ ������������ �������� ��� ������� �������
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
// 2. ���������� ���������
// ------------------------------
void bubbleSort(int arr[], int n) {
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) { // ��� ���������� �� �����������
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
// 3. ������� ���������� (quick sort)
// ------------------------------
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // �������� ������� �������
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
// 4. ����������: ������ �� �����������, �������� � �� ��������
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

    cout << "������ (�����������): ";
    for (int num : even)
        cout << num << " ";
    cout << "\n�������� (��������): ";
    for (int num : odd)
        cout << num << " ";
    cout << endl;
}

// ------------------------------
// 5. ���������� ���������� �� ����������� �� ��������� [start, end)
// ------------------------------
void subarraySortAscending(int arr[], int start, int end) {
    // ����������� ����������� ���������� �� ���������� �������� [start, end)
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
// 6. ���������� ���������� �� �������� �� ��������� [start, end)
// ------------------------------
void subarraySortDescending(int arr[], int start, int end) {
    // ����������� ���������� ��� ���������� [start, end) � �������� �������
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
        cout << "\n������������ ������ �3. ����:" << endl;
        cout << "1. ���������� ������� �����-����� (���������� ����������)" << endl;
        cout << "2. ���������� ������� ��������" << endl;
        cout << "3. ������� ���������� (quick sort)" << endl;
        cout << "4. ����������: ������ �� �����������, �������� �� ��������" << endl;
        cout << "5. ���������� ���������� �� ����������� (������� �� 1 �� N2)" << endl;
        cout << "6. ���������� ���������� �� �������� (������� �� 1 �� N2)" << endl;
        cout << "7. �����" << endl;
        cout << "������� ����� ������ ����: ";
        cin >> choice;

        if (choice == 7)
            break;

        // ��� ������ �������� �������� � ������ ��������� �������
        int arr[SIZE];
        for (int i = 0; i < n; i++)
            arr[i] = origArr[i];

        switch (choice) {
        case 1:
            cout << "\n�������� ������:" << endl;
            printArray(arr, n);
            sortMinMax(arr, n);
            cout << "��������������� ������� ����-�����:" << endl;
            printArray(arr, n);
            break;
        case 2:
            cout << "\n�������� ������:" << endl;
            printArray(arr, n);
            bubbleSort(arr, n);
            cout << "��������������� ������� ��������:" << endl;
            printArray(arr, n);
            break;
        case 3:
            cout << "\n�������� ������:" << endl;
            printArray(arr, n);
            quickSort(arr, 0, n - 1);
            cout << "��������������� ������� ������� ����������:" << endl;
            printArray(arr, n);
            break;
        case 4:
            cout << "\n�������� ������:" << endl;
            printArray(arr, n);
            cout << "\n����������: ������ - �� �����������, �������� - �� ��������:" << endl;
            sortEvenAscOddDesc(arr, n);
            break;
        case 5: {
            int N2;
            cout << "\n�������� ������:" << endl;
            printArray(arr, n);
            cout << "������� N2 (������� ������� �������� ����������, ������� � ������� 1). N2 ������ ���� �� 2 �� " << n << ": ";
            cin >> N2;
            if (N2 < 2 || N2 > n) {
                cout << "������� ������ ��������. �� ������ ���� �� 2 �� " << n << "!" << endl;
                break;
            }
            // ����� ��������� ��������� � ��������� �� 1 �� N2-1
            subarraySortAscending(arr, 1, N2);
            cout << "������ ����� ���������� ���������� �� ����������� (������� 1 �� " << N2 - 1 << "):" << endl;
            printArray(arr, n);
            break;
        }
        case 6: {
            int N2;
            cout << "\n�������� ������:" << endl;
            printArray(arr, n);
            cout << "������� N2 (������� ������� �������� ����������, ������� � ������� 1). N2 ������ ���� �� 2 �� " << n << ": ";
            cin >> N2;
            if (N2 < 2 || N2 > n) {
                cout << "������� ������ ��������. �� ������ ���� �� 2 �� " << n << "!" << endl;
                break;
            }
            subarraySortDescending(arr, 1, N2);
            cout << "������ ����� ���������� ���������� �� �������� (������� 1 �� " << N2 - 1 << "):" << endl;
            printArray(arr, n);
            break;
        }
        default:
            cout << "\n�������� �����! ���������� �����." << endl;
        }
    }

    cout << "\n��������� ���������. ������� ����� ������� ��� ������...\n";
    system("pause");
    return 0;
}