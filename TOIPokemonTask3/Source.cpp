#include <iostream>
#include <string>

struct Pokemon {
    std::string name;
    int power;
    int level;
    int id;
};

struct Node {
    Pokemon data; // ������ ���������� � ���� ������
    Node* next; // ��������� �� ��������� ����
};

// ��������� ������� �������� � ��������������� ������
void insertSorted(Node*& head, const Pokemon& newData) {
    Node* newNode = new Node; // �������� ������ ����
    newNode->data = newData; // ���������� ������ ������ ����
    newNode->next = nullptr; // ����� ���� ��� �� ��������� �� ���������

    // ���� ������ ���� ��� ����� ���� ������ ���� ������
    if (head == nullptr || head->data.id >= newData.id) {
        newNode->next = head; // ��������� ����� ���� �� ������ ������� ������
        head = newNode; // ����� ���� ���������� ������� ������
        return; // ��������� ���������
    }

    // ����� ����� ��� ������� ������ ����
    Node* current = head;
    while (current->next != nullptr && current->next->data.id < newData.id) {
        current = current->next;
    }

    // ������� ������ ���� ����� ��������
    newNode->next = current->next;
    current->next = newNode;
}

// ������� ��� ������ ������� � �������� ��������� ��������
void searchAndDisplayByAttributeValue(Node* head, int targetId) {
    Node* current = head;
    bool found = false;

    // ����� ����� � �������� ��������� ID � ����� �� ������
    while (current != nullptr) {
        if (current->data.id == targetId) {
            found = true;
            std::cout << "������� ������ � ID " << targetId << ":" << std::endl;
            std::cout << "Name: " << current->data.name << ", Power: " << current->data.power << ", Level: " << current->data.level << ", ID: " << current->data.id << std::endl;
        }
        current = current->next;
    }

    // ���� �� ������� �� ����� ������ � �������� ID
    if (!found) {
        std::cout << "������ � ID " << targetId << " �� �������." << std::endl;
    }
}

// ��������� ��� ������������������ ����� ������
void randomInputData(Node*& head, int amount) {
    std::string Names[11] = { "Bulbasaur", "Raikachu", "Caterpie", "Pidgeot", "Meowth", "Rattata", "Clefairy", "Zubat", "Psyduck", "Abra", "Golem" };

    // ���������� ������ ���������� �������
    for (int i = 0; i < amount; ++i) {
        Pokemon newPokemon = { Names[rand() % 11], rand() % 436 + 1, rand() % 97 + 4, rand() % 9000 + 1000 };
        insertSorted(head, newPokemon);
    }
}

// ��������� ��� ������ ����� ������
void printList(Node* head) {
    Node* current = head;

    // ����� ������ ������� ���� ������
    while (current != nullptr) {
        std::cout << "Name: " << current->data.name << ", Power: " << current->data.power << ", Level: " << current->data.level << ", ID: " << current->data.id << std::endl;
        current = current->next;
    }
}

int main() {
    srand(time(nullptr)); // ������������� ���������� ��������� �����
    setlocale(LC_ALL, "Russian");

    Node* head = nullptr; // ��������� �� ������ ������
    int amount;
    std::cout << "������� ���������� ���������: ";
    std::cin >> amount;

    randomInputData(head, amount); // ����������������� ���� ������

    std::cout << "������ ���� ���������:" << std::endl;
    printList(head); // ����� ������ ���������

    int searchId;
    std::cout << "������� ID ��� ������: ";
    std::cin >> searchId;
    searchAndDisplayByAttributeValue(head, searchId); // ����� � ����� �������� �� ID

    // ������� ������, ���������� ��� ������
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
