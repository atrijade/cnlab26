#include <iostream>
#include <limits.h> // For INT_MAX
using namespace std;

class Dijkstra {
    int n, cost[10][10], distance[10], parent[10], visited[10];

public:
    void readMatrix();
    void findShortestPath(int src);
    void display(int src);
};

void Dijkstra::readMatrix() {
    cout << "Enter the number of vertices: ";
    cin >> n;

    cout << "Enter the cost adjacency matrix (Enter 999 for no direct path):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> cost[i][j];
}

void Dijkstra::findShortestPath(int src) {
    for (int i = 0; i < n; i++) {
        distance[i] = cost[src][i]; // Initialize distances
        parent[i] = src;  // Initially, parent of all nodes is the source
        visited[i] = 0;
    }
    visited[src] = 1; // Mark source as visited

    for (int i = 1; i < n; i++) {
        int min = 999, u = -1;

        // Find the nearest unvisited vertex
        for (int j = 0; j < n; j++) {
            if (!visited[j] && distance[j] < min) {
                min = distance[j];
                u = j;
            }
        }

        if (u == -1) break; // No more reachable nodes
        visited[u] = 1;

        // Update distances
        for (int v = 0; v < n; v++) {
            if (!visited[v] && cost[u][v] != 999 && (distance[u] + cost[u][v] < distance[v])) {
                distance[v] = distance[u] + cost[u][v];
                parent[v] = u;
            }
        }
    }
}

void Dijkstra::display(int src) {
    cout << "\nShortest Paths from Source " << src << ":\n";
    for (int i = 0; i < n; i++) {
        if (i == src) continue;
        cout << "To " << i << " - Distance: " << distance[i] << " | Path: " << i;

        int j = i;
        while (parent[j] != src) {
            cout << " <- " << parent[j];
            j = parent[j];
        }
        cout << " <- " << src << endl;
    }
}

int main() {
    Dijkstra dij;
    dij.readMatrix();
    
    int source;
    cout << "Enter the source vertex: ";
    cin >> source;

    dij.findShortestPath(source);
    dij.display(source);

    return 0;
}
