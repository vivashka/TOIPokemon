#include <iostream> // Подключение заголовочного файла для ввода-вывода

// Определение структуры для представления покемона
struct Pokemon {
    std::string name; // Имя покемона
    int power; // Сила покемона
    int level; // Уровень покемона
    int id; // Идентификатор покемона
};

// Определение структуры для узла в дереве силы покемонов
struct PowerNode {
    int power; // Сила текущего покемона в узле
    int index; // Индекс покемона в массиве покемонов
    PowerNode* left; // Указатель на левого потомка
    PowerNode* right; // Указатель на правого потомка
};

// Функция для генерации случайного числа в заданном диапазоне
int Random(int start, int end) {
    int x = rand() % (end - start + 1) + start;
    return x;
}

// Функция для заполнения массива покемонов случайными данными
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

// Функция для вставки нового узла в дерево силы покемонов
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
        root->index = index; // Обновление индекса, если покемон с такой же силой уже существует
    }
    return root;
}

// Функция для поиска узла в дереве силы покемонов
PowerNode* searchPowerTree(PowerNode* root, int power) {
    if (root == nullptr) {
        return nullptr; // Возвращается nullptr, если дерево пустое
    }
    else if (root->power == power) {
        return root; // Возвращается узел, если его сила совпадает с искомой
    }
    else if (power < root->power) {
        return searchPowerTree(root->left, power); // Рекурсивный поиск в левом поддереве
    }
    else {
        return searchPowerTree(root->right, power); // Рекурсивный поиск в правом поддереве
    }
}

// Функция для вывода всех покемонов в порядке возрастания силы
void inorderPowerTree(PowerNode* root) {
    if (root != nullptr) {
        inorderPowerTree(root->left); // Рекурсивный обход левого поддерева
        std::cout << "Power: " << root->power << ", Index: " << root->index << std::endl; // Вывод силы и индекса текущего покемона
        inorderPowerTree(root->right); // Рекурсивный обход правого поддерева
    }
}

// Функция для вывода покемонов в порядке возрастания силы
void printPokemonsByPower(Pokemon pokemons[], int size, PowerNode* root) {
    if (root != nullptr) {
        printPokemonsByPower(pokemons, size, root->left); // Рекурсивный вывод покемонов из левого поддерева
        std::cout << "Имя: " << pokemons[root->index].name << ", Сила: " << pokemons[root->index].power << ", Уровень: " << pokemons[root->index].level << ", ID: " << pokemons[root->index].id << std::endl << std::endl; // Вывод данных текущего покемона
        printPokemonsByPower(pokemons, size, root->right); // Рекурсивный вывод покемонов из правого поддерева
    }
}

// Функция для удаления узла из дерева силы покемонов
PowerNode* deletePowerNode(PowerNode* root, int power) {
    if (root == nullptr) {
        return nullptr; // Возвращается nullptr, если дерево пустое
    }
    else if (power < root->power) {
        root->left = deletePowerNode(root->left, power); // Рекурсивное удаление из левого поддерева
    }
    else if (power > root->power) {
        root->right = deletePowerNode(root->right, power); // Рекурсивное удаление из правого поддерева
    }
    else {
        if (root->left == nullptr && root->right == nullptr) {
            delete root; // Удаление узла без потомков
            root = nullptr;
        }
        else if (root->left == nullptr) {
            PowerNode* temp = root;
            root = root->right; // Перемещение правого потомка на место удаляемого узла
            delete temp;
        }
        else if (root->right == nullptr) {
            PowerNode* temp = root;
            root = root->left; // Перемещение левого потомка на место удаляемого узла
            delete temp;
        }
        else {
            PowerNode* temp = root->right;
            while (temp->left != nullptr) {
                temp = temp->left; // Нахождение самого левого потомка в правом поддереве
            }
            root->power = temp->power; // Замена значения удаляемого узла на значение найденного наименьшего правого потомка
            root->index = temp->index;
            root->right = deletePowerNode(root->right, temp->power); // Рекурсивное удаление найденного наименьшего узла
        }
    }
    return root;
}

int main() {
    setlocale(LC_ALL, "Russian"); // Установка локали для русского языка
    Pokemon pokemons[100]; // Массив покемонов
    int size = 0; // Размер массива покемонов
    randomInputData(pokemons, size); // Заполнение массива случайными данными

    PowerNode* root = nullptr; // Указатель на корень дерева силы покемонов

    // Заполнение дерева силы покемонов
    for (int i = 0; i < size; ++i) {
        root = insertPowerTree(root, pokemons[i].power, i);
    }

    // Вывод покемонов по силе
    std::cout << "Покемоны по силе:" << std::endl;
    printPokemonsByPower(pokemons, size, root);

    // Поиск покемона по силе
    int searchPower;
    std::cout << "Введите силу покемона для поиска: ";
    std::cin >> searchPower;
    PowerNode* foundNode = searchPowerTree(root, searchPower);
    if (foundNode != nullptr) {
        std::cout << "Найден покемон:" << std::endl;
        std::cout << "Имя: " << pokemons[foundNode->index].name << ", Сила: " << pokemons[foundNode->index].power << ", Уровень: " << pokemons[foundNode->index].level << ", ID: " << pokemons[foundNode->index].id << std::endl;
    }
    else {
        std::cout << "Покемон с данной силой не найден." << std::endl;
    }

    // Редактирование покемона по силе
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

        // Обновление данных покемона
        pokemons[foundNode->index].name = newName;
        pokemons[foundNode->index].power = newPower;
        pokemons[foundNode->index].level = newLevel;
        pokemons[foundNode->index].id = newId;

        // Вставка обновленного покемона в дерево силы и удаление старого покемона
        root = insertPowerTree(root, newPower, foundNode->index);
        root = deletePowerNode(root, editPower);
    }
    else {
        std::cout << "Покемон с данной силой не найден." << std::endl;
    }

    // Удаление покемона по силе
    int deletePower;
    std::cout << "Введите силу покемона для удаления: ";
    std::cin >> deletePower;
    foundNode = searchPowerTree(root, deletePower);
    if (foundNode != nullptr) {
        // Сдвиг данных массива покемонов при удалении
        for (int i = foundNode->index; i < size - 1; ++i) {
            pokemons[i] = pokemons[i + 1];
        }
        --size;

        // Удаление покемона из дерева силы
        root = deletePowerNode(root, deletePower);
    }
    else {
        std::cout << "Покемон с данной силой не найден." << std::endl;
    }

    // Вывод покемонов после удаления
    std::cout << "Покемоны по силе после удаления:" << std::endl;
    printPokemonsByPower(pokemons, size, root);

    return 0; // Возврат нулевого значения, указывающего на успешное завершение программы
}
