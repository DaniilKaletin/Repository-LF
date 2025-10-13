#Создание мультисписков на языке python
matrix = []
rows = 3
cols = 4
for i in range(rows):
    matrix.append([0] * cols)

print(matrix)

#Создание очереди на языке python
import queue
q = queue.Queue()
q.put('элемент 1')
q.put('элемент 2')
print(q.get()) 
print(q.get()) 
print(q.empty())

#Реализация дека на языке python
from collections import deque 
tasks = deque() 
tasks.append("task1") 
tasks.append("task2") 
tasks.append("task3") 
while tasks: 
    current_task = tasks.popleft() 
    print(f"Выполняется: {current_task}")

#Создание приоритетной очереди на языке python (вариант 1)
from queue import PriorityQueue 
q = PriorityQueue() 
q.put((7, 'mid-priority item')) 
q.put((9, 'high-priority item')) 
q.put((2, 'low-priority item')) 
while not q.empty(): 
    item = q.get()
    print(item)
    
#Создание приоритетной очереди на языке python (вариант 2)
import heapq
priority_queue = []
heapq.heappush(priority_queue, (2, 'Задача B'))
heapq.heappush(priority_queue, (1, 'Задача A'))
heapq.heappush(priority_queue, (3, 'Задача C'))
print("Исходная очередь (список):", priority_queue)
while priority_queue:
    priority, task = heapq.heappop(priority_queue)
    print(f"Извлечена задача: {task} (приоритет: {priority})")


