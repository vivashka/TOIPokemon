#include <iostream>

struct Pokemon {
    std::string name;
    int power;
    int level;
    int id;
};

// Структура для узла дерева индексов по силе
struct PowerNode {
    int power;
    int index; // Индекс в массиве покемонов
    PowerNode* left; // Левый потомок
    PowerNode* right; // Правый потомок
};

// Функция для генерации случайного числа в заданном диапазоне
int Random(int start, int end) {
    int x = rand() % (end - start + 1) + start;
    return x;
}

// Процедура для рандомизированного ввода данных
void randomInputData(Pokemon pokemons[], int& size) {
    std::string Names[11]{ "Bulbasaur", "Raikachu", "Caterpie", "Pidgeot", "Meowth", "Rattata", "Clefairy", "Zubat", "Psyduck", "Abra", "Golem" };
    int amount;
    std::cout << "Введите количество покемонов: ";
    std::cin >> amount;
    for (int i = 0; i < amount; ++i) {
        pokemons[i] = Pokemon{ Names[Random(0, 10)], Random(23, 436), Random(4, 100), Random(1000, 9999) };
        ++size;
    }
}

// Функция для вставки узла в дерево индексов по силе
PowerNode* insertPowerTree(PowerNode* root, int power, int index) {
    if (root == nullptr) {
        return new PowerNode{ power, index, nullptr, nullptr };
    }
    else if (power < root->power) {
        root->left = insertPowerTree(root->left, power, index);
    }
    else if (power > root->power) {
        root->right = insertPowerTree(root->right, power, index);
    }
    else {
        // Если сила уже есть в дереве, обновляем индекс
        root->index = index;
    }
    return root;
}

// Функция для поиска узла в дереве индексов по силе
PowerNode* searchPowerTree(PowerNode* root, int power) {
    if (root == nullptr) {
        return nullptr;
    }
    else if (root->power == power) {
        return root;
    }
    else if (power < root->power) {
        return searchPowerTree(root->left, power);
    }
    else {
        return searchPowerTree(root->right, power);
    }
}

// Функция для вывода дерева индексов по силе в порядке возрастания
void inorderPowerTree(PowerNode* root) {
    if (root != nullptr) {
        inorderPowerTree(root->left);
        std::cout << "Power: " << root->power << ", Index: " << root->index << std::endl;
        inorderPowerTree(root->right);
    }
}

// Функция для вывода покемонов по силе в порядке возрастания
void printPokemonsByPower(Pokemon pokemons[], int size, PowerNode* root) {
    if (root != nullptr) {
        printPokemonsByPower(pokemons, size, root->left);
        std::cout << "Имя: " << pokemons[root->index].name << ", Сила: " << pokemons[root->index].power << ", Уровень: " << pokemons[root->index].level << ", ID: " << pokemons[root->index].id << std::endl << std::endl;
        printPokemonsByPower(pokemons, size, root->right);
    }
}

// Функция для удаления узла из дерева индексов по силе
PowerNode* deletePowerNode(PowerNode* root, int power) {
    if (root == nullptr) {
        return nullptr;
    }
    else if (power < root->power) {
        root->left = deletePowerNode(root->left, power);
    }
    else if (power > root->power) {
        root->right = deletePowerNode(root->right, power);
    }
    else {
        // Если узел является листом
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            root = nullptr;
        }
        // Если узел имеет только один дочерний узел
        else if (root->left == nullptr) {
            PowerNode* temp = root;
            root = root->right;
            delete temp;
        }
        else if (root->right == nullptr) {
            PowerNode* temp = root;
            root = root->left;
            delete temp;
        }
        // Если узел имеет два дочерних узла
        else {
            PowerNode* temp = root->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            root->power = temp->power;
            root->index = temp->index;
            root->right = deletePowerNode(root->right, temp->power);
        }
    }
    return root;
}
int main() {
    setlocale(LC_ALL, "Russian");
    Pokemon pokemons[100];
    int size = 0;
    randomInputData(pokemons, size);

    // Создаем индекс по силе
    PowerNode* root = nullptr;
    for (int i = 0; i < size; ++i) {
        root = insertPowerTree(root, pokemons[i].power, i);
    }

    // Выводим покемонов по силе в порядке возрастания
    std::cout << "Покемоны по силе в порядке возрастания:" << std::endl;
    printPokemonsByPower(pokemons, size, root);

    // Ищем покемона по силе
    int searchPower;
    std::cout << "Введите силу покемона для поиска: ";
    std::cin >> searchPower;
    PowerNode* foundNode = searchPowerTree(root, searchPower);
    if (foundNode != nullptr) {
        std::cout << "Найден покемон:" << std::endl;
        std::cout << "Имя: " << pokemons[foundNode->index].name << ", Сила: " << pokemons[foundNode->index].power << ", Уровень: " << pokemons[foundNode->index].level << ", ID: " << pokemons[foundNode->index].id << std::endl;
    }
    else {
        std::cout << "Покемон с такой силой не найден." << std::endl;
    }

    // Редактируем покемона по силе
    int editPower;
    std::cout << "Введите силу покемона для редактирования: ";
    std::cin >> editPower;
    foundNode = searchPowerTree(root, editPower);
    if (foundNode != nullptr) {
        std::cout << "Текущие данные покемона:" << std::endl;
        std::cout << "Имя: " << pokemons[foundNode->index].name << ", Сила: " << pokemons[foundNode->index].power << ", Уровень: " << pokemons[foundNode->index].level << ", ID: " << pokemons[foundNode->index].id << std::endl;

        std::string newName;
        int newPower;
        int newLevel;
        int newId;
        std::cout << "Введите новые данные покемона:" << std::endl;
        std::cout << "Имя: ";
        std::cin >> newName;
        std::cout << "Сила: ";
        std::cin >> newPower;
        std::cout << "Уровень: ";
        std::cin >> newLevel;
        std::cout << "ID: ";
        std::cin >> newId;

        pokemons[foundNode->index].name = newName;
        pokemons[foundNode->index].power = newPower;
        pokemons[foundNode->index].level = newLevel;
        pokemons[foundNode->index].id = newId;

        // Обновляем индекс
        root = insertPowerTree(root, newPower, foundNode->index);
        root = deletePowerNode(root, editPower);
    }
    else {
        std::cout << "Покемон с такой силой не найден." << std::endl;
    }

    // Удаляем покемона по силе
    int deletePower;
    std::cout << "Введите силу покемона для удаления: ";
    std::cin >> deletePower;
    foundNode = searchPowerTree(root, deletePower);
    if (foundNode != nullptr) {
        // Удаляем из массива
        for (int i = foundNode->index; i < size - 1; ++i) {
            pokemons[i] = pokemons[i + 1];
        }
        --size;

        // Удаляем из индекса
        root = deletePowerNode(root, deletePower);
    }
    else {
        std::cout << "Покемон с такой силой не найден." << std::endl;
    }
    std::cout << "Покемоны по силе в порядке возрастания:" << std::endl;
    printPokemonsByPower(pokemons, size, root);
    return 0;
}