#include <iostream>
#include <string>

struct Pokemon {
    std::string name;
    int power;
    int level;
    int id;
};

struct Node {
    Pokemon data; // Данные хранящиеся в узле списка
    Node* next; // Указатель на следующий узел
};

// Процедура вставки элемента в отсортированный список
void insertSorted(Node*& head, const Pokemon& newData) {
    Node* newNode = new Node; // Создание нового узла
    newNode->data = newData; // Заполнение данных нового узла
    newNode->next = nullptr; // Новый узел еще не указывает на следующий

    // Если список пуст или новый узел должен быть первым
    if (head == nullptr || head->data.id >= newData.id) {
        newNode->next = head; // Связываем новый узел со старым началом списка
        head = newNode; // Новый узел становится началом списка
        return; // Завершаем процедуру
    }

    // Поиск места для вставки нового узла
    Node* current = head;
    while (current->next != nullptr && current->next->data.id < newData.id) {
        current = current->next;
    }

    // Вставка нового узла после текущего
    newNode->next = current->next;
    current->next = newNode;
}

// Функция для вывода записей с заданным значением атрибута
void searchAndDisplayByAttributeValue(Node* head, int targetId) {
    Node* current = head;
    bool found = false;

    // Поиск узлов с заданным значением ID и вывод их данных
    while (current != nullptr) {
        if (current->data.id == targetId) {
            found = true;
            std::cout << "Найдена запись с ID " << targetId << ":" << std::endl;
            std::cout << "Name: " << current->data.name << ", Power: " << current->data.power << ", Level: " << current->data.level << ", ID: " << current->data.id << std::endl;
        }
        current = current->next;
    }

    // Если не найдено ни одной записи с заданным ID
    if (!found) {
        std::cout << "Запись с ID " << targetId << " не найдена." << std::endl;
    }
}

// Процедура для рандомизированного ввода данных
void randomInputData(Node*& head, int amount) {
    std::string Names[11] = { "Bulbasaur", "Raikachu", "Caterpie", "Pidgeot", "Meowth", "Rattata", "Clefairy", "Zubat", "Psyduck", "Abra", "Golem" };

    // Заполнение списка случайными данными
    for (int i = 0; i < amount; ++i) {
        Pokemon newPokemon = { Names[rand() % 11], rand() % 436 + 1, rand() % 97 + 4, rand() % 9000 + 1000 };
        insertSorted(head, newPokemon);
    }
}

// Процедура для вывода всего списка
void printList(Node* head) {
    Node* current = head;

    // Вывод данных каждого узла списка
    while (current != nullptr) {
        std::cout << "Name: " << current->data.name << ", Power: " << current->data.power << ", Level: " << current->data.level << ", ID: " << current->data.id << std::endl;
        current = current->next;
    }
}

int main() {
    srand(time(nullptr)); // Инициализация генератора случайных чисел
    setlocale(LC_ALL, "Russian");

    Node* head = nullptr; // Указатель на начало списка
    int amount;
    std::cout << "Введите количество покемонов: ";
    std::cin >> amount;

    randomInputData(head, amount); // Рандомизированный ввод данных

    std::cout << "Список всех покемонов:" << std::endl;
    printList(head); // Вывод списка покемонов

    int searchId;
    std::cout << "Введите ID для поиска: ";
    std::cin >> searchId;
    searchAndDisplayByAttributeValue(head, searchId); // Поиск и вывод покемона по ID

    // Очистка памяти, выделенной под список
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
