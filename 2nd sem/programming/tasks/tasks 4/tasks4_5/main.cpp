#include <iostream>
// завдання 5
using namespace std;

const int MAXN = 100; // максимальна кількість вершин
int graph[MAXN][MAXN]; // матриця суміжності
bool visited[MAXN];    // масив відвіданих вершин
int farthestNode;      // найдальша вершина під час DFS
int maxDistance;       // найбільша відстань під час DFS

// функція DFS для знаходження найдальшої вершини
void dfs(int node, int dist, int n) {
    visited[node] = true;
    if (dist > maxDistance) {
        maxDistance = dist;
        farthestNode = node;
    }

    for (int i = 0; i < n; i++) {
        if (graph[node][i] && !visited[i]) {
            dfs(i, dist + 1, n);
        }
    }
}

int main() {
    int n;
    cout << "Enter the number of nodes: ";
    cin >> n;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    // зчитування n-1 ребра дерева
    cout << "Enter the edges (u v):\n";
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    // перший DFS — шукаємо найдальшу вершину від 0
    for (int i = 0; i < n; i++) visited[i] = false;
    maxDistance = 0;
    dfs(0, 0, n);
    int start = farthestNode;

    // другий DFS — шукаємо діаметр
    for (int i = 0; i < n; i++) visited[i] = false;
    maxDistance = 0;
    dfs(start, 0, n);

    cout << "Diameter of the tree: " << maxDistance << endl;

    return 0;
}
