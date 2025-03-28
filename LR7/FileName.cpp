#include <iostream>
#include <windows.h>  // Для функции Sleep() и работы с консолью (цвет и т.д.)
#include <conio.h>    // Для _getch() (если потребуется)
using namespace std;

// Абстрактный базовый класс Figure.
// Определяет интерфейс для всех фигур – процедуры Init, Show, Hide, Locat и Fly.
class Figure {
public:
    virtual void Init() = 0;        // Инициализация фигуры (задание параметров)
    virtual void Show() = 0;        // Отображение фигуры на экране
    virtual void Hide() = 0;        // Скрытие фигуры с экрана (например, очистка предыдущего положения)
    virtual void Locat(int x, int y) = 0;  // Установка новой позиции (координат)
    virtual void Fly(int dx, int dy) = 0;  // Перемещение фигуры (изменение координат с шагом)
    virtual ~Figure() {}            // Виртуальный деструктор
};

// Класс Point – простейшая точка.
// Он реализует функции для установки и изменения положения и служит базой для составных фигур.
class Point : public Figure {
protected:
    int x, y;     // Координаты точки
    int color;    // Цвет точки (код цвета консоли)
public:
    Point() : x(0), y(0), color(7) {}  // по умолчанию: (0,0), белый (7)
    Point(int _x, int _y, int _color = 7) : x(_x), y(_y), color(_color) {}

    // Виртуальные методы. В данной простой реализации Init() просто задаёт позицию.
    virtual void Init() override {
        // Например, можно запросить координаты с клавиатуры.
        cout << "Введите координаты точки (x y): ";
        cin >> x >> y;
    }
    virtual void Show() override {
        // Для демонстрации выводим информацию о точке.
        cout << "Point at (" << x << ", " << y << ") color " << color << endl;
    }
    virtual void Hide() override {
        // Имитация скрытия: вывод сообщения.
        cout << "Hiding point at (" << x << ", " << y << ")" << endl;
    }
    virtual void Locat(int newX, int newY) override {
        x = newX; y = newY;
    }
    virtual void Fly(int dx, int dy) override {
        x += dx; y += dy;
        // При перемещении можно обновлять изображение – сначала скрыть, затем показать:
        Hide();
        Show();
    }
    // Дополнительные аксессоры:
    int getX() const { return x; }
    int getY() const { return y; }
    void setColor(int c) { color = c; }
    int getColor() const { return color; }
};

// Класс Krug (круг). Он характеризуется центром (точка), радиусом и цветом.
class Krug : public Figure {
protected:
    Point center;
    int radius;
    int color;
public:
    Krug() : center(0, 0), radius(0), color(7) {}
    Krug(int x, int y, int r, int _color = 7) : center(x, y, _color), radius(r), color(_color) {}

    virtual void Init() override {
        cout << "Инициализация круга" << endl;
        cout << "Введите координаты центра (x y): ";
        int x, y; cin >> x >> y;
        center.Locat(x, y);
        cout << "Введите радиус круга: ";
        cin >> radius;
        cout << "Введите код цвета (число): ";
        cin >> color;
        center.setColor(color);
    }
    virtual void Show() override {
        cout << "Круг: Центр(" << center.getX() << ", " << center.getY() << "), радиус "
            << radius << ", цвет " << color << endl;
    }
    virtual void Hide() override {
        cout << "Скрытие круга с центром (" << center.getX() << ", " << center.getY() << ")" << endl;
    }
    virtual void Locat(int x, int y) override {
        center.Locat(x, y);
    }
    virtual void Fly(int dx, int dy) override {
        center.Fly(dx, dy);
        // Можно добавить задержку для имитации анимации.
        Sleep(200);
    }
    void setColor(int c) { color = c; center.setColor(c); }
    int getColor() const { return color; }
    int getRadius() const { return radius; }
    void setRadius(int r) { radius = r; }
};

// Класс Ring (кольцо). Это кольцо задаётся центром, внутренним и внешним радиусами,
// сектором (начальный и конечный угол) и цветом.
class Ring : public Figure {
protected:
    Point center;
    int innerRadius;
    int outerRadius;
    double startAngle;  // Начальный угол сектора (в градусах)
    double endAngle;    // Конечный угол сектора (в градусах)
    int color;
public:
    Ring() : center(0, 0), innerRadius(0), outerRadius(0), startAngle(0), endAngle(360), color(7) {}
    Ring(int x, int y, int innerR, int outerR, double sA = 0, double eA = 360, int col = 7)
        : center(x, y, col), innerRadius(innerR), outerRadius(outerR), startAngle(sA), endAngle(eA), color(col) {
    }

    virtual void Init() override {
        cout << "Инициализация кольца" << endl;
        cout << "Введите координаты центра (x y): ";
        int x, y;
        cin >> x >> y;
        center.Locat(x, y);
        cout << "Введите внутренний и внешний радиусы (inner outer): ";
        cin >> innerRadius >> outerRadius;
        cout << "Введите начальный и конечный угол сектора (в градусах): ";
        cin >> startAngle >> endAngle;
        cout << "Введите код цвета (число): ";
        cin >> color;
        center.setColor(color);
    }
    virtual void Show() override {
        cout << "Кольцо: Центр(" << center.getX() << ", " << center.getY() << "), внутренний радиус "
            << innerRadius << ", внешний радиус " << outerRadius;
        cout << ", сектор от " << startAngle << " до " << endAngle << " градусов, цвет " << color << endl;
    }
    virtual void Hide() override {
        cout << "Скрытие кольца с центром (" << center.getX() << ", " << center.getY() << ")" << endl;
    }
    virtual void Locat(int x, int y) override {
        center.Locat(x, y);
    }
    virtual void Fly(int dx, int dy) override {
        center.Fly(dx, dy);
        Sleep(200);
    }
    // Дополнительные методы для сужения-расширения сектора и смены цвета.
    void ChangeSector(double newStart, double newEnd) {
        startAngle = newStart;
        endAngle = newEnd;
        cout << "Новый сектор: от " << startAngle << " до " << endAngle << " градусов" << endl;
    }
    void ChangeColor(int newColor) {
        color = newColor;
        center.setColor(newColor);
        cout << "Цвет кольца изменён на " << color << endl;
    }
    int getColor() const { return color; }
};

////////////////////////////////////////
// Основная программа.
////////////////////////////////////////
int main() {
    // Устанавливаем русскую локаль для корректного отображения кириллицы.
    setlocale(LC_ALL, "ru");

    // Для демонстрации создадим два объекта: круг и кольцо.
    Krug myCircle(10, 5, 3, 9);  // Центр (10,5), радиус 3, цвет (код 9)
    Ring myRing(20, 10, 2, 5, 45, 315, 12);  // Центр (20,10), внутренний радиус 2, внешний 5, сектор от 45 до 315, цвет 12

    // Отобразим фигуры на экране.
    myCircle.Show();
    myRing.Show();

    // Имитация перемещения фигур:
    cout << "\nПеремещение фигур...\n" << endl;
    for (int i = 0; i < 5; i++) {
        // Перемещаем круг на 1 вправо и 1 вниз.
        myCircle.Fly(1, 1);
        // Перемещаем кольцо на 2 влево и 1 вверх.
        myRing.Fly(-2, -1);

        // Обновляем изображение фигур:
        myCircle.Show();
        myRing.Show();

        Sleep(500);
    }

    // Демонстрация дополнительных возможностей для кольца:
    cout << "\nИзменение свойств кольца:" << endl;
    // Изменение сектора (сужение или расширение).
    myRing.ChangeSector(90, 270);
    myRing.Show();

    // Смена цвета (код цвета изменяется, например, на 14).
    myRing.ChangeColor(14);
    myRing.Show();

    // Ждем нажатия клавиши для завершения.
    cout << "\nНажмите любую клавишу для выхода..." << endl;
    _getch();
    return 0;
}