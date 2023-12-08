#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <cstring>
#include <thread>

class Graph {
private:
    int numVertices;
    std::vector<std::vector<bool>> adjacencyMatrix;

public:
    Graph(int numVertices) {
        this->numVertices = numVertices;
        adjacencyMatrix.resize(numVertices, std::vector<bool>(numVertices, false));
    }

    ~Graph() {}

    void addVertex() {
        numVertices++;
        adjacencyMatrix.resize(numVertices, std::vector<bool>(numVertices, false));
        for (int i = 0; i < numVertices - 1; i++) {
            adjacencyMatrix[i].resize(numVertices, false);
        }
    }

    void removeVertex(int vertex) {
        if (vertex >= 0 && vertex < numVertices) {
            numVertices--;
            adjacencyMatrix.erase(adjacencyMatrix.begin() + vertex);
            for (auto& row : adjacencyMatrix) {
                row.erase(row.begin() + vertex);
            }
        }
    }


    void addEdge(int from, int to) {
        if (from >= 0 && from < numVertices && to >= 0 && to < numVertices && from != to) {
            adjacencyMatrix[from][to] = true;
        }
        else {
            std::cout << "Error: Invalid edge." << std::endl;
        }
    }


    void removeEdge(int from, int to) {
        if (from >= 0 && from < numVertices && to >= 0 && to < numVertices) {
            if (adjacencyMatrix[from][to]) {
                adjacencyMatrix[from][to] = false;
            }
            else {
                std::cout << "Error: Edge does not exist." << std::endl;
            }
        }
        else {
            std::cout << "Error: Invalid vertex index." << std::endl;
        }
    }


    void print() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "Matrix: " << std::endl;
        std::cout << "   ";
        for (int i = 0; i < numVertices; i++) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
        for (int i = 0; i < numVertices; i++) {
            std::cout << i << "  ";
            for (int j = 0; j < numVertices; j++) {
                std::cout << adjacencyMatrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void depthFirstTraversal() {
        std::vector<bool> visited(numVertices, false);
        std::stack<int> stack;
        stack.push(0);

        while (!stack.empty()) {
            int vertex = stack.top();
            stack.pop();

            if (!visited[vertex]) {
                visited[vertex] = true;
                std::cout << "Visited vertex: " << vertex << std::endl;

                for (int i = 0; i < numVertices; i++) {
                    if (adjacencyMatrix[vertex][i] && !visited[i]) {
                        stack.push(i);
                    }
                }
            }
        }
    }

    void findConnectedComponents() {
        std::vector<bool> visited(numVertices, false);
        std::vector<std::vector<int>> components;

        for (int i = 0; i < numVertices; i++) {
            if (!visited[i]) {
                std::vector<int> component;
                std::stack<int> stack;
                stack.push(i);

                while (!stack.empty()) {
                    int vertex = stack.top();
                    stack.pop();

                    if (!visited[vertex]) {
                        visited[vertex] = true;
                        component.push_back(vertex);

                        for (int j = 0; j < numVertices; j++) {
                            if (adjacencyMatrix[vertex][j] && !visited[j]) {
                                stack.push(j);
                            }
                        }
                    }
                }

                if (!component.empty()) {
                    components.push_back(component);
                }
            }
        }

        // Изменение: Удаление пустых компонент связности
        components.erase(std::remove_if(components.begin(), components.end(), [](const std::vector<int>& component) {
            return component.empty();
            }), components.end());

        for (int i = 0; i < components.size(); i++) {
            std::cout << "Connected Component " << i + 1 << ": ";
            for (int j = 0; j < components[i].size(); j++) {
                std::cout << components[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }



    void saveToFile(const std::string& filename) {
        std::ofstream file(filename);
        if (file.is_open()) {
            file << numVertices << std::endl;
            for (int i = 0; i < numVertices; i++) {
                for (int j = 0; j < numVertices; j++) {
                    file << adjacencyMatrix[i][j] << " ";
                }
                file << std::endl;
            }
            file.close();
            std::cout << "Graph saved to " << filename << std::endl;
        }
        else {
            std::cout << "Error saving graph to file." << std::endl;
        }
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            int vertices;
            file >> vertices;
            if (vertices >= 5 && vertices <= 100) {
                numVertices = vertices;
                adjacencyMatrix.resize(numVertices, std::vector<bool>(numVertices, false));

                for (int i = 0; i < numVertices; i++) {
                    for (int j = 0; j < numVertices; j++) {
                        int value;
                        file >> value;
                        adjacencyMatrix[i][j] = value == 1;
                    }
                }

                std::cout << "Graph loaded from " << filename << std::endl;
            }
            else {
                std::cout << "Invalid number of vertices in the file." << std::endl;
                std::exit(1);
            }
            file.close();
        }
        else {
            std::cout << "Error loading graph from file." << std::endl;
            std::exit(1);
        }
    }
};

int main() {
    Graph graph(5);
    graph.loadFromFile("graph.txt");
    graph.print();
    graph.addVertex();
    graph.print();
    graph.removeEdge(4, 1);
    graph.addEdge(1, 1);
    graph.print();
    std::cout << "--------" << std::endl;
    graph.depthFirstTraversal();
    std::cout << "--------" << std::endl;
    graph.findConnectedComponents();

    //graph.saveToFile("graph.txt");
    return 0;
}
