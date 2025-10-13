#include <iostream>
#include <queue> // Включаем заголовочный файл для std::queue

int main() {
    // Создаем очередь для хранения целых чисел
    std::queue<int> myQueue;

    // Добавляем элементы в очередь
    myQueue.push(10);
    myQueue.push(20);
    myQueue.push(30);

    // Выводим элементы из очереди
    std::cout << "Элементы очереди: ";
    while (!myQueue.empty()) {
        std::cout << myQueue.front() << " "; // Получаем первый элемент
        myQueue.pop(); // Удаляем первый элемент
    }
    std::cout << std::endl; // Вывод: Элементы очереди: 10 20 30

    return 0;
}
