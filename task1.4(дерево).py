class TreeNode:
    def __init__(self, value):
        self.value = value      # Значение узла
        self.children = []      # Список дочерних узлов
    
    def add_child(self, child_node):
        # Добавление дочернего узла
        self.children.append(child_node)
    
    def remove_child(self, child_node):
        # Удаление дочернего узла
        self.children = [child for child in self.children if child != child_node]
    
    def traverse(self):
        # Обход дерева в глубину
        nodes = [self]
        while nodes:
            current_node = nodes.pop()
            print(current_node.value)
            nodes.extend(current_node.children[::-1])

# Бинарное дерево
class BinaryTreeNode:
    def __init__(self, value):
        self.value = value      # Значение узла
        self.left = None        # Левый потомок
        self.right = None       # Правый потомок
        self.parent = None      # Родительский узел (опционально)
    
    def insert_left(self, value):
        # Вставка левого потомка
        self.left = BinaryTreeNode(value)
        self.left.parent = self
        return self.left
    
    def insert_right(self, value):
        # Вставка правого потомка
        self.right = BinaryTreeNode(value)
        self.right.parent = self
        return self.right