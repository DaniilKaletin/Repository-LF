// Реализация хеш-таблицы с использованием вручную на основе массива связанных списков: 
#include <iostream>
#include <list>
#include <functional>
        // Структура для хранения пары ключ-значение
        template<typename K, typename V>
struct HashNode {
K key;
V value;
HashNode(K k, V v) : key(k), value(v) {}
        };
        // Класс хеш-таблицы
        template<typename K, typename V>
class HashTable {
    private:
    std::list<HashNode<K, V>>* table;
    size_t capacity;
    size_t size;
    // Простая хеш-функция
    size_t hashFunction(const K& key) {
        return std::hash<K>()(key) % capacity;
    }
    public:
    HashTable(size_t cap = 10) : capacity(cap), size(0) {
        table = new std::list<HashNode<K, V>>[capacity];
    } 
    ~HashTable() {
        delete[] table;
    }
    // Вставка элемента 
    void insert(const K& key, const V& value) {
        size_t index = hashFunction(key);

        // Проверяем, существует ли уже такой ключ 
        for (auto& node : table[index]) {
            if (node.key == key) {
                node.value = value; // Обновляем значение 
                return;
            }
        }
        // Добавляем новую пару ключ-значение 
        table[index].push_back(HashNode<K, V>(key, value));
        size++;
    }
    // Поиск значения по ключу 
    V* find(const K& key) {
        size_t index = hashFunction(key);

        for (auto& node : table[index]) {
            if (node.key == key) {
                return &node.value;
            }
        }
        return nullptr;
    }
    // Удаление элемента 
    void remove(const K& key) {
        size_t index = hashFunction(key);

        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->key == key) {
                table[index].erase(it);
                size--;
                return;
            }
        }
    }
    // Получение размера таблицы 
    size_t getSize() const {
        return size;
    }
};
int main() {
    HashTable<std::string, int> hashTable;

    hashTable.insert("one", 1);
    hashTable.insert("two", 2);
    hashTable.insert("three", 3);
    std::cout << "Value for 'one': " << *(hashTable.find("one")) << std::endl;
    hashTable.remove("two");
    std::cout << "Size of hash table: " << hashTable.getSize() << std::endl;
    return 0;
}