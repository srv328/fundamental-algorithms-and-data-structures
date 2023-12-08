#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <thread>

struct FIO {
    std::string surname;
    std::string name;
    std::string patronymic;
};

struct Date {
    int number;
    int month;
    int year;
};

struct Flight_Number {
    std::string prefix;
    int digits;
};

struct Passenger {
    Flight_Number flight_number;
    FIO fio;
    Date date;
};

bool passengerEquals(const Passenger& p1, const Passenger& p2) {
    return p1.flight_number.prefix == p2.flight_number.prefix &&
        p1.flight_number.digits == p2.flight_number.digits &&
        p1.fio.surname == p2.fio.surname &&
        p1.fio.name == p2.fio.name &&
        p1.fio.patronymic == p2.fio.patronymic &&
        p1.date.number == p2.date.number &&
        p1.date.month == p2.date.month &&
        p1.date.year == p2.date.year;
}

class HashTable {
private:
    struct HashEntry {
        bool occupied;
        Passenger passenger;
        HashEntry() : occupied(false) {}
    };

    int initialSize; // Начальный размер таблицы
    int size; // Размер таблицы
    int count; // Количество элементов
    int k; // Параметр k для вторичной хеш-функции
    std::vector<HashEntry> table;

    // Хеш-функция для составного ключа (свёртка по 2)
    int hash(const std::string& key) {
        int hash = 0;
        for (int i = 0; i < key.size(); i += 2) {
            std::string substring = key.substr(i, 2);
            for (char c : substring) {
                hash += static_cast<int>(c);
            }
        }
        return hash % size;
    }

    // Вторичная хеш-функция с линейным пробированием
    int linearProbe(int index, int attempt, int step) {
        return (index + attempt * step) % size;
    }

    // Нахождение наименьшего общего делителя для проверки взаимнопростости значения К с размером таблицы
    int gcd(int a, int b) {
        if (b == 0) {
            return a;
        }
        return gcd(b, a % b);
    }

    // Разрешение коллизий с линейным пробированием
    int resolveCollision(int index, const std::string& key, const std::vector<HashEntry>& table) {
        int attempt = 1;
        int newIndex = linearProbe(index, attempt, k);

        while (table[newIndex].occupied && getKey(table[newIndex].passenger) != key) {
            attempt++;
            newIndex = linearProbe(index, attempt, k);
        }

        return newIndex;
    }

    //Для печати
    void printSeparatorLine() {
        int lineLength = 105; // Длина строки разделителя
        for (int i = 0; i < lineLength; i++) {
            std::cout << "-";
        }
        std::cout << std::endl;
    }

    // Перехеширование таблицы
    void resizeTable(int newSize) {
        this->size = newSize; // Update the size member variable
        std::vector<HashEntry> newTable(newSize);
        int newCount = 0;

        for (const auto& entry : table) {
            if (entry.occupied) {
                std::string key = getKey(entry.passenger);
                int index = hash(key);

                if (newTable[index].occupied) {
                    index = resolveCollision(index, key, newTable);
                }

                newTable[index].occupied = true;
                newTable[index].passenger = entry.passenger;
                newCount++;
            }
        }
        table = std::move(newTable); // Update the table with the resized table
        count = newCount;
    }

    // Ключ ФИО + номер рейса
    std::string getKey(Passenger passenger) {
        return passenger.fio.surname+ passenger.fio.name + passenger.fio.patronymic + std::to_string(passenger.flight_number.digits) + passenger.flight_number.prefix;
    }

    //Восстановление свойств ХТ
    void addAfterRemoval(int index) {
        int step = k;
        int newIndex = (index + step) % size;
        while (table[(newIndex + k) % size].occupied && hash(getKey(table[(newIndex + k) % size].passenger)) == hash(getKey(table[index].passenger))) {
            step += k;
            newIndex = (index + step) % size;
        }
        if (table[newIndex].occupied) {
            table[index] = table[newIndex];
            table[newIndex].occupied = false;
        }
    }

public:
    // Конструктор
    HashTable(int initialSize) : size(initialSize), count(0), k(0) {
        table.resize(size);
        this->initialSize = size;
    }

    //Установка значения К для линейного пробирования
    void setKValue(int newValue) {
        if (newValue <= 1) {
            std::cout << "Incorrect value of K. Try again!" << std::endl;
            std::exit(1);
        }
        else if (gcd(newValue, size) != 1) {
            std::cout << "K should be coprime with the table size. Try again!" << std::endl;
            std::exit(1);
        }
        else {
            k = newValue;
        }
    }

    // Деструктор
    ~HashTable() {
        table.clear();
    }

    //Очистка ХТ
    void clear() {
        for (int i = 0; i < size; i++) {
            table[i].occupied = false;
            table[i].passenger = Passenger();
        }
        count = 0;
        resizeTable(initialSize);
        std::cout << "Hash table cleared!" << std::endl;
    }

    // Добавление элемента
    void add(const std::string& prefix, int digits, const std::string& surname, const std::string& name, const std::string& patronymic,
        int number, int month, int year) {
        Passenger passenger{ {prefix, digits}, {surname,name,patronymic}, {number,month,year} };
        if (search(passenger.flight_number.prefix, passenger.flight_number.digits,
            passenger.fio.surname, passenger.fio.name, passenger.fio.patronymic)) {
            std::cout << "Element with the same key already exists. Cannot add!" << std::endl;
            return;
        }
        std::string key = getKey(passenger);
        int index = hash(key);

        if (!table[index].occupied) {
            table[index].occupied = true;
            table[index].passenger = passenger;
            count++;
        }
        else {
            int newIndex = resolveCollision(index, key, table);
            if (getKey(table[newIndex].passenger) == key) {
                std::cout << "Element with the same key already exists. Cannot add!" << std::endl;
                return;
            }
            table[newIndex].occupied = true;
            table[newIndex].passenger = passenger;
            count++;
        }
        if (count >= 0.75 * size) {
            resizeTable(2 * size);
        }
    }

    // Удаление элемента
    void remove(const std::string& prefix, int digits, const std::string& surname, const std::string& name, const std::string& patronymic,
        int number, int month, int year) {
        Passenger passenger{ {prefix, digits}, {surname, name, patronymic}, {number, month, year} };
        std::string key = getKey(passenger);
        int index = hash(key);
        bool flag = false;
        if (table[index].occupied && passengerEquals(table[index].passenger, passenger)) {
            table[index].occupied = false;
            count--;
            std::cout << "Passenger removed successfully!" << std::endl;
            flag = true;
            addAfterRemoval(index);
        }
        else {
            int newIndex = resolveCollision(index, key, table);
            if (table[newIndex].occupied && passengerEquals(table[newIndex].passenger, passenger)) {
                table[newIndex].occupied = false;
                count--;
                std::cout << "Passenger removed successfully!" << std::endl;
                flag = true;
                addAfterRemoval(newIndex);
            }
        }
        if (!flag) {
            std::cout << "Passenger not found!" << std::endl;
            return;
        }
        if (count <= 0.25 * size && size / 2 >= initialSize) {
            resizeTable(size / 2);
        }
    }

    //Поиск элемента
    bool search(const std::string& prefix, int digits, const std::string& surname, const std::string& name, const std::string& patronymic) {
        std::string key = surname + name + patronymic + std::to_string(digits) + prefix;
        int index = hash(key);
        
        if (getKey(table[index].passenger) == key) {
            return true;
        }

        int newIndex = resolveCollision(index, key, table);
        if (getKey(table[newIndex].passenger) == key) {
            return true;
        }

        return false;
    }

    //Печать ХТ
    void print() {
        std::cout << std::left; // Выравнивание по левому краю
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        std::cout << "Hash table: " << std::endl;
        // Заголовок таблицы
        std::cout << std::setw(6) << "Index";
        std::cout << std::setw(30) << "Key";
        std::cout << std::setw(50) << "Value";
        std::cout << std::setw(10) << "Status";
        std::cout << "Hash" << std::endl;
        printSeparatorLine();

        for (int i = 0; i < size; i++) {
            if (table[i].occupied) {
                std::string key = "[" + table[i].passenger.flight_number.prefix + std::to_string(table[i].passenger.flight_number.digits)
                    + " " + table[i].passenger.fio.surname + " " + table[i].passenger.fio.name + " " + table[i].passenger.fio.patronymic
                    + "]";
                std::string value = "[" + std::to_string(table[i].passenger.date.number) + "/" + std::to_string(table[i].passenger.date.month) + "/" + std::to_string(table[i].passenger.date.year) + "]";
                std::string status = "[1]";
                std::string hashValue = std::to_string(hash(key));

                std::cout << std::setw(6) << i;
                std::cout << std::setw(30) << key;
                std::cout << std::setw(50) << value;
                std::cout << std::setw(10) << status;
                std::cout << "Hash: " << hashValue << std::endl;
            }
            else {
                std::cout << std::setw(6) << i;
                std::cout << std::setw(30) << "N/A";
                std::cout << std::setw(50) << "N/A";
                std::cout << "[0]" << std::endl;
            }
        }
    }
};

int main() {
    HashTable hashTable(10);
    hashTable.setKValue(7);
    hashTable.add("CD", 1234, "Koshkin", "Meow", "Gavkov", 7, 7, 2023);
    hashTable.add("CD", 1243, "Koshkin", "Meow", "Gavkov", 7, 7, 2023);
    hashTable.add("CD", 1324, "Koshkin", "Meow", "Gavkov", 7, 7, 2023);
    hashTable.add("CD", 1342, "Koshkin", "Meow", "Gavkov", 7, 7, 2023);
    hashTable.add("DC", 4321, "Koshkin", "Meow", "Gavkov", 7, 7, 2023);
    hashTable.add("DC", 1234, "Koshkin", "Meow", "Gavkov", 7, 7, 2023);
    hashTable.add("DC", 4312, "Koshkin", "Meow", "Gavkov", 7, 7, 2023);
    hashTable.print();
    hashTable.add("DC", 1243, "Koshkin", "Meow", "Gavkov", 7, 7, 2023);
    std::cout << (hashTable.search("CD", 1243, "Koshkin", "Meow", "Gavkov") ? "Passenger found." : "Passenger not found.") << std::endl;
    std::cout << (hashTable.search("CD", 1243, "Koshkin", "Meow", "Gavkov") ? "Passenger found." : "Passenger not found.") << std::endl;
    std::cout << (hashTable.search("CD", 1324, "Koshkin", "Meow", "Gavkov") ? "Passenger found." : "Passenger not found.") << std::endl;
    std::cout << (hashTable.search("CD", 1342, "Koshkin", "Meow", "Gavkov") ? "Passenger found." : "Passenger not found.") << std::endl;
    std::cout << (hashTable.search("DC", 1234, "Koshkin", "Meow", "Gavkov") ? "Passenger found." : "Passenger not found.") << std::endl;
    hashTable.print();
    hashTable.remove("CD", 1243, "Koshkin", "Meow", "Gavkov", 7, 7, 2023);
    hashTable.print();
    hashTable.remove("DC", 1234, "Koshkin", "Meow", "Gavkov", 7, 7, 2023);
    hashTable.print();
    hashTable.remove("CD", 1324, "Koshkin", "Meow", "Gavkov", 7, 7, 2023);
    hashTable.print();
    hashTable.remove("DC", 4312, "Koshkin", "Meow", "Gavkov", 7, 7, 2023);
    hashTable.print();
    hashTable.remove("CD", 1342, "Koshkin", "Meow", "Gavkov", 7, 7, 2023);
    hashTable.print();
    hashTable.remove("CD", 1234, "Koshkin", "Meow", "Gavkov", 7, 7, 2023);
    hashTable.print();
    hashTable.remove("DC", 1243, "Koshkin", "Meow", "Gavkov", 7, 7, 2023);
    hashTable.print();
    hashTable.remove("DC", 4321, "Koshkin", "Meow", "Gavkov", 7, 7, 2023);
    hashTable.print();
    hashTable.clear();
    std::cout << (hashTable.search("CD", 1243, "Koshkin", "Meow", "Gavkov") ? "Passenger found." : "Passenger not found.") << std::endl;
    std::cout << (hashTable.search("CD", 1243, "Koshkin", "Meow", "Gavkov") ? "Passenger found." : "Passenger not found.") << std::endl;
    std::cout << (hashTable.search("CD", 1324, "Koshkin", "Meow", "Gavkov") ? "Passenger found." : "Passenger not found.") << std::endl;
    std::cout << (hashTable.search("CD", 1342, "Koshkin", "Meow", "Gavkov") ? "Passenger found." : "Passenger not found.") << std::endl;
    std::cout << (hashTable.search("DC", 1234, "Koshkin", "Meow", "Gavkov") ? "Passenger found." : "Passenger not found.") << std::endl;
    hashTable.print();
    hashTable.add("CD", 1234, "Koshkin", "Meow", "Gavkov", 7, 7, 2023);
    hashTable.add("CD", 1243, "Koshkin", "Meow", "Gavkov", 7, 7, 2023);
    hashTable.add("CD", 1324, "Koshkin", "Meow", "Gavkov", 7, 7, 2023);
    hashTable.add("CD", 1342, "Koshkin", "Meow", "Gavkov", 7, 7, 2023);
    hashTable.add("DC", 4321, "Koshkin", "Meow", "Gavkov", 7, 7, 2023);
    hashTable.add("DC", 1234, "Koshkin", "Meow", "Gavkov", 7, 7, 2023);
    hashTable.add("DC", 4312, "Koshkin", "Meow", "Gavkov", 7, 7, 2023);
    hashTable.print();
    hashTable.remove("CD", 1243, "Koshkin", "Meow", "Gavkov", 7, 7, 2023);
    hashTable.print();
    hashTable.remove("DC", 1234, "Koshkin", "Meow", "Gavkov", 7, 7, 2023);
    hashTable.print();
    hashTable.remove("CD", 1324, "Koshkin", "Meow", "Gavkov", 7, 7, 2023);
    hashTable.print();
    hashTable.remove("DC", 4312, "Koshkin", "Meow", "Gavkov", 7, 7, 2023);
    hashTable.print();
    hashTable.remove("CD", 1342, "Koshkin", "Meow", "Gavkov", 7, 7, 2023);
    hashTable.print();
    hashTable.remove("CD", 1234, "Koshkin", "Meow", "Gavkov", 7, 7, 2023);
    hashTable.print();
    hashTable.remove("DC", 1243, "Koshkin", "Meow", "Gavkov", 7, 7, 2023);
    hashTable.print();
    hashTable.remove("DC", 4321, "Koshkin", "Meow", "Gavkov", 7, 7, 2023);
    hashTable.print();
    hashTable.clear();
    return 0;
}
