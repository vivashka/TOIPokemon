#include <iostream>

struct Pokemon {
    std::string name;
    int power;
    int level;
    int id;
};

struct Power {
    int power;
    int index;
};

struct Level {
    int level;
    int index;
};

// Функция для генерации случайного числа в заданном диапазоне
int Random(int start, int end) {
    int x = rand() % (end - start + 1) + start;
    return x;
}

// Процедура для рандомизированного ввода данных
void randomInputData(Pokemon pokemons[], int amount) {
    std::string Names[11]{ "Bulbasaur", "Raikachu", "Caterpie", "Pidgeot", "Meowth", "Rattata", "Clefairy", "Zubat", "Psyduck", "Abra", "Golem" };
    for (int i{ 0 }; i < amount; ++i) {
        pokemons[i] = Pokemon{ Names[Random(0, 10)], Random(1, 436), Random(4, 100), Random(1000, 9999) };
    }
}

// Процедура для сортировки массива индексов для силы методом пузырька
void bubblePowerSort(Power pokemons[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (pokemons[j].power < pokemons[j + 1].power) {
                Power temp = pokemons[j];
                pokemons[j] = pokemons[j + 1];
                pokemons[j + 1] = temp;
            }
        }
    }
}

// Процедура для сортировки массива индексов для уровня методом вставок
void insertionLevelSort(Level pokemons[], int n) {
    for (int i = 1; i < n; ++i) {
        Level key = pokemons[i];
        int j = i - 1;
        while (j >= 0 && pokemons[j].level < key.level) {
            pokemons[j + 1] = pokemons[j];
            --j;
        }
        pokemons[j + 1] = key;
    }
}

// Процедура для печати массива покемонов
void printArray(Pokemon pokemons[], int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << "Name: " << pokemons[i].name << ", Power: " << pokemons[i].power << ", Level: " << pokemons[i].level << ", ID: " << pokemons[i].id << std::endl;
    }
}

// Рекурсивная функция для поиска индекса в массиве индексов для силы
int recursivePowerSearch(Power pokemons[], int left, int right, int key) {
    if (right >= left) {
        int mid = left + (right - left) / 2;

        if (pokemons[mid].power == key)
            return mid;

        if (pokemons[mid].power > key)
            return recursivePowerSearch(pokemons, left, mid - 1, key);

        return recursivePowerSearch(pokemons, mid + 1, right, key);
    }

    return -1;
}

// Итеративная функция для поиска индекса в массиве индексов для уровня
int iterativeLevelSearch(Level pokemons[], int n, int key) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (pokemons[mid].level == key)
            return mid;

        if (pokemons[mid].level < key)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;  // Не нашлось
}

// Процедура для изменения записи по индексу в массиве покемонов и массиве индексов для силы
void editPowerRecord(Pokemon pokemons[], Power powerIndex[], int n, int recordIndex, int newPower) {
    pokemons[recordIndex].power = newPower;
    for (int i = 0; i < n; ++i) {
        if (powerIndex[i].index == recordIndex) {
            powerIndex[i].power = newPower;
            break;
        }
    }
}

// Процедура для изменения записи по индексу в массиве покемонов и массиве индексов для уровня
void LevelRecord(Pokemon pokemons[], Level levelIndex[], int n, int recordIndex, int newLevel) {
    pokemons[recordIndex].level = newLevel;
    for (int i = 0; i < n; ++i) {
        if (levelIndex[i].index == recordIndex) {
            levelIndex[i].level = newLevel;
            break;
        }
    }
}

// Процедура для удаления записи по ключу из массива покемонов и массива индексов для силы
void removeRecordByKey(Pokemon* pokemons, Power* powerIndex, int& size, int index) {
    for (int i = index; i < size - 1; ++i) {
        pokemons[i] = pokemons[i + 1];
        powerIndex[i] = powerIndex[i + 1];
    }
    --size;
}

// Процедура для удаления записи по ключу из массива покемонов и массива индексов для уровня
void deleteLevelRecord(Pokemon* pokemons, Level* levelIndex, int& size, int index) {
    for (int i = index; i < size - 1; ++i) {
        pokemons[i] = pokemons[i + 1];
        levelIndex[i] = levelIndex[i + 1];
    }
    --size;
}

int main() {
    //setlocale(LC_ALL, "Russian");
    int arraySize = 6; // Размер массива покемонов
    Pokemon* pokemons = new Pokemon[arraySize]; // Выделение памяти под массив покемонов
    randomInputData(pokemons, arraySize); // Заполнение массива случайными данными

    // Вывод массива индексов для силы
    std::cout << "----------------------Создание массива индексов для силы--------------------------------" << std::endl;
    Power* powerIndex = new Power[arraySize];
    for (int i = 0; i < arraySize; ++i) {
        powerIndex[i].power = pokemons[i].power;
        powerIndex[i].index = i;
        std::cout << "Name: " << pokemons[i].name << ", Power: " << pokemons[i].power <<
            ", Level: " << pokemons[i].level << ", ID: " << pokemons[i].id
            << ", Index: " << powerIndex[i].index << std::endl;
    }

    // Поиск индекса по значению силы (рекурсивный)
    std::cout << "Индекс:" << recursivePowerSearch(powerIndex, 0, arraySize, 290);

    // Вывод массива индексов для уровня
    std::cout << "\n------------------------Создание массива индексов для уровня------------------------------" << std::endl;
    Level* levelIndex = new Level[arraySize];
    for (int i = 0; i < arraySize; ++i) {
        levelIndex[i].level = pokemons[i].level;
        levelIndex[i].index = i;
        std::cout << "Name: " << pokemons[i].name << ", Power: " << pokemons[i].power <<
            ", Level: " << pokemons[i].level << ", ID: " << pokemons[i].id
            << ", Index: " << levelIndex[i].index << std::endl;
    }

    // Поиск индекса по значению уровня (итеративный)
    std::cout << "Индекс:" << iterativeLevelSearch(levelIndex, arraySize, 290);

    // Сортировка массива индексов для силы
    std::cout << "\n------------------------Сортировка массива для силы------------------------------" << std::endl;
    bubblePowerSort(powerIndex, arraySize);
    Pokemon* tempPokemons = new Pokemon[arraySize];
    for (int i = 0; i < arraySize; ++i) {
        tempPokemons[i] = pokemons[powerIndex[i].index];
    }
    
    // Замена исходного массива покемонов
    for (int i = 0; i < arraySize; ++i) {
        pokemons[i] = tempPokemons[i];
        powerIndex[i].index = i;
        levelIndex[i].index = i;
        levelIndex[i].level = pokemons[i].level;
        std::cout << "Name: " << pokemons[i].name << ", Power: " << pokemons[i].power <<
            ", Level: " << pokemons[i].level << ", ID: " << pokemons[i].id
            << ", Index: " << powerIndex[i].index << std::endl;
    }
    // Сортировка массива индексов для уровня
    std::cout << "-----------------------Сортировка массива индексов для уровня-------------------------------" << std::endl;
    insertionLevelSort(levelIndex, arraySize);
    for (int i = 0; i < arraySize; ++i) {
        tempPokemons[i] = pokemons[levelIndex[i].index];
    }
    for (int i = 0; i < arraySize; ++i) {
        pokemons[i] = tempPokemons[i];
        levelIndex[i].index = i;
        std::cout << "Name: " << pokemons[i].name << ", Power: " << pokemons[i].power <<
            ", Level: " << pokemons[i].level << ", ID: " << pokemons[i].id
            << ", Index: " << levelIndex[i].index << std::endl;
    }


    // Изменение значения силы и соответствующего индекса
    std::cout << "-----------------------Изменение массива индексов для силы-------------------------------" << std::endl;
    editPowerRecord(pokemons, powerIndex, arraySize, 4, 324);
    printArray(pokemons, arraySize);

    // Изменение значения уровня и соответствующего индекса
    std::cout << "-----------------------Изменение массива индексов для уровня-------------------------------" << std::endl;
    LevelRecord(pokemons, levelIndex, arraySize, 4, 10000);
    printArray(pokemons, arraySize);

    // Удаление записи по ключу из массива покемонов и массива индексов для силы
    std::cout << "-----------------------Удаление массива индексов для силы-------------------------------" << std::endl;
    removeRecordByKey(pokemons, powerIndex, arraySize, 0);
    printArray(pokemons, arraySize);

    // Удаление записи по ключу из массива покемонов и массива индексов для уровня
    std::cout << "-----------------------Удаление массива индексов для уровня-------------------------------" << std::endl;
    deleteLevelRecord(pokemons, levelIndex, arraySize, 2);
    printArray(pokemons, arraySize);

    // Освобождение памяти, выделенной для массивов покемонов и индексов
    delete[] pokemons;
    delete[] powerIndex;
    delete[] levelIndex;

    return 0;
}
