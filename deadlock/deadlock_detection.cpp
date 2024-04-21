#include <iostream>
#include <vector>

using namespace std;

const int MAX_RESOURCES = 10; // Maximum number of resources

// Function to perform depth-first search (DFS) on the Resource Allocation Graph (RAG)
bool isCyclicUtil(const vector<vector<int>>& graph, vector<bool>& visited, vector<bool>& recStack, int v) {
    if (!visited[v]) {
        visited[v] = true;
        recStack[v] = true;

        for (int i = 0; i < graph.size(); ++i) {
            if (graph[v][i]) {
                if (!visited[i] && isCyclicUtil(graph, visited, recStack, i))
                    return true;
                else if (recStack[i])
                    return true;
            }
        }
    }
    recStack[v] = false; // Remove the vertex from recursion stack
    return false;
}

// Function to detect cycle in the Resource Allocation Graph (RAG)
bool isCyclic(const vector<vector<int>>& graph) {
    vector<bool> visited(MAX_RESOURCES, false);
    vector<bool> recStack(MAX_RESOURCES, false);

    for (int i = 0; i < graph.size(); ++i) {
        if (isCyclicUtil(graph, visited, recStack, i))
            return true;
    }
    return false;
}

int main() {
    // Sample Resource Allocation Graph (RAG)
    vector<vector<int>> resourceGraph = {
        {0, 1, 0, 0}, // P0 requests R1
        {0, 0, 1, 0}, // P1 requests R2
        {1, 0, 0, 1}, // P2 requests R0 and R3
        {0, 0, 0, 0}  // P3 requests no resources
    };

    // Check if the Resource Allocation Graph (RAG) contains a cycle (indicating deadlock)
    if (isCyclic(resourceGraph))
        cout << "Deadlock Detected!" << endl;
    else
        cout << "No Deadlock Detected." << endl;

    return 0;
}
