#include <iostream>
#include <queue> // Подключение заголовочного файла priority_queue

int main() {
    // Объявление приоритетной очереди для целых чисел
    std::priority_queue<int> pq;

    // Добавление элементов в очередь
    pq.push(30);
    pq.push(100);
    pq.push(25);
    pq.push(40);

    // Вывод элементов в порядке убывания (наибольший первым)
    std::cout << "Элементы приоритетной очереди (по убыванию):" << std::endl;
    while (!pq.empty()) {
        std::cout << pq.top() << " "; // Получаем верхний элемент
        pq.pop();                     // Удаляем верхний элемент
    }
    std::cout << std::endl;

    return 0;
}
