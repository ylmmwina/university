#include <iostream>
// завдання 2
using namespace std;

const int MAX = 100;

int main() {
    int n;
    cout << "Enter the number of vertices: ";
    cin >> n;

    int adj[MAX][MAX];
    cout << "Enter the adjacency matrix (only 0s and 1s):\n";
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> adj[i][j];

    int complement[MAX][MAX];

    // створення матриці доповнення графа
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            complement[i][j] = (i != j && adj[i][j] == 0) ? 1 : 0;

    // виведення матриці доповнення
    cout << "\nAdjacency matrix of the complement graph:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            cout << complement[i][j] << " ";
        cout << endl;
    }

    // вектор суміжності для доповнення графа
    cout << "\nAdjacency list of the complement graph:\n";
    for (int i = 0; i < n; ++i) {
        cout << "Vertex " << i << ": ";
        bool hasAdjacent = false;
        for (int j = 0; j < n; ++j) {
            if (complement[i][j] == 1) {
                cout << j << " ";
                hasAdjacent = true;
            }
        }
        if (!hasAdjacent) cout << "(no adjacent vertices)";
        cout << endl;
    }

    return 0;
}
