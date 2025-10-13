#include <iostream>
#include <set> // Подключение заголовочного файла
#include <algorithm> // Для std::for_each

int main() {
    // Объявление мультисписка для хранения целых чисел
    std::multiset<int> myMultiset;

    // Вставка элементов (дубликаты разрешены)
    myMultiset.insert(10);
    myMultiset.insert(20);
    myMultiset.insert(10);
    myMultiset.insert(30);
    myMultiset.insert(20);

    // Вывод элементов (они будут отсортированы)
    std::cout << "Элементы мультисписка:" << std::endl;
    for (int val : myMultiset) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Пример удаления одного элемента
    // Удаляет одно вхождение значения 10
    myMultiset.erase(10);

    std::cout << "Элементы после удаления одного 10:" << std::endl;
    for (int val : myMultiset) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}
