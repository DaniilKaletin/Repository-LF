#include <iostream>
#include <list>

using namespace std;

int main() {
    // Создадим пустой список STACK
    list<char> stack;
    
    // Заполним список символами
    stack.push_back('5');
    stack.push_back('1');
    stack.push_back('9');
    stack.push_back('7');
    stack.push_back('6');
    stack.push_back('0');
    stack.push_back('1');
    stack.push_back('$');
    stack.push_back('#');
    
    // Выводим список STACK
    cout << "Список символов: ";
    for (char c : stack) {
        cout << c << " ";
    }
    cout << endl;
    
    return 0;
}