#include <iostream>
#include <string>

// Структура, представляющая покемона
struct Pokemon {
    std::string name; // Имя покемона
    int power;        // Сила покемона
    int level;        // Уровень покемона
    int id;           // Идентификатор покемона
};

// Структура, представляющая узел связанного списка
struct Node {
    Pokemon data; // Данные, хранимые в узле
    Node* next;   // Указатель на следующий узел
};

// Функция для вставки данных в отсортированный по ID связанный список
void insertSorted(Node*& head, const Pokemon& newData) {
    Node* newNode = new Node;   // Создание нового узла
    newNode->data = newData;    // Присвоение новым данным
    newNode->next = nullptr;    // Новый узел пока не связан с другими

    // Если список пуст или первый элемент имеет ID больше или равный новому, вставляем новый элемент в начало списка
    if (head == nullptr || head->data.id >= newData.id) {
        newNode->next = head; // Связываем новый узел со старым началом списка
        head = newNode;       // Новый узел становится началом списка
        return;               // Завершаем функцию
    }

    // Поиск места для вставки нового узла
    Node* current = head;
    while (current->next != nullptr && current->next->data.id < newData.id) {
        current = current->next;
    }

    // Вставка нового узла
    newNode->next = current->next;
    current->next = newNode;
}

// Функция для поиска и вывода покемона по его ID
void searchAndDisplayByAttributeValue(Node* head, int targetId) {
    Node* current = head;
    bool found = false;

    // Поиск покемона по его ID и вывод его данных
    while (current != nullptr) {
        if (current->data.id == targetId) {
            found = true;
            std::cout << "Найден покемон с ID " << targetId << ":" << std::endl;
            std::cout << "Имя: " << current->data.name << ", Сила: " << current->data.power << ", Уровень: " << current->data.level << ", ID: " << current->data.id << std::endl;
        }
        current = current->next;
    }

    // Если покемон с указанным ID не найден
    if (!found) {
        std::cout << "Покемон с ID " << targetId << " не найден." << std::endl;
    }
}

// Функция для генерации случайных данных покемонов и их вставки в список
void randomInputData(Node*& head, int amount) {
    std::string Names[11] = { "Bulbasaur", "Raikachu", "Caterpie", "Pidgeot", "Meowth", "Rattata", "Clefairy", "Zubat", "Psyduck", "Abra", "Golem" };

    // Генерация и вставка случайных покемонов
    for (int i = 0; i < amount; ++i) {
        Pokemon newPokemon = { Names[rand() % 11], rand() % 436 + 1, rand() % 97 + 4, rand() % 9000 + 1000 };
        insertSorted(head, newPokemon);
    }
}

// Функция для вывода всего списка покемонов
void printList(Node* head) {
    Node* current = head;

    // Вывод данных каждого узла списка
    while (current != nullptr) {
        std::cout << "Имя: " << current->data.name << ", Сила: " << current->data.power << ", Уровень: " << current->data.level << ", ID: " << current->data.id << std::endl;
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

    randomInputData(head, amount); // Генерация случайных данных

    std::cout << "Список всех покемонов:" << std::endl;
    printList(head); // Вывод списка покемонов

    int searchId;
    std::cout << "Введите ID для поиска: ";
    std::cin >> searchId;
    searchAndDisplayByAttributeValue(head, searchId); // Поиск и вывод покемона по ID

    // Освобождение памяти, выделенной под список
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
