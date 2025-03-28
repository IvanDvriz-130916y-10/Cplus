#include <iostream>
#include <string>
#include <cstdlib>   // для system("pause")
using namespace std;

//
// Шаблон класса "односвязный линейный список"
//

template <typename T>
class SinglyLinkedList {
private:
    // Структура узла списка
    struct Node {
        T data;      // данные
        Node* next;  // указатель на следующий элемент
        Node(const T& data) : data(data), next(nullptr) {}
    };
    Node* head; // указатель на первый элемент списка

public:
    // Конструктор – создаём пустой список
    SinglyLinkedList() : head(nullptr) {}

    // Деструктор – освобождаем память, вызывая метод clear()
    ~SinglyLinkedList() { clear(); }

    // Очистка списка – удаляет все узлы
    void clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
    }

    // Добавление элемента в конец списка
    void push_back(const T& value) {
        Node* newNode = new Node(value);
        if (head == nullptr)
            head = newNode;
        else {
            Node* current = head;
            while (current->next != nullptr)
                current = current->next;
            current->next = newNode;
        }
    }

    // Функция удаления элемента по ключу.
    // Для универсальности используется функция сравнения, передаваемая через указатель.
    // compare(данные узла, ключ) должна возвращать true, если найден нужный элемент.
    template <typename Key>
    bool removeByKey(const Key& key, bool (*compare)(const T&, const Key&)) {
        if (head == nullptr)
            return false;
        // Если первый элемент подходит:
        if (compare(head->data, key)) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return true;
        }
        Node* current = head;
        while (current->next != nullptr && !compare(current->next->data, key))
            current = current->next;
        if (current->next != nullptr) {
            Node* temp = current->next;
            current->next = temp->next;
            delete temp;
            return true;
        }
        return false; // элемент не найден
    }

    // Функция поиска узла по ключу.
    // Возвращает указатель на узел типа Node или nullptr, если элемент не найден.
    template <typename Key>
    Node* findByKey(const Key& key, bool (*compare)(const T&, const Key&)) {
        Node* current = head;
        while (current != nullptr) {
            if (compare(current->data, key))
                return current;
            current = current->next;
        }
        return nullptr;
    }

    // Функция вывода списка. Принимается указатель на функцию вывода для объекта типа T.
    void print(void (*printFunc)(const T&)) const {
        Node* current = head;
        while (current != nullptr) {
            printFunc(current->data);
            current = current->next;
        }
        cout << endl;
    }

    // Проверка на пустоту списка
    bool empty() const {
        return head == nullptr;
    }
};

//
// Тип данных "Bus" – хранит сведения об автобусе
//

struct Bus {
    int busNumber;      // номер автобуса
    std::string driver; // фамилия с инициалами водителя
    int route;          // номер маршрута

    // Конструкторы
    Bus() : busNumber(0), driver(""), route(0) {}
    Bus(int bn, const std::string& drv, int rt) : busNumber(bn), driver(drv), route(rt) {}

    // Для простоты сравнение автобусов происходит по номеру автобуса
    bool operator==(const Bus& other) const {
        return busNumber == other.busNumber;
    }
};

//
// Функция сравнения для поиска или удаления автобуса по номеру
// Если номер автобуса из данных совпадает с ключом, возвращается true.
//
bool compareBusNumber(const Bus& bus, const int& key) {
    return bus.busNumber == key;
}

//
// Функция вывода информации об автобусе
//
void printBus(const Bus& bus) {
    cout << "Номер автобуса: " << bus.busNumber
        << ", Водитель: " << bus.driver
        << ", Маршрут: " << bus.route << endl;
}

//
// Основная программа
//
int main() {
    // Устанавливаем локаль для корректного отображения кириллицы
    setlocale(LC_ALL, "ru");

    cout << "Лабораторная работа №10\n";
    cout << "Управление автобусами в автобусном парке с использованием шаблона односвязного списка\n\n";

    // Создаём два списка:
    // park – автобусы, находящиеся в парке;
    // routeList – автобусы, находящиеся на маршруте.
    SinglyLinkedList<Bus> park;
    SinglyLinkedList<Bus> routeList;

    // 1. Первоначальное формирование данных обо всех автобусах в парке.
    cout << "Введите количество автобусов в парке: ";
    int n;
    cin >> n;

    // Для каждого автобуса вводятся: номер автобуса, фамилия и инициалы водителя, номер маршрута
    for (int i = 0; i < n; i++) {
        int bn, rt;
        std::string driver;
        cout << "\nАвтобус " << i + 1 << ":\n";
        cout << "Введите номер автобуса: ";
        cin >> bn;
        cout << "Введите фамилию и инициалы водителя: ";
        cin.ignore(); // удаляем символ новой строки из буфера ввода
        getline(cin, driver);
        cout << "Введите номер маршрута: ";
        cin >> rt;
        Bus b(bn, driver, rt);
        park.push_back(b);
    }

    // Основное меню программы
    int choice;
    do {
        cout << "\nМеню операций:\n";
        cout << "1. Автобус выезжает из парка\n";
        cout << "2. Автобус въезжает в парк\n";
        cout << "3. Вывести информацию об автобусах, находящихся в парке\n";
        cout << "4. Вывести информацию об автобусах, находящихся на маршруте\n";
        cout << "5. Выход\n";
        cout << "Выберите операцию (1-5): ";
        cin >> choice;

        switch (choice) {
        case 1: {
            // Автобус выезжает из парка – его данные перемещаются в список автобусов на маршруте.
            cout << "Введите номер автобуса, выезжающего из парка: ";
            int num;
            cin >> num;
            // Ищем автобус в списке автобусов в парке.
            auto node = park.findByKey<int>(num, compareBusNumber);
            if (node != nullptr) {
                Bus b = node->data;
                // Удаляем его из списка автобусов в парке
                bool removed = park.removeByKey<int>(num, compareBusNumber);
                if (removed) {
                    // Добавляем в список автобусов на маршруте
                    routeList.push_back(b);
                    cout << "Автобус с номером " << num << " перемещён на маршрут.\n";
                }
            }
            else {
                cout << "Автобус с номером " << num << " не найден в парке!\n";
            }
            break;
        }
        case 2: {
            // Автобус въезжает в парк – его данные перемещаются из списка автобусов на маршруте в список автобусов в парке.
            cout << "Введите номер автобуса, въезжающего в парк: ";
            int num;
            cin >> num;
            auto node = routeList.findByKey<int>(num, compareBusNumber);
            if (node != nullptr) {
                Bus b = node->data;
                bool removed = routeList.removeByKey<int>(num, compareBusNumber);
                if (removed) {
                    park.push_back(b);
                    cout << "Автобус с номером " << num << " перемещён в парк.\n";
                }
            }
            else {
                cout << "Автобус с номером " << num << " не найден среди автобусов на маршруте!\n";
            }
            break;
        }
        case 3: {
            // Вывод автобусов, находящихся в парке
            cout << "\nСведения об автобусах, находящихся в парке:\n";
            if (park.empty())
                cout << "Парк пуст.\n";
            else
                park.print(printBus);
            break;
        }
        case 4: {
            // Вывод автобусов, находящихся на маршруте
            cout << "\nСведения об автобусах, находящихся на маршруте:\n";
            if (routeList.empty())
                cout << "На маршруте нет автобусов.\n";
            else
                routeList.print(printBus);
            break;
        }
        case 5: {
            cout << "Завершение программы.\n";
            break;
        }
        default:
            cout << "Неверный выбор. Повторите ввод.\n";
        }

    } while (choice != 5);

    cout << "\nПрограмма завершена. Нажмите любую клавишу для выхода...\n";
    system("pause");
    return 0;
}