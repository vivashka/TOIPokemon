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
            std::cout << "Имя: " << current->data.name << ", Сила: " << current->data.power << ", Уровень: " 
                << current->data.level << ", ID: " << current->data.id << std::endl;
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


// Функция для удаления узла из списка по его ID
void removeNodeByID(Node*& head, int id) {
    if (head == nullptr) {
        return; // Если список пуст, ничего делать не нужно
    }

    // Если удаляемый узел - первый в списке
    if (head->data.id == id) {
        Node* temp = head; // Временный указатель на удаляемый узел
        head = head->next; // Перемещаем указатель на начало списка на следующий узел
        delete temp; // Освобождаем память, занимаемую удаляемым узлом
        return; // Завершаем функцию
    }

    // Если удаляемый узел не первый в списке
    Node* current = head;
    while (current->next != nullptr && current->next->data.id != id) {
        current = current->next; // Переходим к следующему узлу
    }

    // Проверяем, был ли найден узел для удаления
    if (current->next != nullptr) {
        Node* temp = current->next; // Временный указатель на удаляемый узел
        current->next = current->next->next; // Пропускаем удаляемый узел в списке
        delete temp; // Освобождаем память, занимаемую удаляемым узлом
    }
}

int main() {
    srand(time(nullptr)); // Инициализация генератора случайных чисел
    //setlocale(LC_ALL, "Russian");

    Node* head = nullptr; // Указатель на начало списка
    int amount;
    std::cout << "Введите количество покемонов: ";
    std::cin >> amount;

    randomInputData(head, amount); // Генерация случайных данных

    std::cout << "Список всех покемонов:" << std::endl;
    printList(head); // Вывод списка покемонов

    int searchId;
    std::cout << "Введите ID для удаления: ";
    std::cin >> searchId;
    removeNodeByID(head, searchId); // Удаление узла из списка по ID

    printList(head);
    
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
