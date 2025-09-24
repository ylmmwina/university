#include <iostream>
// завдання 3
using namespace std;

// функція DFS для перевірки зв'язності графа
void dfs(int** graph, bool* visited, int n, int v) {
    visited[v] = true;
    for (int i = 0; i < n; i++) {
        if (graph[v][i] && !visited[i]) {
            dfs(graph, visited, n, i);
        }
    }
}

int main() {
    int n, e;
    cout << "Enter the number of intersections: ";
    cin >> n;
    cout << "Enter the number of roads: ";
    cin >> e;

    // матриця суміжності
    int** graph = new int*[n];
    for (int i = 0; i < n; i++) {
        graph[i] = new int[n];
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }

    cout << "Enter the roads as pairs 'a b' (road between a and b):\n";
    for (int i = 0; i < e; i++) {
        int a, b;
        cin >> a >> b;
        graph[a][b] = 1;
        graph[b][a] = 1; // неорієнтований граф
    }

    // підрахунок степеня кожної вершини
    int* degree = new int[n];
    for (int i = 0; i < n; i++) {
        degree[i] = 0;
        for (int j = 0; j < n; j++) {
            if (graph[i][j]) degree[i]++;
        }
    }

    // пошук кількості вершин з непарним степенем
    int oddCount = 0;
    for (int i = 0; i < n; i++) {
        if (degree[i] % 2 == 1) oddCount++;
    }

    // перевірка зв'язності(знаходимо першу вершину з ребрами)
    int start = -1;
    for (int i = 0; i < n; i++) {
        if (degree[i] > 0) {
            start = i;
            break;
        }
    }

    bool* visited = new bool[n];
    for (int i = 0; i < n; i++) visited[i] = false;

    // якщо існує хоч одна вершина з ребрами — перевіряємо зв'язність
    if (start != -1) {
        dfs(graph, visited, n, start);
    }

    // перевірка, чи всі вершини з ребрами були відвідані
    bool connected = true;
    for (int i = 0; i < n; i++) {
        if (degree[i] > 0 && !visited[i]) {
            connected = false;
            break;
        }
    }

    if (connected && oddCount == 2) {
        cout << "Euler path is possible." << endl;
    } else {
        cout << "Euler path is not possible." << endl;
    }

    for (int i = 0; i < n; i++) delete[] graph[i];
    delete[] graph;
    delete[] degree;
    delete[] visited;

    return 0;
}
