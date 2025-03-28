#include <iostream>
#include <cstring>   // ��� ����������� �������: strlen, strcpy, strcat, strcmp
#include <cstdlib>   // ��� ������� malloc, calloc, free

using namespace std;

// 1. ����������� ����� ������
// ������� 1: ������������ ������� � ��������
int dlina1(const char* s)
{
    int len = 0;
    while (s[len] != '\0')
    {
        len++;
    }
    return len;
}

// ������� 2: ����� ���������
int dlina2(const char* s)
{
    const char* p = s;
    while (*p != '\0')
        p++;
    return int(p - s);
}

// ������� 3: ����������� ������
int dlina3(const char* s)
{
    if (*s == '\0')
        return 0;
    return 1 + dlina3(s + 1);
}

// 2. ������� ����������� ������ (������ strcpy)
// dest ������ ���� ���������� ������� ��������
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

// 3. ������� ��������� ����� (������ strcmp)
// ���������� 0, ���� ������ �����, ������������� �����, ���� ������ ������ ����������� � ������,
// ��� ������������� �����, ���� ������.
int sravn(const char* s1, const char* s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return (unsigned char)(*s1) - (unsigned char)(*s2);
}

// 4. ������� ������������ ����� (������ strcat)
// ���������� ������ src � ����� ������ dest; dest ������ ���� ���������� �������.
void konkat(char* dest, const char* src)
{
    // ���������� �� ����� dest
    while (*dest != '\0')
        dest++;
    // �������� src � �����
    while (*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

// ================================
// ������� ��� ������������ ������ � ������������ �������
// ================================

// ������������ ������ � ����������� ����������� �������� ��� ������ malloc()
void testWithMalloc()
{
    cout << "\n*** ���� � �������������� malloc() ***\n";

    // �������� ������ ��� ���� ����� (100 ���� ������)
    char* str1 = (char*)malloc(100);
    char* str2 = (char*)malloc(100);
    if (!str1 || !str2)
    {
        cerr << "������ ��������� ������ (malloc)!" << endl;
        exit(1);
    }

    // �������������� ������ � ������� ����� ������� �����������
    kopir(str1, "Hello, ");
    kopir(str2, "World!");

    // ������� ����� ����� � �������������� ���������� �������
    cout << "����� str1 (dlina1): " << dlina1(str1) << endl;
    cout << "����� str2 (dlina2): " << dlina2(str2) << endl;
    cout << "����� str1 (dlina3): " << dlina3(str1) << endl;

    // ��������� ������������: str1 = str1 + str2
    konkat(str1, str2);
    cout << "��������� ������������ (str1): " << str1 << endl;

    // ��������� �����:
    // �������� ����� ������ str2 � ������ ������������ ������� ������
    char* tmp = (char*)malloc(100);
    if (!tmp)
    {
        cerr << "������ ��������� ������ ��� tmp!" << endl;
        exit(1);
    }
    kopir(tmp, str2);
    int cmp = sravn(str2, tmp);
    cout << "��������� str2 � tmp (���������): " << cmp << endl;

    // ����������� ������
    free(str1);
    free(str2);
    free(tmp);
}

// ������������ ������ � ����������� ����������� �������� ��� ������ calloc()
// ������� calloc() ���������� �� malloc() ���, ��� �������������� ���������� ������ ������.
void testWithCalloc()
{
    cout << "\n*** ���� � �������������� calloc() ***\n";

    // �������� ������ ��� ���� ����� (100 ��������� �� sizeof(char) ������)
    char* str1 = (char*)calloc(100, sizeof(char));
    char* str2 = (char*)calloc(100, sizeof(char));
    if (!str1 || !str2)
    {
        cerr << "������ ��������� ������ (calloc)!" << endl;
        exit(1);
    }

    kopir(str1, "Dynamic ");
    kopir(str2, "String");

    cout << "����� str1 (dlina1): " << dlina1(str1) << endl;
    cout << "����� str2 (dlina2): " << dlina2(str2) << endl;

    konkat(str1, str2);
    cout << "��������� ������������ (str1): " << str1 << endl;

    // ��� ������������ �������: calloc � malloc.
    // ��� calloc ������ ���������������� ������, � ��� malloc � ���.
    cout << "������, ���������� calloc, ���������������� ������, ������� ����� ����� ��������� ����� ������� ������ ������.\n";

    free(str1);
    free(str2);
}

// ������������ ���������� ������� � ������� �����
void testArrayStrings()
{
    cout << "\n*** ���� ������ � �������� ����� ***\n";
    const int numStrings = 3;
    const int sizeStr = 100;
    // �������� ������ ���������� �� ������ (����������� ���������� ������ ����� calloc)
    char* arr[numStrings];
    for (int i = 0; i < numStrings; i++)
    {
        arr[i] = (char*)calloc(sizeStr, sizeof(char));
        if (!arr[i])
        {
            cerr << "������ �������� ������ � �������!" << endl;
            exit(1);
        }
    }

    // �������������� ������
    kopir(arr[0], "��������");
    kopir(arr[1], "������������ ������ �������!");
    kopir(arr[2], "Do you want?");

    // ������� ����� � ���������� ����� �� �������
    for (int i = 0; i < numStrings; i++)
    {
        cout << "arr[" << i << "] = \"" << arr[i] << "\"; ����� = " << dlina1(arr[i]) << endl;
    }

    // �������� ������������: ������� �� ������ ������ �����
    konkat(arr[1], " - ����������");
    cout << "\n����� ������������:\n";
    for (int i = 0; i < numStrings; i++)
    {
        cout << "arr[" << i << "] = \"" << arr[i] << "\", ����� = " << dlina1(arr[i]) << endl;
    }

    // ����������� ������ ��� ������ ������
    for (int i = 0; i < numStrings; i++)
    {
        free(arr[i]);
    }
}

// ================================
// main() � ������������ ������ ���� �������
// ================================
int main(void)
{
    setlocale(LC_ALL, "ru");

    cout << "������������ ������ �4. ��������� ��������� ������.\n";

    // �������� ����������� ������ (������������������ ��� ����������)
    char str1[] = "qwerty";
    char str2[] = "1234567890";

    cout << "\n--- ������ �� ������������ �������� ---\n";
    // ������������� ����������� ������� strlen (�� <cstring>)
    cout << "����������� strlen:\n";
    cout << "����� str1 = " << strlen(str1) << ", str2 = " << strlen(str2) << endl;

    // ������������� ���������� ������� ����������� ����� (����� ���������)
    cout << "\n���������� ������� ����������� �����:\n";
    cout << "dlina1(str1) = " << dlina1(str1) << ", dlina1(str2) = " << dlina1(str2) << endl;
    cout << "dlina2(str1) = " << dlina2(str1) << ", dlina2(str2) = " << dlina2(str2) << endl;
    cout << "dlina3(str1) = " << dlina3(str1) << ", dlina3(str2) = " << dlina3(str2) << endl;

    // ������������ �����������
    // ��� ������������ �������� ����� �����
    char kopia1[50], kopia2[50];
    // ����� ������������ ������ ����������, ����� ����� ���� ��������� �����.
    kopir(kopia1, str1);
    kopir(kopia2, str2);
    cout << "\n��������� �����������:\n";
    cout << "kopia1 = \"" << kopia1 << "\", kopia2 = \"" << kopia2 << "\"" << endl;

    // ������������ ��������� �����
    int compRes = sravn(str1, "qwerty"); // ������ ���� 0
    cout << "\n��������� ���������:\n";
    cout << "sravn(str1, \"qwerty\") = " << compRes << endl;

    // ������������ ������������
    // ��� ����� �������� ��� ����� ������-������� � ����������� ��������
    char conc1[100] = "������: ";
    char conc2[50] = "�����.";
    konkat(conc1, conc2);
    cout << "\n��������� ������������:\n";
    cout << "conc1 = \"" << conc1 << "\"" << endl;

    // -------------------------
    // ������ � ������������ ��������� ������ � �������������� malloc() � calloc()
    // -------------------------
    testWithMalloc();
    testWithCalloc();

    // -------------------------
    // ������ � �������� �����
    // -------------------------
    testArrayStrings();

    cout << "\n������ ���������. ������� ����� ������� ��� ������..." << endl;
    system("pause");
    return 0;
}