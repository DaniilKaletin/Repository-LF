#include <vector>
#include <iostream>
using namespace std;

// Узел общего дерева
class TreeNode {
public:
    int value;                      // Значение узла
    vector<TreeNode*> children;     // Вектор дочерних узлов
    
    // Конструктор
    TreeNode(int val) : value(val) {}
    
    // Добавление дочернего узла
    void addChild(TreeNode* child) {
        children.push_back(child);
    }
    
    // Удаление дочернего узла
    void removeChild(TreeNode* child) {
        for (auto it = children.begin(); it != children.end(); ++it) {
            if (*it == child) {
                children.erase(it);
                break;
            }
        }
    }
    
    // Обход дерева в глубину
    void traverse() {
        cout << value << " ";
        for (TreeNode* child : children) {
            child->traverse();
        }
    }
};

// Узел бинарного дерева
class BinaryTreeNode {
public:
    int value;                      // Значение узла
    BinaryTreeNode* left;           // Левый потомок
    BinaryTreeNode* right;          // Правый потомок
    BinaryTreeNode* parent;         // Родительский узел
    
    // Конструктор
    BinaryTreeNode(int val) : value(val), left(nullptr), right(nullptr), parent(nullptr) {}
    
    // Вставка левого потомка
    BinaryTreeNode* insertLeft(int val) {
        left = new BinaryTreeNode(val);
        left->parent = this;
        return left;
    }
    
    // Вставка правого потомка
    BinaryTreeNode* insertRight(int val) {
        right = new BinaryTreeNode(val);
        right->parent = this;
        return right;
    }
    
    // Деструктор (для очистки памяти)
    ~BinaryTreeNode() {
        delete left;
        delete right;
    }
};