//сортировка выбором на Java
public class SelectionSort {
    
    // Метод сортировки массива целых чисел методом выбора
    public static void selectionSort(int[] array) {
        
        int n = array.length;     // Получаем длину массива

        for (int i = 0; i < n - 1; i++) {      // Внешний цикл проходит по элементам массива
            int minIndex = i;                  // Предполагаемый индекс минимального элемента изначально равен текущему положению
            
            // Внутренний цикл ищет минимальный элемент среди оставшихся элементов справа
            for (int j = i + 1; j < n; j++) {
                if (array[j] < array[minIndex]) {   // Если найден меньший элемент, обновляем индекс минимального элемента
                    minIndex = j;
                }
            }
            
            // Меняем местами текущий элемент и найденный минимальный элемент
            swap(array, i, minIndex);
        }
    }

    // Вспомогательная функция для обмена двух элементов массива
    private static void swap(int[] arr, int a, int b) {
        int temp = arr[a];           // Сохраняем значение первого элемента временно
        arr[a] = arr[b];             // Первый элемент заменяется вторым элементом
        arr[b] = temp;               // Второй элемент заменяется первым сохранённым значением
    }

    // Основной метод для запуска программы
    public static void main(String[] args) {
        int[] numbers = {64, 25, 12, 22, 11};       // Исходный массив
        
        System.out.println("Исходный массив:");
        printArray(numbers);                        // Печать исходного массива перед сортировкой
        
        selectionSort(numbers);                     // Сортируем массив методом выборочной сортировки
        
        System.out.println("\nОтсортированный массив:");
        printArray(numbers);                        // Печать отсортированного массива
    }

    // Вспомогательный метод для печати содержимого массива
    private static void printArray(int[] arr) {
        for (int num : arr) {
            System.out.print(num + " ");
        }
        System.out.println();
    }
}




//Сортировка обменом (пузырьком) на Java
public class BubbleSortExample {

    // Реализация метода пузырьковой сортировки
    public static void bubbleSort(int[] array) {
        int n = array.length;                 // Длина массива
        boolean swapped;                      // Флаг для отслеживания факта обмена

        // Проходим по массиву столько раз, сколько элементов минус один
        for (int i = 0; i < n - 1; i++) {
            swapped = false;                  // Изначально считаем, что обменов не было
            
            // Каждый проход перемещается больший элемент ближе к концу массива
            for (int j = 0; j < n - i - 1; j++) {
                
                // Если текущий элемент больше следующего, меняем их местами
                if (array[j] > array[j + 1]) {
                    // Обмениваем два соседних элемента
                    int temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                    
                    swapped = true;           // Установили флаг, что произошел обмен
                }
            }
            
            // Если ни разу не произошло обменов, значит массив уже отсортирован
            if (!swapped) break;              // Выходим досрочно из основного цикла
        }
    }

    // Метод для вывода массива на экран
    public static void printArray(int[] array) {
        for (int value : array) {
            System.out.print(value + " ");    // Выводим значения массива
        }
        System.out.println();                  // Перевод строки
    }

    // Основная программа
    public static void main(String[] args) {
        int[] myArray = {64, 34, 25, 12, 22, 11, 90};
        
        System.out.println("Исходный массив:");
        printArray(myArray);                   // Выводим начальное состояние массива
        
        bubbleSort(myArray);                   // Применяем пузырьковую сортировку
        
        System.out.println("Отсортированный массив:");
        printArray(myArray);                   // Выводим конечное состояние массива
    }
}




//пирамидальная сортировка на Java
import java.util.Arrays;
class HeapSort {

    // Метод для преобразования двоичного дерева в кучу (heapify)
    public static void heapify(int[] arr, int n, int root) {
        int largest = root;          // Рассматриваемый узел (корень)
        int leftChild = 2 * root + 1;// Левый дочерний узел
        int rightChild = 2 * root + 2;// Правый дочерний узел

        // Если левый ребенок существует и больше корня
        if (leftChild < n && arr[leftChild] > arr[largest])
            largest = leftChild;

        // Если правый ребенок существует и больше самого большого узла
        if (rightChild < n && arr[rightChild] > arr[largest])
            largest = rightChild;

        // Если корень не самый большой, меняем местами и восстанавливаем структуру
        if (largest != root) {
            int temp = arr[root];
            arr[root] = arr[largest];
            arr[largest] = temp;

            // Рекурсивно применяем heapify к новому поддереву
            heapify(arr, n, largest);
        }
    }

    // Основная процедура сортировки кучей
    public static void heapSort(int[] arr) {
        int n = arr.length;

        // Строим max-кучу (перестраиваем дерево в бинарную кучу)
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(arr, n, i);

        // Один за другим извлекаем максимальный элемент из кучи
        for (int i = n - 1; i > 0; i--) {
            // Перемещение текущего корневого элемента в конец
            int temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;

            // Вызываем heapify на уменьшенной куче
            heapify(arr, i, 0);
        }
    }

    // Главный метод для тестирования
    public static void main(String[] args) {
        int[] arr = {12, 11, 13, 5, 6, 7};
        System.out.println("Исходный массив: " + Arrays.toString(arr));

        heapSort(arr); // Вызываем сортировку

        System.out.println("Отсортированный массив: " + Arrays.toString(arr));
    }
}


class HeapSort {

    // Метод для преобразования двоичного дерева в кучу (heapify)
    public static void heapify(int[] arr, int n, int root) {
        int largest = root;          // Рассматриваемый узел (корень)
        int leftChild = 2 * root + 1;// Левый дочерний узел
        int rightChild = 2 * root + 2;// Правый дочерний узел

        // Если левый ребенок существует и больше корня
        if (leftChild < n && arr[leftChild] > arr[largest])
            largest = leftChild;

        // Если правый ребенок существует и больше самого большого узла
        if (rightChild < n && arr[rightChild] > arr[largest])
            largest = rightChild;

        // Если корень не самый большой, меняем местами и восстанавливаем структуру
        if (largest != root) {
            int temp = arr[root];
            arr[root] = arr[largest];
            arr[largest] = temp;

            // Рекурсивно применяем heapify к новому поддереву
            heapify(arr, n, largest);
        }
    }

    // Основная процедура сортировки кучей
    public static void heapSort(int[] arr) {
        int n = arr.length;

        // Строим max-кучу (перестраиваем дерево в бинарную кучу)
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(arr, n, i);

        // Один за другим извлекаем максимальный элемент из кучи
        for (int i = n - 1; i > 0; i--) {
            // Перемещение текущего корневого элемента в конец
            int temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;

            // Вызываем heapify на уменьшенной куче
            heapify(arr, i, 0);
        }
    }

    // Главный метод для тестирования
    public static void main(String[] args) {
        int[] arr = {12, 11, 13, 5, 6, 7};
        System.out.println("Исходный массив: " + Arrays.toString(arr));

        heapSort(arr); // Вызываем сортировку

        System.out.println("Отсортированный массив: " + Arrays.toString(arr));
    }
}





//последовательный поиск на Java
public class LinearSearch {

    // Метод для выполнения линейного поиска
    public static int linearSearch(int[] arr, int target) {
        // Просматриваем каждый элемент массива по порядку
        for (int i = 0; i < arr.length; i++) {
            // Если текущий элемент совпадает с искомым значением
            if (arr[i] == target) {
                return i; // Возвращаем индекс найденного элемента
            }
        }
        return -1; // Если элемент не найден, возвращаем -1
    }

    // Тестовый метод для демонстрации работы поиска
    public static void main(String[] args) {
        int[] data = {3, 7, 1, 9, 5};
        int searchElement = 9;
        
        // Вызываем функцию поиска
        int result = linearSearch(data, searchElement);
        
        // Вывод результата
        if(result != -1) {
            System.out.println("Элемент найден на индексе: " + result);
        } else {
            System.out.println("Элемент не найден");
        }
    }
}


