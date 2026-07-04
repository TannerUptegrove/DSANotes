#include <iostream>
#include <climits>
#include <vector>
using namespace std;

class WeightedGraph {
    int numVertices;
    int numEdges;
    vector<vector<int>> adjacencyMatrix;

    public:
    WeightedGraph(int s) {
        numVertices = s;
        numEdges = 0;
        adjacencyMatrix.resize(numVertices, vector<int>(numVertices, 0));
    }

    void InsertEdge(int vertex1, int vertex2, int weight) {
        if (vertex1 == vertex2) {
            cout << "\nDuplicate vertex entries found...\n";
            return;
        }
            

        if (vertex1 < 0 || vertex1 > numVertices) {
            cout << "\nVertex 1 is out of the graph range...\n";
            return;
        }

        if (vertex2 < 0 || vertex2 > numVertices) {
            cout << "\nVertex 2 is out of the graph range...\n";
            return;
        }

        // Allows for bi-directional edges.
        adjacencyMatrix[vertex1][vertex2] = weight;
        //adjacencyMatrix[vertex2][vertex1] = weight;
        numEdges++;
    }

    void Dijkstra(int startVertex) {
        // Each element represents the distance from
        // the starting vertex to that index's vertex.
        vector<int> distances(numVertices, INT_MAX);

        // Each element represents a vertex, and saves
        // whether it has been visited or not yet.
        vector<bool> visited(numVertices, false);

        // The starting vertex's distance is always set to 0.
        distances[startVertex] = 0;

        // Iterates for each vertex but the last one.
        for (int i = 0; i < numVertices - 1; i++) {
            // u represents the current vertex of an iteration.
            int u = FindMinDistance(distances, visited);
            visited[u] = true;

            // j represents the index of a neighboring vertex.
            for (int j = 0; j < numVertices; j++) {

                // Where distances get overridden.
                if (!visited[j] &&
                    adjacencyMatrix[u][j] != 0 &&
                    distances[u] != INT_MAX &&
                    distances[u] + adjacencyMatrix[u][j] < distances[j]) {
                    distances[j] = distances[u] + adjacencyMatrix[u][j];
                }
            }
        }

        // Display the shortest distances from the starting vertex, to every other one.
        cout << "\nDijkstra's Algorithm\nDistances from the starting vertex " << startVertex << endl;
        for (int i = 0; i < numVertices; i++) {
            cout << "To vertex " << i << ": ";
            if (distances[i] == INT_MAX)
                cout << "INF\n";
            else
                cout << distances[i] << endl;
        }
    }

    // Used to select the next vertex for each iteration of the outer Dijkstra for-loop.
    // It makes sure to return the index of the next closest vertex that hasn't been visited.
    int FindMinDistance(vector<int>& distances, vector<bool>& visited) {
        int minValue = INT_MAX;
        int minIndex = -1;

        for (int i = 0; i < numVertices; i++) {
            if (!visited[i] && distances[i] <= minValue) {
                minValue = distances[i];
                minIndex = i;
            }
        }
        return minIndex;
    }

    // Since this graph uses an adjacency matrix that stores the weights
    // of the edges that intersect the vertices, this version of the algorithm is
    // written in the worst-case time complexity of O(V^3).
    //
    // There are more efficient versions of this, but it would require the
    // graph to be represented differently.
    void BellmanFord(int startVertex) {
        vector<int> distances(numVertices, INT_MAX);
        distances[startVertex] = 0;

        for (int i = 0; i < numVertices - 1; i++) {
            bool updated = false;

            // To grab the source vertex of an edge.
            for (int u = 0; u < numVertices; u++) {

                // To grab the destination vertex of an edge.
                for (int v = 0; v < numVertices; v++) {
                    if (adjacencyMatrix[u][v] != 0 &&
                        distances[u] != INT_MAX &&
                        distances[u] + adjacencyMatrix[u][v] < distances[v]) {
                        distances[v] = distances[u] + adjacencyMatrix[u][v];
                        updated = true;
                    }
                }
            }

            if (!updated) break; // Allows the loop to end if no distances were updated.
        }

        // Detecting a negative cycle by running the above check one more time.
        for (int u = 0; u < numVertices; u++) {
            for (int v = 0; v < numVertices; v++) {
                if (adjacencyMatrix[u][v] != 0 &&
                    distances[u] != INT_MAX &&
                    distances[u] + adjacencyMatrix[u][v] < distances[v]) {
                    cout << "\nCycle detected in graph...\n";
                    return;
                }
            }
        }

        cout << "\nBellman-Ford Algorithm\nDistances from the starting vertex " << startVertex << endl;
        for (int i = 0; i < numVertices; i++) {
            cout << "To vertex " << i << ": ";
            if (distances[i] == INT_MAX)
                cout << "INF\n";
            else
                cout << distances[i] << endl;
        }
    }

    void DisplayAdjacencyMatrix() {
        cout << "\nAdjacency Matrix Representation:\n";

        cout << "  ";
        for (int i = 0; i < numVertices; i++)
            cout << i << " ";
        cout << endl;

        for (int i = 0; i < numVertices; i++) {
            cout << i << " ";
            for (int j = 0; j < numVertices; j++) {
                if (adjacencyMatrix[i][j] != 0 || i == j)
                    cout << adjacencyMatrix[i][j] << " ";
                else
                    cout << "X ";
            }
            cout << endl;
        }
    }
};

// Prim's Algorithm coming soon...

int main() {
    WeightedGraph g(6);
    /*
    //Dijkstra Test
    g.InsertEdge(0, 1, 3);
    g.InsertEdge(0, 2, 4);
    g.InsertEdge(0, 3, 7);
    g.InsertEdge(1, 2, 1);
    g.InsertEdge(1, 5, 5);
    g.InsertEdge(2, 3, 2);
    g.InsertEdge(2, 5, 6);
    g.InsertEdge(3, 4, 3);
    g.InsertEdge(3, 6, 6);
    g.InsertEdge(4, 5, 1);
    g.InsertEdge(4, 6, 3);
    g.InsertEdge(4, 7, 4);
    g.InsertEdge(5, 7, 8);
    g.InsertEdge(6, 7, 2);
    g.DisplayAdjacencyMatrix();
    g.Dijkstra(0);
    */
    
    //Bellman Ford Test
    g.InsertEdge(0 , 2, 2);
    g.InsertEdge(1, 0, 1);
    g.InsertEdge(2, 1, -2);
    g.InsertEdge(3, 0, -4);
    g.InsertEdge(3, 2, -1);
    g.InsertEdge(4, 3, 1);
    g.InsertEdge(5, 0, 10);
    g.InsertEdge(5, 4, 8);
    g.DisplayAdjacencyMatrix();
    g.BellmanFord(5);
        
    return 0;
}