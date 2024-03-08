#include <iostream>

struct Pokemon {
    std::string name;
    int power;
    int level;
    int id;
};

// ��������� ��� ���� ������ �������� �� ����
struct PowerNode {
    int power;
    int index; // ������ � ������� ���������
    PowerNode* left; // ����� �������
    PowerNode* right; // ������ �������
};

// ������� ��� ��������� ���������� ����� � �������� ���������
int Random(int start, int end) {
    int x = rand() % (end - start + 1) + start;
    return x;
}

// ��������� ��� ������������������ ����� ������
void randomInputData(Pokemon pokemons[], int& size) {
    std::string Names[11]{ "Bulbasaur", "Raikachu", "Caterpie", "Pidgeot", "Meowth", "Rattata", "Clefairy", "Zubat", "Psyduck", "Abra", "Golem" };
    int amount;
    std::cout << "������� ���������� ���������: ";
    std::cin >> amount;
    for (int i = 0; i < amount; ++i) {
        pokemons[i] = Pokemon{ Names[Random(0, 10)], Random(23, 436), Random(4, 100), Random(1000, 9999) };
        ++size;
    }
}

// ������� ��� ������� ���� � ������ �������� �� ����
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
        // ���� ���� ��� ���� � ������, ��������� ������
        root->index = index;
    }
    return root;
}

// ������� ��� ������ ���� � ������ �������� �� ����
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

// ������� ��� ������ ������ �������� �� ���� � ������� �����������
void inorderPowerTree(PowerNode* root) {
    if (root != nullptr) {
        inorderPowerTree(root->left);
        std::cout << "Power: " << root->power << ", Index: " << root->index << std::endl;
        inorderPowerTree(root->right);
    }
}

// ������� ��� ������ ��������� �� ���� � ������� �����������
void printPokemonsByPower(Pokemon pokemons[], int size, PowerNode* root) {
    if (root != nullptr) {
        printPokemonsByPower(pokemons, size, root->left);
        std::cout << "���: " << pokemons[root->index].name << ", ����: " << pokemons[root->index].power << ", �������: " << pokemons[root->index].level << ", ID: " << pokemons[root->index].id << std::endl << std::endl;
        printPokemonsByPower(pokemons, size, root->right);
    }
}

// ������� ��� �������� ���� �� ������ �������� �� ����
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
        // ���� ���� �������� ������
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            root = nullptr;
        }
        // ���� ���� ����� ������ ���� �������� ����
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
        // ���� ���� ����� ��� �������� ����
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

    // ������� ������ �� ����
    PowerNode* root = nullptr;
    for (int i = 0; i < size; ++i) {
        root = insertPowerTree(root, pokemons[i].power, i);
    }

    // ������� ��������� �� ���� � ������� �����������
    std::cout << "�������� �� ���� � ������� �����������:" << std::endl;
    printPokemonsByPower(pokemons, size, root);

    // ���� �������� �� ����
    int searchPower;
    std::cout << "������� ���� �������� ��� ������: ";
    std::cin >> searchPower;
    PowerNode* foundNode = searchPowerTree(root, searchPower);
    if (foundNode != nullptr) {
        std::cout << "������ �������:" << std::endl;
        std::cout << "���: " << pokemons[foundNode->index].name << ", ����: " << pokemons[foundNode->index].power << ", �������: " << pokemons[foundNode->index].level << ", ID: " << pokemons[foundNode->index].id << std::endl;
    }
    else {
        std::cout << "������� � ����� ����� �� ������." << std::endl;
    }

    // ����������� �������� �� ����
    int editPower;
    std::cout << "������� ���� �������� ��� ��������������: ";
    std::cin >> editPower;
    foundNode = searchPowerTree(root, editPower);
    if (foundNode != nullptr) {
        std::cout << "������� ������ ��������:" << std::endl;
        std::cout << "���: " << pokemons[foundNode->index].name << ", ����: " << pokemons[foundNode->index].power << ", �������: " << pokemons[foundNode->index].level << ", ID: " << pokemons[foundNode->index].id << std::endl;

        std::string newName;
        int newPower;
        int newLevel;
        int newId;
        std::cout << "������� ����� ������ ��������:" << std::endl;
        std::cout << "���: ";
        std::cin >> newName;
        std::cout << "����: ";
        std::cin >> newPower;
        std::cout << "�������: ";
        std::cin >> newLevel;
        std::cout << "ID: ";
        std::cin >> newId;

        pokemons[foundNode->index].name = newName;
        pokemons[foundNode->index].power = newPower;
        pokemons[foundNode->index].level = newLevel;
        pokemons[foundNode->index].id = newId;

        // ��������� ������
        root = insertPowerTree(root, newPower, foundNode->index);
        root = deletePowerNode(root, editPower);
    }
    else {
        std::cout << "������� � ����� ����� �� ������." << std::endl;
    }

    // ������� �������� �� ����
    int deletePower;
    std::cout << "������� ���� �������� ��� ��������: ";
    std::cin >> deletePower;
    foundNode = searchPowerTree(root, deletePower);
    if (foundNode != nullptr) {
        // ������� �� �������
        for (int i = foundNode->index; i < size - 1; ++i) {
            pokemons[i] = pokemons[i + 1];
        }
        --size;

        // ������� �� �������
        root = deletePowerNode(root, deletePower);
    }
    else {
        std::cout << "������� � ����� ����� �� ������." << std::endl;
    }
    std::cout << "�������� �� ���� � ������� �����������:" << std::endl;
    printPokemonsByPower(pokemons, size, root);
    return 0;
}