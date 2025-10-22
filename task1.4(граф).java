import java.util.*;

// Класс для представления взвешенного ребра
class Edge {
    public int destination;
    public int weight;
    
    public Edge(int destination, int weight) {
        this.destination = destination;
        this.weight = weight;
    }
    
    @Override
    public String toString() {
        return "(" + destination + ", " + weight + ")";
    }
}

// Граф через список смежности
class Graph {
    private Map<Integer, List<Edge>> adjacencyList;  // Список смежности
    private boolean isDirected;                      // Флаг ориентированности
    private Set<Integer> vertices;                   // Множество вершин
    
    // Конструктор
    public Graph(boolean directed) {
        this.adjacencyList = new HashMap<>();
        this.isDirected = directed;
        this.vertices = new HashSet<>();
    }
    
    // Добавление вершины
    public void addVertex(int vertex) {
        vertices.add(vertex);
        adjacencyList.putIfAbsent(vertex, new ArrayList<>());
    }
    
    // Добавление ребра
    public void addEdge(int u, int v, int weight) {
        addVertex(u);
        addVertex(v);
        
        adjacencyList.get(u).add(new Edge(v, weight));
        
        // Если граф неориентированный, добавляем обратное ребро
        if (!isDirected) {
            adjacencyList.get(v).add(new Edge(u, weight));
        }
    }
    
    // Перегруженный метод для ребра веса 1
    public void addEdge(int u, int v) {
        addEdge(u, v, 1);
    }
    
    // Удаление ребра
    public void removeEdge(int u, int v) {
        List<Edge> edgesU = adjacencyList.get(u);
        if (edgesU != null) {
            edgesU.removeIf(edge -> edge.destination == v);
        }
        
        // Если граф неориентированный, удаляем обратное ребро
        if (!isDirected) {
            List<Edge> edgesV = adjacencyList.get(v);
            if (edgesV != null) {
                edgesV.removeIf(edge -> edge.destination == u);
            }
        }
    }
    
    // Получение соседей вершины
    public List<Edge> getNeighbors(int vertex) {
        return adjacencyList.getOrDefault(vertex, new ArrayList<>());
    }
    
    // Получение всех вершин
    public Set<Integer> getVertices() {
        return vertices;
    }
    
    // Вывод графа
    public void display() {
        for (Map.Entry<Integer, List<Edge>> entry : adjacencyList.entrySet()) {
            System.out.print(entry.getKey() + ": ");
            for (Edge edge : entry.getValue()) {
                System.out.print(edge + " ");
            }
            System.out.println();
        }
    }
}

// Граф через матрицу смежности
class GraphMatrix {
    private int[][] adjacencyMatrix;  // Матрица смежности
    private Map<Integer, Integer> vertexIndex;  // Соответствие вершина -> индекс
    private List<Integer> indexVertex;          // Соответствие индекс -> вершина
    
    // Конструктор
    public GraphMatrix(List<Integer> vertices) {
        int size = vertices.size();
        this.adjacencyMatrix = new int[size][size];
        this.vertexIndex = new HashMap<>();
        this.indexVertex = new ArrayList<>(vertices);
        
        for (int i = 0; i < size; i++) {
            vertexIndex.put(vertices.get(i), i);
        }
    }
    
    // Добавление ребра
    public void addEdge(int u, int v, int weight) {
        int i = vertexIndex.get(u);
        int j = vertexIndex.get(v);
        adjacencyMatrix[i][j] = weight;
    }
    
    // Удаление ребра
    public void removeEdge(int u, int v) {
        int i = vertexIndex.get(u);
        int j = vertexIndex.get(v);
        adjacencyMatrix[i][j] = 0;
    }
    
    // Проверка смежности вершин
    public boolean isAdjacent(int u, int v) {
        int i = vertexIndex.get(u);
        int j = vertexIndex.get(v);
        return adjacencyMatrix[i][j] != 0;
    }
    
    // Вывод матрицы смежности
    public void display() {
        System.out.print("  ");
        for (int vertex : indexVertex) {
            System.out.print(vertex + " ");
        }
        System.out.println();
        
        for (int i = 0; i < adjacencyMatrix.length; i++) {
            System.out.print(indexVertex.get(i) + " ");
            for (int j = 0; j < adjacencyMatrix[i].length; j++) {
                System.out.print(adjacencyMatrix[i][j] + " ");
            }
            System.out.println();
        }
    }
}