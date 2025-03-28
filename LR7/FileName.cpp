#include <iostream>
#include <windows.h>  // ��� ������� Sleep() � ������ � �������� (���� � �.�.)
#include <conio.h>    // ��� _getch() (���� �����������)
using namespace std;

// ����������� ������� ����� Figure.
// ���������� ��������� ��� ���� ����� � ��������� Init, Show, Hide, Locat � Fly.
class Figure {
public:
    virtual void Init() = 0;        // ������������� ������ (������� ����������)
    virtual void Show() = 0;        // ����������� ������ �� ������
    virtual void Hide() = 0;        // ������� ������ � ������ (��������, ������� ����������� ���������)
    virtual void Locat(int x, int y) = 0;  // ��������� ����� ������� (���������)
    virtual void Fly(int dx, int dy) = 0;  // ����������� ������ (��������� ��������� � �����)
    virtual ~Figure() {}            // ����������� ����������
};

// ����� Point � ���������� �����.
// �� ��������� ������� ��� ��������� � ��������� ��������� � ������ ����� ��� ��������� �����.
class Point : public Figure {
protected:
    int x, y;     // ���������� �����
    int color;    // ���� ����� (��� ����� �������)
public:
    Point() : x(0), y(0), color(7) {}  // �� ���������: (0,0), ����� (7)
    Point(int _x, int _y, int _color = 7) : x(_x), y(_y), color(_color) {}

    // ����������� ������. � ������ ������� ���������� Init() ������ ����� �������.
    virtual void Init() override {
        // ��������, ����� ��������� ���������� � ����������.
        cout << "������� ���������� ����� (x y): ";
        cin >> x >> y;
    }
    virtual void Show() override {
        // ��� ������������ ������� ���������� � �����.
        cout << "Point at (" << x << ", " << y << ") color " << color << endl;
    }
    virtual void Hide() override {
        // �������� �������: ����� ���������.
        cout << "Hiding point at (" << x << ", " << y << ")" << endl;
    }
    virtual void Locat(int newX, int newY) override {
        x = newX; y = newY;
    }
    virtual void Fly(int dx, int dy) override {
        x += dx; y += dy;
        // ��� ����������� ����� ��������� ����������� � ������� ������, ����� ��������:
        Hide();
        Show();
    }
    // �������������� ���������:
    int getX() const { return x; }
    int getY() const { return y; }
    void setColor(int c) { color = c; }
    int getColor() const { return color; }
};

// ����� Krug (����). �� ��������������� ������� (�����), �������� � ������.
class Krug : public Figure {
protected:
    Point center;
    int radius;
    int color;
public:
    Krug() : center(0, 0), radius(0), color(7) {}
    Krug(int x, int y, int r, int _color = 7) : center(x, y, _color), radius(r), color(_color) {}

    virtual void Init() override {
        cout << "������������� �����" << endl;
        cout << "������� ���������� ������ (x y): ";
        int x, y; cin >> x >> y;
        center.Locat(x, y);
        cout << "������� ������ �����: ";
        cin >> radius;
        cout << "������� ��� ����� (�����): ";
        cin >> color;
        center.setColor(color);
    }
    virtual void Show() override {
        cout << "����: �����(" << center.getX() << ", " << center.getY() << "), ������ "
            << radius << ", ���� " << color << endl;
    }
    virtual void Hide() override {
        cout << "������� ����� � ������� (" << center.getX() << ", " << center.getY() << ")" << endl;
    }
    virtual void Locat(int x, int y) override {
        center.Locat(x, y);
    }
    virtual void Fly(int dx, int dy) override {
        center.Fly(dx, dy);
        // ����� �������� �������� ��� �������� ��������.
        Sleep(200);
    }
    void setColor(int c) { color = c; center.setColor(c); }
    int getColor() const { return color; }
    int getRadius() const { return radius; }
    void setRadius(int r) { radius = r; }
};

// ����� Ring (������). ��� ������ ������� �������, ���������� � ������� ���������,
// �������� (��������� � �������� ����) � ������.
class Ring : public Figure {
protected:
    Point center;
    int innerRadius;
    int outerRadius;
    double startAngle;  // ��������� ���� ������� (� ��������)
    double endAngle;    // �������� ���� ������� (� ��������)
    int color;
public:
    Ring() : center(0, 0), innerRadius(0), outerRadius(0), startAngle(0), endAngle(360), color(7) {}
    Ring(int x, int y, int innerR, int outerR, double sA = 0, double eA = 360, int col = 7)
        : center(x, y, col), innerRadius(innerR), outerRadius(outerR), startAngle(sA), endAngle(eA), color(col) {
    }

    virtual void Init() override {
        cout << "������������� ������" << endl;
        cout << "������� ���������� ������ (x y): ";
        int x, y;
        cin >> x >> y;
        center.Locat(x, y);
        cout << "������� ���������� � ������� ������� (inner outer): ";
        cin >> innerRadius >> outerRadius;
        cout << "������� ��������� � �������� ���� ������� (� ��������): ";
        cin >> startAngle >> endAngle;
        cout << "������� ��� ����� (�����): ";
        cin >> color;
        center.setColor(color);
    }
    virtual void Show() override {
        cout << "������: �����(" << center.getX() << ", " << center.getY() << "), ���������� ������ "
            << innerRadius << ", ������� ������ " << outerRadius;
        cout << ", ������ �� " << startAngle << " �� " << endAngle << " ��������, ���� " << color << endl;
    }
    virtual void Hide() override {
        cout << "������� ������ � ������� (" << center.getX() << ", " << center.getY() << ")" << endl;
    }
    virtual void Locat(int x, int y) override {
        center.Locat(x, y);
    }
    virtual void Fly(int dx, int dy) override {
        center.Fly(dx, dy);
        Sleep(200);
    }
    // �������������� ������ ��� �������-���������� ������� � ����� �����.
    void ChangeSector(double newStart, double newEnd) {
        startAngle = newStart;
        endAngle = newEnd;
        cout << "����� ������: �� " << startAngle << " �� " << endAngle << " ��������" << endl;
    }
    void ChangeColor(int newColor) {
        color = newColor;
        center.setColor(newColor);
        cout << "���� ������ ������ �� " << color << endl;
    }
    int getColor() const { return color; }
};

////////////////////////////////////////
// �������� ���������.
////////////////////////////////////////
int main() {
    // ������������� ������� ������ ��� ����������� ����������� ���������.
    setlocale(LC_ALL, "ru");

    // ��� ������������ �������� ��� �������: ���� � ������.
    Krug myCircle(10, 5, 3, 9);  // ����� (10,5), ������ 3, ���� (��� 9)
    Ring myRing(20, 10, 2, 5, 45, 315, 12);  // ����� (20,10), ���������� ������ 2, ������� 5, ������ �� 45 �� 315, ���� 12

    // ��������� ������ �� ������.
    myCircle.Show();
    myRing.Show();

    // �������� ����������� �����:
    cout << "\n����������� �����...\n" << endl;
    for (int i = 0; i < 5; i++) {
        // ���������� ���� �� 1 ������ � 1 ����.
        myCircle.Fly(1, 1);
        // ���������� ������ �� 2 ����� � 1 �����.
        myRing.Fly(-2, -1);

        // ��������� ����������� �����:
        myCircle.Show();
        myRing.Show();

        Sleep(500);
    }

    // ������������ �������������� ������������ ��� ������:
    cout << "\n��������� ������� ������:" << endl;
    // ��������� ������� (������� ��� ����������).
    myRing.ChangeSector(90, 270);
    myRing.Show();

    // ����� ����� (��� ����� ����������, ��������, �� 14).
    myRing.ChangeColor(14);
    myRing.Show();

    // ���� ������� ������� ��� ����������.
    cout << "\n������� ����� ������� ��� ������..." << endl;
    _getch();
    return 0;
}