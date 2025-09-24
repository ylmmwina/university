#include <iostream>
// завдання 4
const int INF = 1e9; // Нескінченність

using namespace std;

int main() {
    int n, m;
    cout << "Enter the number of devices: ";
    cin >> n;
    cout << "Enter the number of cables: ";
    cin >> m;

    // матриця суміжності
    int** graph = new int*[n];
    for (int i = 0; i < n; i++) {
        graph[i] = new int[n];
        for (int j = 0; j < n; j++) {
            graph[i][j] = INF; // Початково немає з'єднання
        }
    }

    // зчитування кабелів: кожен кабель з вагою (енергетичними втратами)
    cout << "Enter the cables as 'u v w' (u to v with loss w):\n";
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u][v] = w;
        graph[v][u] = w; // з'єднання двостороннє
    }

    int A, B, X;
    cout << "Enter start device (A): ";
    cin >> A;
    cout << "Enter target device (B): ";
    cin >> B;
    cout << "Enter available battery charge (X): ";
    cin >> X;

    int* dist = new int[n];
    bool* visited = new bool[n];

    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = false;
    }

    dist[A] = 0;

    // алгоритм Дейкстри
    for (int count = 0; count < n - 1; count++) {
        // знаходимо вершину з найменшою відстанню серед невідвіданих
        int u = -1, minDist = INF;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                u = i;
            }
        }

        if (u == -1) break; // немає досяжних вершин

        visited[u] = true;

        // оновлюємо відстані для сусідів
        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] < INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    if (dist[B] <= X) {
        cout << "Possible to reach within battery limit." << endl;
    } else {
        cout << "Not possible to reach within battery limit." << endl;
    }

    for (int i = 0; i < n; i++) delete[] graph[i];
    delete[] graph;
    delete[] dist;
    delete[] visited;

    return 0;
}
