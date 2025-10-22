from collections import defaultdict, deque

# Представление графа через список смежности
class Graph:
    def __init__(self, directed=False):
        self.graph = defaultdict(list)  # Словарь для хранения списка смежности
        self.directed = directed        # Флаг ориентированности графа
        self.vertices = set()           # Множество вершин
    
    def add_vertex(self, vertex):
        # Добавление вершины в граф
        self.vertices.add(vertex)
    
    def add_edge(self, u, v, weight=1):
        # Добавление ребра между вершинами u и v
        self.graph[u].append((v, weight))
        self.vertices.add(u)
        self.vertices.add(v)
        
        # Если граф неориентированный, добавляем обратное ребро
        if not self.directed:
            self.graph[v].append((u, weight))
    
    def remove_edge(self, u, v):
        # Удаление ребра между вершинами u и v
        self.graph[u] = [node for node in self.graph[u] if node[0] != v]
        if not self.directed:
            self.graph[v] = [node for node in self.graph[v] if node[0] != u]
    
    def get_neighbors(self, vertex):
        # Получение списка соседей вершины
        return self.graph[vertex]
    
    def display(self):
        # Вывод структуры графа
        for vertex in self.graph:
            print(f"{vertex}: {self.graph[vertex]}")

# Представление графа через матрицу смежности
class GraphMatrix:
    def __init__(self, vertices):
        self.vertices = vertices        # Список вершин
        self.size = len(vertices)       # Количество вершин
        self.vertex_index = {v: i for i, v in enumerate(vertices)}  # Словарь индексов
        self.matrix = [[0] * self.size for _ in range(self.size)]  # Матрица смежности
    
    def add_edge(self, u, v, weight=1):
        # Добавление ребра между u и v
        i = self.vertex_index[u]
        j = self.vertex_index[v]
        self.matrix[i][j] = weight
    
    def remove_edge(self, u, v):
        # Удаление ребра между u и v
        i = self.vertex_index[u]
        j = self.vertex_index[v]
        self.matrix[i][j] = 0
    
    def is_adjacent(self, u, v):
        # Проверка смежности вершин
        i = self.vertex_index[u]
        j = self.vertex_index[v]
        return self.matrix[i][j] != 0
    
    def display(self):
        # Вывод матрицы смежности
        print("  " + " ".join(self.vertices))
        for i, row in enumerate(self.matrix):
            print(f"{self.vertices[i]} {' '.join(map(str, row))}")