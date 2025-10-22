import java.util.ArrayList;
import java.util.List;

// Узел общего дерева
class TreeNode {
    public int value;                    // Значение узла
    public List<TreeNode> children;      // Список дочерних узлов
    
    // Конструктор
    public TreeNode(int value) {
        this.value = value;
        this.children = new ArrayList<>();
    }
    
    // Добавление дочернего узла
    public void addChild(TreeNode child) {
        children.add(child);
    }
    
    // Удаление дочернего узла
    public void removeChild(TreeNode child) {
        children.remove(child);
    }
    
    // Обход дерева в глубину
    public void traverse() {
        System.out.print(value + " ");
        for (TreeNode child : children) {
            child.traverse();
        }
    }
}

// Узел бинарного дерева
class BinaryTreeNode {
    public int value;                    // Значение узла
    public BinaryTreeNode left;          // Левый потомок
    public BinaryTreeNode right;         // Правый потомок
    public BinaryTreeNode parent;        // Родительский узел
    
    // Конструктор
    public BinaryTreeNode(int value) {
        this.value = value;
        this.left = null;
        this.right = null;
        this.parent = null;
    }
    
    // Вставка левого потомка
    public BinaryTreeNode insertLeft(int value) {
        left = new BinaryTreeNode(value);
        left.parent = this;
        return left;
    }
    
    // Вставка правого потомка
    public BinaryTreeNode insertRight(int value) {
        right = new BinaryTreeNode(value);
        right.parent = this;
        return right;
    }
    
    // Обход в порядке in-order (для бинарного дерева)
    public void inOrderTraversal() {
        if (left != null) {
            left.inOrderTraversal();
        }
        System.out.print(value + " ");
        if (right != null) {
            right.inOrderTraversal();
        }
    }
}