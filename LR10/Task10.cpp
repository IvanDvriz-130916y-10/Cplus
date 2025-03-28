#include <iostream>
#include <string>
#include <cstdlib>   // ��� system("pause")
using namespace std;

//
// ������ ������ "����������� �������� ������"
//

template <typename T>
class SinglyLinkedList {
private:
    // ��������� ���� ������
    struct Node {
        T data;      // ������
        Node* next;  // ��������� �� ��������� �������
        Node(const T& data) : data(data), next(nullptr) {}
    };
    Node* head; // ��������� �� ������ ������� ������

public:
    // ����������� � ������ ������ ������
    SinglyLinkedList() : head(nullptr) {}

    // ���������� � ����������� ������, ������� ����� clear()
    ~SinglyLinkedList() { clear(); }

    // ������� ������ � ������� ��� ����
    void clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
    }

    // ���������� �������� � ����� ������
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

    // ������� �������� �������� �� �����.
    // ��� ��������������� ������������ ������� ���������, ������������ ����� ���������.
    // compare(������ ����, ����) ������ ���������� true, ���� ������ ������ �������.
    template <typename Key>
    bool removeByKey(const Key& key, bool (*compare)(const T&, const Key&)) {
        if (head == nullptr)
            return false;
        // ���� ������ ������� ��������:
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
        return false; // ������� �� ������
    }

    // ������� ������ ���� �� �����.
    // ���������� ��������� �� ���� ���� Node ��� nullptr, ���� ������� �� ������.
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

    // ������� ������ ������. ����������� ��������� �� ������� ������ ��� ������� ���� T.
    void print(void (*printFunc)(const T&)) const {
        Node* current = head;
        while (current != nullptr) {
            printFunc(current->data);
            current = current->next;
        }
        cout << endl;
    }

    // �������� �� ������� ������
    bool empty() const {
        return head == nullptr;
    }
};

//
// ��� ������ "Bus" � ������ �������� �� ��������
//

struct Bus {
    int busNumber;      // ����� ��������
    std::string driver; // ������� � ���������� ��������
    int route;          // ����� ��������

    // ������������
    Bus() : busNumber(0), driver(""), route(0) {}
    Bus(int bn, const std::string& drv, int rt) : busNumber(bn), driver(drv), route(rt) {}

    // ��� �������� ��������� ��������� ���������� �� ������ ��������
    bool operator==(const Bus& other) const {
        return busNumber == other.busNumber;
    }
};

//
// ������� ��������� ��� ������ ��� �������� �������� �� ������
// ���� ����� �������� �� ������ ��������� � ������, ������������ true.
//
bool compareBusNumber(const Bus& bus, const int& key) {
    return bus.busNumber == key;
}

//
// ������� ������ ���������� �� ��������
//
void printBus(const Bus& bus) {
    cout << "����� ��������: " << bus.busNumber
        << ", ��������: " << bus.driver
        << ", �������: " << bus.route << endl;
}

//
// �������� ���������
//
int main() {
    // ������������� ������ ��� ����������� ����������� ���������
    setlocale(LC_ALL, "ru");

    cout << "������������ ������ �10\n";
    cout << "���������� ���������� � ���������� ����� � �������������� ������� ������������ ������\n\n";

    // ������ ��� ������:
    // park � ��������, ����������� � �����;
    // routeList � ��������, ����������� �� ��������.
    SinglyLinkedList<Bus> park;
    SinglyLinkedList<Bus> routeList;

    // 1. �������������� ������������ ������ ��� ���� ��������� � �����.
    cout << "������� ���������� ��������� � �����: ";
    int n;
    cin >> n;

    // ��� ������� �������� ��������: ����� ��������, ������� � �������� ��������, ����� ��������
    for (int i = 0; i < n; i++) {
        int bn, rt;
        std::string driver;
        cout << "\n������� " << i + 1 << ":\n";
        cout << "������� ����� ��������: ";
        cin >> bn;
        cout << "������� ������� � �������� ��������: ";
        cin.ignore(); // ������� ������ ����� ������ �� ������ �����
        getline(cin, driver);
        cout << "������� ����� ��������: ";
        cin >> rt;
        Bus b(bn, driver, rt);
        park.push_back(b);
    }

    // �������� ���� ���������
    int choice;
    do {
        cout << "\n���� ��������:\n";
        cout << "1. ������� �������� �� �����\n";
        cout << "2. ������� �������� � ����\n";
        cout << "3. ������� ���������� �� ���������, ����������� � �����\n";
        cout << "4. ������� ���������� �� ���������, ����������� �� ��������\n";
        cout << "5. �����\n";
        cout << "�������� �������� (1-5): ";
        cin >> choice;

        switch (choice) {
        case 1: {
            // ������� �������� �� ����� � ��� ������ ������������ � ������ ��������� �� ��������.
            cout << "������� ����� ��������, ����������� �� �����: ";
            int num;
            cin >> num;
            // ���� ������� � ������ ��������� � �����.
            auto node = park.findByKey<int>(num, compareBusNumber);
            if (node != nullptr) {
                Bus b = node->data;
                // ������� ��� �� ������ ��������� � �����
                bool removed = park.removeByKey<int>(num, compareBusNumber);
                if (removed) {
                    // ��������� � ������ ��������� �� ��������
                    routeList.push_back(b);
                    cout << "������� � ������� " << num << " ��������� �� �������.\n";
                }
            }
            else {
                cout << "������� � ������� " << num << " �� ������ � �����!\n";
            }
            break;
        }
        case 2: {
            // ������� �������� � ���� � ��� ������ ������������ �� ������ ��������� �� �������� � ������ ��������� � �����.
            cout << "������� ����� ��������, ����������� � ����: ";
            int num;
            cin >> num;
            auto node = routeList.findByKey<int>(num, compareBusNumber);
            if (node != nullptr) {
                Bus b = node->data;
                bool removed = routeList.removeByKey<int>(num, compareBusNumber);
                if (removed) {
                    park.push_back(b);
                    cout << "������� � ������� " << num << " ��������� � ����.\n";
                }
            }
            else {
                cout << "������� � ������� " << num << " �� ������ ����� ��������� �� ��������!\n";
            }
            break;
        }
        case 3: {
            // ����� ���������, ����������� � �����
            cout << "\n�������� �� ���������, ����������� � �����:\n";
            if (park.empty())
                cout << "���� ����.\n";
            else
                park.print(printBus);
            break;
        }
        case 4: {
            // ����� ���������, ����������� �� ��������
            cout << "\n�������� �� ���������, ����������� �� ��������:\n";
            if (routeList.empty())
                cout << "�� �������� ��� ���������.\n";
            else
                routeList.print(printBus);
            break;
        }
        case 5: {
            cout << "���������� ���������.\n";
            break;
        }
        default:
            cout << "�������� �����. ��������� ����.\n";
        }

    } while (choice != 5);

    cout << "\n��������� ���������. ������� ����� ������� ��� ������...\n";
    system("pause");
    return 0;
}