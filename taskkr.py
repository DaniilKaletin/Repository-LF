# ===== БЛОЧНАЯ СОРТИРОВКА (BUCKET SORT) =====
def bucket_sort(arr):
    """
    Блочная сортировка для равномерно распределенных чисел в диапазоне [0, 1)
    Сложность: O(n) в лучшем случае, O(n^2) в худшем
    """
    if len(arr) == 0:
        return arr

    # Создаем пустые корзины
    num_buckets = len(arr)
    buckets = [[] for _ in range(num_buckets)]

    # Распределяем элементы по корзинам
    for num in arr:
        bucket_index = int(num * num_buckets)
        buckets[bucket_index].append(num)

    # Сортируем каждую корзину и объединяем
    sorted_arr = []
    for bucket in buckets:
        sorted_arr.extend(sorted(bucket))  # Используем встроенную сортировку

    return sorted_arr

# ===== БЛИННАЯ СОРТИРОВКА (PANCAKE SORT) =====
def pancake_sort(arr):
    """
    Сортировка переворотами. Сложность: O(n^2)
    """
    def flip(subarray_end):
        """Переворачивает подмассив до указанного индекса"""
        start = 0
        while start < subarray_end:
            arr[start], arr[subarray_end] = arr[subarray_end], arr[start]
            start += 1
            subarray_end -= 1

    n = len(arr)
    for size in range(n, 1, -1):
        # Находим индекс максимального элемента в неотсортированной части
        max_idx = arr.index(max(arr[:size]))
        
        if max_idx != size - 1:
            # Перемещаем максимум в начало, если он не там
            if max_idx != 0:
                flip(max_idx)
            # Перемещаем максимум в конец неотсортированной части
            flip(size - 1)
    return arr

# ===== СОРТИРОВКА БУСИНАМИ (BEAD SORT) =====
def bead_sort(arr):
    """
    Гравитационная сортировка для неотрицательных целых чисел
    Сложность: O(S), где S - сумма элементов
    """
    if not arr or min(arr) < 0:
        raise ValueError("Только для неотрицательных целых чисел")

    # Создаем "абак" из бусин
    max_val = max(arr)
    beads = [[0] * max_val for _ in range(len(arr))]

    # Расставляем бусины
    for i, num in enumerate(arr):
        for j in range(num):
            beads[i][j] = 1

    # Симулируем "падение" бусин
    for j in range(max_val):
        sum_col = sum(beads[i][j] for i in range(len(arr)))
        for i in range(len(arr)):
            beads[i][j] = 1 if len(arr) - i <= sum_col else 0

    # Преобразуем обратно в числа
    return [sum(row) for row in beads]

# ===== ПОИСК СКАЧКАМИ (JUMP SEARCH) =====
def jump_search(arr, target):
    """
    Поиск в отсортированном массиве с прыжками. Сложность: O(√n)
    """
    n = len(arr)
    step = int(n ** 0.5)
    prev = 0

    # Прыжки до блока, где может быть элемент
    while prev < n and arr[min(step, n) - 1] < target:
        prev = step
        step += int(n ** 0.5)
        if prev >= n:
            return -1

    # Линейный поиск в блоке
    for i in range(prev, min(step, n)):
        if arr[i] == target:
            return i
    return -1

# ===== ЭКСПОНЕНЦИАЛЬНЫЙ ПОИСК (EXPONENTIAL SEARCH) =====
def exponential_search(arr, target):
    """
    Экспоненциальный поиск + бинарный. Сложность: O(log n)
    """
    if arr[0] == target:
        return 0

    n = len(arr)
    i = 1
    while i < n and arr[i] <= target:
        i *= 2

    # Бинарный поиск в найденном диапазоне
    left = i // 2
    right = min(i, n - 1)
    
    while left <= right:
        mid = (left + right) // 2
        if arr[mid] == target:
            return mid
        elif arr[mid] < target:
            left = mid + 1
        else:
            right = mid - 1
    return -1

# ===== ТЕРНАРНЫЙ ПОИСК (TERNARY SEARCH) =====
def ternary_search(arr, target):
    """
    Рекурсивный тернарный поиск. Сложность: O(log₃n)
    """
    def ternary_recursive(left, right):
        if left > right:
            return -1

        mid1 = left + (right - left) // 3
        mid2 = right - (right - left) // 3

        if arr[mid1] == target:
            return mid1
        if arr[mid2] == target:
            return mid2

        if target < arr[mid1]:
            return ternary_recursive(left, mid1 - 1)
        elif target > arr[mid2]:
            return ternary_recursive(mid2 + 1, right)
        else:
            return ternary_recursive(mid1 + 1, mid2 - 1)

    return ternary_recursive(0, len(arr) - 1)

# ===== ТЕСТИРОВАНИЕ =====
if __name__ == "__main__":
    print("Результаты работы алгоритмов:\n")

    # Тестовые данные
    test_bucket = [0.42, 0.32, 0.67, 0.89, 0.11, 0.22]
    test_sort = [64, 34, 25, 12, 22, 11, 90]
    test_bead = [4, 1, 6, 2, 3]
    test_search = [2, 5, 8, 12, 16, 23, 38, 45, 67, 73]
    
    print("Блочная сортировка:")
    print(f"Исходный: {test_bucket}")
    print(f"Результат: {bucket_sort(test_bucket.copy())}\n")

    print("Блинная сортировка:")
    print(f"Исходный: {test_sort}")
    print(f"Результат: {pancake_sort(test_sort.copy())}\n")

    print("Сортировка бусинами:")
    print(f"Исходный: {test_bead}")
    print(f"Результат: {bead_sort(test_bead.copy())}\n")

    print("Поиск скачками (элемент 23):")
    print(f"Массив: {test_search}")
    print(f"Индекс: {jump_search(test_search, 23)}\n")

    print("Экспоненциальный поиск (элемент 45):")
    print(f"Массив: {test_search}")
    print(f"Индекс: {exponential_search(test_search, 45)}\n")

    print("Тернарный поиск (элемент 16):")
    print(f"Массив: {test_search}")
    print(f"Индекс: {ternary_search(test_search, 16)}")