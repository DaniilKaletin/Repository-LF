#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

// Структура для представления взвешенного ребра
struct Edge {
    int destination;
    int weight;
    
    Edge(int dest, int w = 1) : destination(dest), weight(w) {}
};

// Граф через список смежности
class Graph {
private:
    unordered_map<int, vector<Edge>> adjacencyList;  // Список смежности
    bool isDirected;                                 // Флаг ориентированности
    unordered_set<int> vertices;                     // Множество вершин

public:
    // Конструктор
    Graph(bool directed = false) : isDirected(directed) {}
    
    // Добавление вершины
    void addVertex(int vertex) {
        vertices.insert(vertex);
    }
    
    // Добавление ребра
    void addEdge(int u, int v, int weight = 1) {
        adjacencyList[u].push_back(Edge(v, weight));
        vertices.insert(u);
        vertices.insert(v);
        
        // Если граф неориентированный, добавляем обратное ребро
        if (!isDirected) {
            adjacencyList[v].push_back(Edge(u, weight));
        }
    }
    
    // Удаление ребра
    void removeEdge(int u, int v) {
        // Удаление ребра u -> v
        auto& neighbors = adjacencyList[u];
        for (auto it = neighbors.begin(); it != neighbors.end(); ) {
            if (it->destination == v) {
                it = neighbors.erase(it);
            } else {
                ++it;
            }
        }
        
        // Если граф неориентированный, удаляем обратное ребро
        if (!isDirected) {
            auto& reverseNeighbors = adjacencyList[v];
            for (auto it = reverseNeighbors.begin(); it != reverseNeighbors.end(); ) {
                if (it->destination == u) {
                    it = reverseNeighbors.erase(it);
                } else {
                    ++it;
                }
            }
        }
    }
    
    // Получение соседей вершины
    vector<Edge> getNeighbors(int vertex) {
        return adjacencyList[vertex];
    }
    
    // Вывод графа
    void display() {
        for (const auto& pair : adjacencyList) {
            cout << pair.first << ": ";
            for (const Edge& edge : pair.second) {
                cout << "(" << edge.destination << ", " << edge.weight << ") ";
            }
            cout << endl;
        }
    }
};

// Граф через матрицу смежности
class GraphMatrix {
private:
    vector<vector<int>> adjacencyMatrix;  // Матрица смежности
    unordered_map<int, int> vertexIndex;  // Соответствие вершина -> индекс
    vector<int> indexVertex;              // Соответствие индекс -> вершина

public:
    // Конструктор
    GraphMatrix(const vector<int>& vertices) {
        int size = vertices.size();
        adjacencyMatrix.resize(size, vector<int>(size, 0));
        indexVertex = vertices;
        
        for (int i = 0; i < size; i++) {
            vertexIndex[vertices[i]] = i;
        }
    }
    
    // Добавление ребра
    void addEdge(int u, int v, int weight = 1) {
        int i = vertexIndex[u];
        int j = vertexIndex[v];
        adjacencyMatrix[i][j] = weight;
    }
    
    // Удаление ребра
    void removeEdge(int u, int v) {
        int i = vertexIndex[u];
        int j = vertexIndex[v];
        adjacencyMatrix[i][j] = 0;
    }
    
    // Проверка смежности вершин
    bool isAdjacent(int u, int v) {
        int i = vertexIndex[u];
        int j = vertexIndex[v];
        return adjacencyMatrix[i][j] != 0;
    }
    
    // Вывод матрицы смежности
    void display() {
        cout << "  ";
        for (int v : indexVertex) {
            cout << v << " ";
        }
        cout << endl;
        
        for (int i = 0; i < adjacencyMatrix.size(); i++) {
            cout << indexVertex[i] << " ";
            for (int j = 0; j < adjacencyMatrix[i].size(); j++) {
                cout << adjacencyMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};