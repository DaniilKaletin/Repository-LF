#include <iostream>
#include <deque> // Подключаем заголовочный файл для std::deque

int main() {
    // 1. Создание дека
    std::deque<int> myDeque; // Дек для хранения целых чисел

    // 2. Добавление элементов
    myDeque.push_back(10);   // Добавить в конец
    myDeque.push_front(5);   // Добавить в начало
    myDeque.push_back(20);   // Добавить в конец
    myDeque.push_front(2);   // Добавить в начало

    // Дек теперь содержит: [2, 5, 10, 20]

    // 3. Доступ к элементам
    std::cout << "Первый элемент: " << myDeque.front() << std::endl; // 2
    std::cout << "Последний элемент: " << myDeque.back() << std::endl; // 20
    std::cout << "Элемент по индексу 1: " << myDeque[1] << std::endl; // 5 [6]

    // 4. Итерация по деку
    std::cout << "Все элементы: ";
    for (auto const& element : myDeque) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
    // Вывод: 2 5 10 20

    // 5. Удаление элементов
    myDeque.pop_back();  // Удалить последний элемент
    myDeque.pop_front(); // Удалить первый элемент

    // Дек теперь содержит: [5, 10]

    return 0;
}
