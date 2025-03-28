#define _CRT_SECURE_NO_WARNINGS  // ���� ������ ��������� ��������������, ����� ���������� ���� ������

#include <iostream>
#include <fstream>
#include <cstring>    // ��� ������� ������ �� ��������: strlen, strcpy_s, strcat_s.
#include <cstdlib>    // ��� ������� exit.
#include <iomanip>    // ��� ������������� �������.
#include <limits>     // ��� numeric_limits.
using namespace std;

// =====================================================================
// ����� STROKA
// =====================================================================

class Stroka {
private:
    char* str;
    size_t length;

    // ��������������� ������� ��� ����������� ������
    void copyData(const char* source) {
        if (source) {
            length = strlen(source);
            str = new char[length + 1];
            // ���������� ���������� ������� strcpy_s
            strcpy_s(str, length + 1, source);
        }
        else {
            length = 0;
            str = new char[1];
            str[0] = '\0';
        }
    }
public:
    // ������������ � ����������
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

    // �������� ������������
    Stroka& operator=(const Stroka& other) {
        if (this != &other) {
            delete[] str;
            copyData(other.str);
        }
        return *this;
    }

    // ������ ��� ������� � ������
    const char* c_str() const { return str; }

    // ����� ��� ���������� (���� ������)
    // ����� (����) ����� ������ ��� ��������.
    Stroka Encrypt(int shift) const {
        char* buff = new char[length + 1];
        strcpy_s(buff, length + 1, str);
        for (size_t i = 0; i < length; i++) {
            // ���� ������ � ����� ���������� �������� (��������� � �������)
            if (buff[i] >= 'A' && buff[i] <= 'Z') {
                buff[i] = char((buff[i] - 'A' + shift) % 26 + 'A');
            }
            else if (buff[i] >= 'a' && buff[i] <= 'z') {
                buff[i] = char((buff[i] - 'a' + shift) % 26 + 'a');
            }
            // ������ ������� ��������� ��� ���������.
        }
        Stroka result(buff);
        delete[] buff;
        return result;
    }

    // ���������� ��������� ����� � ������
    friend ostream& operator<<(ostream& os, const Stroka& s);
    friend istream& operator>>(istream& is, Stroka& s);
};

// ���������� ��������� ������: ��������� �������� ������ Stroka ����� cout << s;
ostream& operator<<(ostream& os, const Stroka& s) {
    os << s.str;
    return os;
}

// ���������� ��������� �����: ��������� ������� ������ Stroka ����� cin >> s;
// ��� ������ ���� ������ (������� �������) ����� ������������ getline �� ������.
istream& operator>>(istream& is, Stroka& s) {
    char buffer[256];
    // ��������� ������ �� ������� ����� ������.
    is.getline(buffer, 256);
    // ��������������� ������� s ����� ������.
    s = buffer;
    return is;
}

// =====================================================================
// ������� ��� ������ � ��������� ��������
// =====================================================================

// ������� ������������� ������ �������� Stroka � ���� � �� ����������� ������.
void FileStreamDemo() {
    cout << "\n*** ������������ ������ � ��������� �������� ***\n";
    // ������� ��������� �������� ������ Stroka.
    Stroka s1("������������, Hello");
    Stroka s2("����� ������� �������!");
    Stroka s3("����� �������� ������ �����");

    // ���������� ������ � ��������� ����
    ofstream outFile("stroki.txt");
    if (!outFile) {
        cerr << "������ �������� ����� ��� ������!" << endl;
        return;
    }
    outFile << s1 << endl;
    outFile << s2 << endl;
    outFile << s3 << endl;
    outFile.close();
    cout << "����� ������� � ���� stroki.txt" << endl;

    // ������ ����� �� �����
    ifstream inFile("stroki.txt");
    if (!inFile) {
        cerr << "������ �������� ����� ��� ������!" << endl;
        return;
    }
    cout << "\n���������� �����:" << endl;
    Stroka temp;
    while (!inFile.eof()) {
        // ��� ����������� ������ ������� ���������� ���������
        inFile.clear();
        // ���������� getline ��� ������ ���� ������
        char buf[256];
        inFile.getline(buf, 256);
        // ���� ������ ������ � ���������
        if (strlen(buf) == 0)
            break;
        temp = buf;
        cout << temp << endl;
    }
    inFile.close();
}

// =====================================================================
// ������� ���������� � �������������� �������
// =====================================================================

// ������� ����������� ������ � ���� ���������� �� ������������, ��������� ����������
// � ������� ��������� ��� � �������, ��� � ���������� � ����.
void EncryptorDemo() {
    cout << "\n*** ���������-�������� (���� ������) � �������������� ������� ***\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ������� ������ �����
    cout << "������� ����� ��� ����������: ";

    Stroka input;
    char buffer[256];
    cin.getline(buffer, 256);
    input = buffer;

    int shift;
    cout << "������� ����� (���� ����������, ����� �����): ";
    cin >> shift;

    // ��������� ����������
    Stroka encrypted = input.Encrypt(shift);

    // ������� ��������� � �������
    cout << "\n������������� �����: " << encrypted << endl;

    // ���������� ��������� � ����
    ofstream outFile("encrypted.txt");
    if (!outFile) {
        cerr << "������ �������� ����� ��� ������ �������������� ������!" << endl;
        return;
    }
    outFile << encrypted;
    outFile.close();
    cout << "������������� ����� ������� � ���� encrypted.txt" << endl;
}

// =====================================================================
// ������� ��� ����������� ������� ���������� ���������� �������
// =====================================================================

void StreamStateDemo() {
    cout << "\n*** ������������ ������ � ���������� ������� ***\n";
    // �������� ����� ��� ������ �� ��������������� �����, ����� ������� ������.
    ifstream fakeFile("nonexistent.txt");
    if (!fakeFile) {
        // ������� ��������� �� ������. ������ ����� ��������� ����� ������.
        cout << "����� ifstream � ��������� ���������: "
            << (fakeFile.fail() ? "failbit ����������" : "failbit �� ����������") << endl;
    }

    // ������ ��������� ������� ������:
    cout << "\n�� ��������� �������: " << 1234.5678 << endl;
    // ������������� ���� ������������� ������ � �������� 2.
    cout.setf(ios::fixed);
    cout.precision(2);
    cout << "����� ��������� ������� (fixed, precision=2): " << 1234.5678 << endl;

    // ���������� ����� ��������������:
    cout.unsetf(ios::fixed);
    cout.precision(6);
    cout << "����� ������ �������: " << 1234.5678 << endl;

    // ������ ���������� ���������� ������ �����:
    cout << "\n������� ����� �����: ";
    int num;
    cin >> num;
    if (cin.fail()) {
        cout << "������ �����. ����� ��������� ������." << endl;
        cin.clear();   // �������� ���� ������
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // �������� �����
    }
    else {
        cout << "������� �����: " << num << endl;
    }
}

// =====================================================================
// ������� ������� (����)
// =====================================================================

void ShowMenu() {
    cout << "\n==============================" << endl;
    cout << "������������ ������ �8 (������)" << endl;
    cout << "1. ����/����� ������� Stroka � �������������� ���������� << � >>" << endl;
    cout << "2. ������ � ��������� �������� (������ � ������ Stroka)" << endl;
    cout << "3. �������� (���� ������) � �������������� �������" << endl;
    cout << "4. ������������ ���������� ���������� �������" << endl;
    cout << "5. �����" << endl;
    cout << "�������� ����� ����: ";
}

int main() {
    // ������������� ������ ��� ����������� ������ ���������.
    setlocale(LC_ALL, "ru");

    int choice = 0;
    do {
        ShowMenu();
        cin >> choice;
        // ������� ������� ����� ������ ����� ����� �����.
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (choice) {
        case 1: {
            cout << "\n*** ������������ ���������� << � >> ��� ������ Stroka ***\n";
            cout << "������� ������ (���, ��� �������� �� ������� Enter): ";
            Stroka s;
            // ���������� ������������� �������� �����.
            cin >> s;
            cout << "���������� ������: " << s << endl;
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
            cout << "����� �� ���������." << endl;
            break;
        }
        default:
            cout << "�������� �����! ���������� ��� ���." << endl;
        }
    } while (choice != 5);

    return 0;
}