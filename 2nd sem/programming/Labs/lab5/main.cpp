#include <iostream>

using namespace std;

// варіант 5

const int MAXN = 1001;
const int INF = 1000000000;

int n, m;
int adj[MAXN][MAXN];  // матриця суміжності
int dist[MAXN];
int parent[MAXN];
bool visited[MAXN];

// проста мінімальна купа (лінійний пошук)
int extract_min(int n) {
    int min_v = -1;
    for (int i = 1; i <= n; ++i) {
        if (!visited[i] && (min_v == -1 || dist[i] < dist[min_v])) {
            min_v = i;
        }
    }
    return min_v;
}

// вивід шляху через parent[]
void print_path(int v) {
    if (parent[v] == -1) {
        cout << v;
        return;
    }
    print_path(parent[v]);
    cout << " -> " << v;
}

int main() {
    cout << "Enter number of vertices and edges: ";
    cin >> n >> m;

    // ініціалізація графа
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            adj[i][j] = INF;

    cout << "Enter edges in the format: from to weight\n";
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u][v] = w;  // для неорієнтованого графа також: adj[v][u] = w;
    }

    int start;
    cout << "Enter the starting vertex: ";
    cin >> start;

    // ініціалізація
    for (int i = 1; i <= n; ++i) {
        dist[i] = INF;
        parent[i] = -1;
        visited[i] = false;
    }
    dist[start] = 0;

    // алгоритм Дейкстри
    for (int i = 1; i <= n; ++i) {
        int u = extract_min(n);
        if (u == -1) break; // немає доступних вершин
        visited[u] = true;

        for (int v = 1; v <= n; ++v) {
            if (adj[u][v] != INF && !visited[v]) {
                if (dist[u] + adj[u][v] < dist[v]) {
                    dist[v] = dist[u] + adj[u][v];
                    parent[v] = u;
                }
            }
        }
    }

    cout << "\nMinimum distances from vertex " << start << ":\n";
    for (int i = 1; i <= n; ++i) {
        cout << "To " << i << ": ";
        if (dist[i] == INF)
            cout << "Unreachable\n";
        else
            cout << dist[i] << "\n";
    }

    cout << "\nPaths from vertex " << start << ":\n";
    for (int i = 1; i <= n; ++i) {
        cout << "Path to " << i << ": ";
        if (dist[i] == INF) {
            cout << "No path\n";
        } else {
            print_path(i);
            cout << "\n";
        }
    }

    return 0;
}
