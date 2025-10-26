#сортировка вставками на Python
def insertion_sort(arr):
    # Цикл начинается со второго элемента (индекс 1)
    for i in range(1, len(arr)):
        key = arr[i]                       # Берём текущий элемент
        j = i - 1                          # Запоминаем индекс предыдущего элемента
        
        # Пока предыдущий элемент больше текущего и мы ещё не дошли до начала списка
        while j >= 0 and arr[j] > key:
            arr[j + 1] = arr[j]           # Перемещаем больший элемент вправо
            j -= 1                         # Переходим к следующему элементу слева
        
        # Вставляем текущий элемент на правильную позицию
        arr[j + 1] = key


# Тестируем нашу функцию
arr = [12, 11, 13, 5, 6]
print("Исходный массив:", arr)

insertion_sort(arr)                        # Вызываем функцию сортировки

print("Отсортированный массив:", arr)




#сортировка Шелла
def shell_sort(arr):
    gap = len(arr) // 2  # Устанавливаем начальный промежуток (gap)
    
    # Продолжаем уменьшать gap, пока он не достигнет нуля
    while gap > 0:
        # Проходим по всему массиву с установленным промежутком
        for i in range(gap, len(arr)):  
            current_value = arr[i]  # Текущий элемент
            position = i            # Его текущая позиция
            
            # Сравниваем текущий элемент с элементами, расположенными на расстоянии gap
            while position >= gap and arr[position-gap] > current_value:
                # Если предшествующий элемент больше, сдвигаем его вперед
                arr[position] = arr[position-gap]
                position -= gap  # Передвигаемся назад на gap позиций
            
            # Когда нашли правильное место, ставим текущий элемент на свою позицию
            arr[position] = current_value
        
        # Уменьшаем gap вдвое для следующей итерации
        gap //= 2

# Пример использования
arr = [64, 34, 25, 12, 22, 11, 90]
shell_sort(arr)
print("Отсортированный массив:", arr)


#бинарный поиск на Python
def binary_search(arr, x):
    """
    Бинарный поиск числа x в отсортированном массиве arr.
    Возвращает индекс числа, если оно найдено, иначе -1.
    """
    low = 0                     # Нижняя граница диапазона поиска
    high = len(arr) - 1         # Верхняя граница диапазона поиска
    
    while low <= high:          # Пока границы не пересеклись
        mid = (low + high) // 2 # Вычисляем средний индекс
        
        # Проверяем, какой участок продолжать искать
        if arr[mid] < x:        # Если средний элемент меньше искомого
            low = mid + 1       # Искать в правом диапазоне
        elif arr[mid] > x:      # Если средний элемент больше искомого
            high = mid - 1      # Искать в левом диапазоне
        else:                   # Средний элемент равен искомому
            return mid          # Возвратим индекс среднего элемента
    
    return -1                   # Если элемент не найден, вернуть -1

# Пример использования
sorted_array = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29]
search_element = 11

result = binary_search(sorted_array, search_element)

if result != -1:
    print(f"Элемент {search_element} найден на индексе {result}.")
else:
    print(f"Элемент {search_element} не найден.")



#поиск Фибоначчи на Python
def fibonacci_search(arr, x):
    """Алгоритм поиска Фибоначчи"""
    # Первые числа ряда Фибоначчи
    fib_m_minus_2 = 0  # F(m-2)
    fib_m_minus_1 = 1  # F(m-1)
    fib_M = fib_m_minus_1 + fib_m_minus_2  # F(m)

    # Ищем минимальное число Фибоначчи, большее или равное длине массива
    while fib_M < len(arr):
        fib_m_minus_2 = fib_m_minus_1
        fib_m_minus_1 = fib_M
        fib_M = fib_m_minus_1 + fib_m_minus_2

    offset = -1  # смещение, показывающее начало отрезка поиска

    # Повторяем, пока отрезок поиска не станет пустым
    while fib_M > 1:
        # Определяем индекс для проверки
        i = min(offset + fib_m_minus_2, len(arr)-1)

        # Три возможных сценария:
        if arr[i] < x:  # Если искомое больше, сужаем область поиска вправо
            fib_M = fib_m_minus_1
            fib_m_minus_1 = fib_m_minus_2
            fib_m_minus_2 = fib_M - fib_m_minus_1
            offset = i
        elif arr[i] > x:  # Если искомое меньше, сужаем область поиска влево
            fib_M = fib_m_minus_2
            fib_m_minus_1 = fib_m_minus_1 - fib_m_minus_2
            fib_m_minus_2 = fib_M - fib_m_minus_1
        else:  # Совпадение, элемент найден
            return i

    # Если остался единственный элемент для проверки
    if fib_m_minus_1 and arr[offset+1] == x:
        return offset + 1

    # Если ничего не найдено
    return -1

# Тестируем функцию
data = [10, 22, 35, 40, 45, 50, 80, 82, 85, 90, 100]
element_to_find = 85

index = fibonacci_search(data, element_to_find)

if index != -1:
    print(f"Элемент {element_to_find} найден на индексе {index}")
else:
    print(f"Элемент {element_to_find} не найден")