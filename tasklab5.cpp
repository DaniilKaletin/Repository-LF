//сортировка слиянием на C++
#include <iostream>
using namespace std;

// Процедура объединения двух отсортированных частей массива
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;       // Размер левой половины
    int n2 = right - mid;          // Размер правой половины
    
    // Создаем временные массивы для левой и правой половинок
    int L[n1], R[n2];
    
    // Копируем данные в временные массивы
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    // Индексы для временной левой и правой половинки
    int i = 0;                     
    int j = 0;                     
    int k = left;                  // Начальная позиция для объединения
    
    // Объединение временных массивов обратно в оригинальный массив
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {        // Если элемент левого массива меньше или равен правому
            arr[k++] = L[i++];     // Кладём элемент из левого массива
        } else {
            arr[k++] = R[j++];     // Иначе кладём элемент из правого массива
        }
    }
    
    // Остаточные элементы из левой половины
    while (i < n1) {
        arr[k++] = L[i++];
    }
    
    // Остаточные элементы из правой половины
    while (j < n2) {
        arr[k++] = R[j++];
    }
}

// Рекурсивная процедура разделения массива на две части и последующей сортировки
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;   // Нахождение середины массива
        
        // Рекурсивно сортируем левую половину
        mergeSort(arr, left, mid);
        
        // Рекурсивно сортируем правую половину
        mergeSort(arr, mid + 1, right);
        
        // Объединяем обе отсортированные половины
        merge(arr, left, mid, right);
    }
}

// Основная программа
int main() {
    int arr[] = {38, 27, 43, 3, 9, 82, 10};  // Наш тестовый массив
    int size = sizeof(arr)/sizeof(arr[0]);    // Определяем размер массива
    
    cout << "Исходный массив:\n";
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
    
    // Вызываем процедуру сортировки
    mergeSort(arr, 0, size - 1);
    
    cout << "\nОтсортированный массив:\n";
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
    
    return 0;
}




//быстрая сортировка на C++
#include <iostream>
using namespace std;

// Функция для обмена двух элементов в массиве
void swap(int& a, int& b) {
    int temp = a;   // Сохраняем первое значение во временную переменную
    a = b;          // Первое значение присваиваем второму
    b = temp;       // Второе значение присваиваем первому
}

// Процедура разделения массива (Partition)
int partition(int arr[], int low, int high) {
    int pivot = arr[high];   // Последний элемент массива выбран в качестве опорного (pivot)
    int i = low - 1;         // Указатель на границу меньшей секции

    // Основной цикл: перебор всех элементов кроме последнего (pivota)
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {  // Если текущий элемент меньше pivota
            i++;              // Увеличить границу меньшей секции
            swap(arr[i], arr[j]);  // Поменять местами текущий элемент с границей
        }
    }

    // Поместить pivot на своё место
    swap(arr[i + 1], arr[high]);
    return i + 1;             // Возвращаем индекс позиции pivot'a
}

// Главная рекурсивная функция быстрой сортировки
void quickSort(int arr[], int low, int high) {
    if (low < high) {                 // Базовый случай: если индексы пересеклись, выход
        int pi = partition(arr, low, high);  // Найти индекс опоры (partition index)
        
        // Рекурсивно сортировать левую часть
        quickSort(arr, low, pi - 1);
        
        // Рекурсивно сортировать правую часть
        quickSort(arr, pi + 1, high);
    }
}

// Вспомогательная функция для вывода массива
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// Основная программа
int main() {
    int arr[] = {10, 7, 8, 9, 1, 5};  // Исходный массив
    int n = sizeof(arr) / sizeof(arr[0]);  // Определение размера массива
    
    cout << "Исходный массив: ";
    printArray(arr, n);  // Выводим исходный массив
    
    quickSort(arr, 0, n - 1);  // Вызываем процедуру быстрой сортировки
    
    cout << "Отсортированный массив: ";
    printArray(arr, n);  // Выводим отсортированный массив
    
    return 0;
}



//интерполирующий поиск на C++
#include <iostream>
using namespace std;

// Интерполирующий поиск в отсортированном массиве
int interpolationSearch(int arr[], int n, int x) {
    int low = 0;              // Нижний индекс
    int high = n - 1;         // Верхний индекс

    // Пока нижний индекс меньше верхнего и искомое значение лежит в пределах крайних элементов
    while ((low <= high) && (x >= arr[low]) && (x <= arr[high])) {
        // Если массив содержит одинаковые элементы, проверить крайние индексы
        if (arr[low] == arr[high]) {
            if (arr[low] == x) return low;
            return -1;
        }

        // Формула интерполяционного поиска
        int pos = low + (((double)(high - low) /
                         (arr[high] - arr[low])) *
                        (x - arr[low]));

        // Проверка трех возможных случаев
        if (arr[pos] == x) {   // Значение найдено
            return pos;
        }
        if (arr[pos] < x) {    // Значение больше, смещаемся вправо
            low = pos + 1;
        } else {               // Значение меньше, смещаемся влево
            high = pos - 1;
        }
    }

    return -1;                // Если элемент не найден
}

// Основная программа
int main() {
    int sortedArr[] = {10, 12, 13, 16, 18, 19, 20, 21, 22, 23, 24, 33, 35, 42, 47};
    int n = sizeof(sortedArr) / sizeof(sortedArr[0]);
    int elementToFind = 18;

    int index = interpolationSearch(sortedArr, n, elementToFind);

    if (index != -1) {
        cout << "Элемент " << elementToFind << " найден на индексе " << index << "." << endl;
    } else {
        cout << "Элемент " << elementToFind << " не найден." << endl;
    }

    return 0;
}
