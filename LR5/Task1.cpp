#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
using namespace std;

// ������� ��� �������� ��������, ����� � ���� � �������� ��������� �����.
void CountCharactersInFile(const string& filename)
{
    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "������ �������� ����� \"" << filename << "\" ��� ������!" << endl;
        return;
    }

    string line;
    size_t totalChars = 0;
    size_t totalWords = 0;
    size_t totalLines = 0;

    while (getline(inputFile, line)) {
        totalLines++;
        totalChars += line.size();
        // ��� �������� ���� ���������� istringstream
        istringstream iss(line);
        string word;
        while (iss >> word) {
            totalWords++;
        }
    }
    inputFile.close();

    cout << "\n���������� ������� ����� \"" << filename << "\":" << endl;
    cout << "���������� �����: " << totalLines << endl;
    cout << "����� ���������� ��������: " << totalChars << endl;
    cout << "���������� ����: " << totalWords << endl;
}

// ������� ��� ������ ��������� � ��������� ����� � �������� ���������� ���������.
void SearchSubstringInFile(const string& filename)
{
    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "������ �������� ����� \"" << filename << "\" ��� ������!" << endl;
        return;
    }

    // ��������� ���� ���� � ������
    stringstream buffer;
    buffer << inputFile.rdbuf();
    string content = buffer.str();
    inputFile.close();

    // ����������� ��������� ��� ������
    cout << "\n������� ��������� ��� ������: ";
    string substring;
    getline(cin, substring);

    if (substring.empty()) {
        cout << "��������� �����, ����� �� ��������." << endl;
        return;
    }

    size_t pos = 0;
    size_t count = 0;
    while ((pos = content.find(substring, pos)) != string::npos) {
        count++;
        pos += substring.length();
    }

    cout << "��������� \"" << substring << "\" ����������� � ����� " << count << " ���(�)." << endl;
}

// ������� ��� ���������� ������ (���� ������) �� �������� ����� � ���������� ���������� � �������� ����.
void EncryptFile(const string& inputFilename, const string& outputFilename)
{
    ifstream inputFile(inputFilename);
    if (!inputFile) {
        cerr << "������ �������� ����� \"" << inputFilename << "\" ��� ������!" << endl;
        return;
    }

    // ��������� ���� ����� �� �����
    stringstream buffer;
    buffer << inputFile.rdbuf();
    string content = buffer.str();
    inputFile.close();

    // ����������� ���� ����������
    int shift;
    cout << "\n������� ����� (����� �����) ��� ����������: ";
    cin >> shift;
    // ���� ������������ ��� ������������� ����� ��� ����� ������ 26 � ����� �������� ��� � ����������� ���������
    shift = shift % 26;   // ��� ���������� ��������

    // ���������� ������ (���� ������, ��� ��������� ����)
    for (size_t i = 0; i < content.size(); i++) {
        char ch = content[i];
        // ������������� ��� ��������� ���� (��������� � ��������)
        if (ch >= 'A' && ch <= 'Z') {
            content[i] = char((ch - 'A' + shift + 26) % 26 + 'A');
        }
        else if (ch >= 'a' && ch <= 'z') {
            content[i] = char((ch - 'a' + shift + 26) % 26 + 'a');
        }
        // ���� ��������� ��������� � ���������, �� ����� �������� �������������� ���������.
        // ������ ��� ������� ���� (���������, ��������� Windows-1251, ������� �� �������� �������)
        else if (ch >= '�' && ch <= '�') {
            content[i] = char((ch - '�' + shift + 32) % 32 + '�');
        }
        else if (ch >= '�' && ch <= '�') {
            content[i] = char((ch - '�' + shift + 32) % 32 + '�');
        }
    }

    // ���������� ������������� ����� � �������� ����
    ofstream outputFile(outputFilename);
    if (!outputFile) {
        cerr << "������ �������� ����� \"" << outputFilename << "\" ��� ������!" << endl;
        return;
    }
    outputFile << content;
    outputFile.close();

    cout << "\n������������� ����� ������� � ���� \"" << outputFilename << "\"." << endl;
}

// ������� ��� ������ �������� ����
void ShowMenu() {
    cout << "\n==============================" << endl;
    cout << "������������ ������ �5 (����-�����, ������ � �������)" << endl;
    cout << "1. ������� ��������, ����� � ���� � �����" << endl;
    cout << "2. ����� ��������� � �����" << endl;
    cout << "3. ���������� ����� (���� ������)" << endl;
    cout << "4. �����" << endl;
    cout << "�������� ����� ����: ";
}

int main()
{
    // ������������� ������ ��� ����������� ����������� ���������.
    setlocale(LC_ALL, "ru");

    const string inputFilename = "input.txt";      // ��� �������� ����� ��� �������� ������
    const string outputFilename = "encrypted.txt";   // ��� ����� ��� ������ �������������� ������

    int choice = 0;
    do {
        ShowMenu();
        cin >> choice;
        // ������� ������ ����� ����� ����� �����
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
            cout << "����� �� ���������." << endl;
            break;
        default:
            cout << "�������� �����! ���������� ��� ���." << endl;
        }
    } while (choice != 4);

    return 0;
}