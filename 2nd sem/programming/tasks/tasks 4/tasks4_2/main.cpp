#include <iostream>
// завдання 2
using namespace std;

// функція для перевірки наявності циклу за допомогою DFS
bool dfs(int** graph, int n, int node, bool* visited, bool* recursionStack) {
    // якщо вузол ще не відвіданий
    if (!visited[node]) {
        visited[node] = true;
        recursionStack[node] = true;

        // перевіряємо всіх сусідів
        for (int i = 0; i < n; i++) {
            if (graph[node][i]) {
                // якщо сусід ще не відвіданий — рекурсивно перевіряємо його
                if (!visited[i] && dfs(graph, n, i, visited, recursionStack)) {
                    return true;
                }
                // якщо сусід вже в стеку рекурсії — виявлено цикл
                else if (recursionStack[i]) {
                    return true;
                }
            }
        }
    }

    recursionStack[node] = false;
    return false;
}

int main() {
    int n, e;

    cout << "Enter the number of code blocks: ";
    cin >> n;
    cout << "Enter the number of dependencies: ";
    cin >> e;

    // ініціалізація графа
    int** graph = new int*[n];
    for (int i = 0; i < n; i++) {
        graph[i] = new int[n];
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }

    cout << "Enter the dependencies in format 'a b' (a -> b):\n";
    for (int i = 0; i < e; i++) {
        int a, b;
        cin >> a >> b;
        graph[a][b] = 1;
    }

    bool* visited = new bool[n];
    bool* recursionStack = new bool[n];

    for (int i = 0; i < n; i++) {
        visited[i] = false;
        recursionStack[i] = false;
    }

    bool hasCycle = false;

    // перевірка кожного вузла
    for (int i = 0; i < n; i++) {
        if (dfs(graph, n, i, visited, recursionStack)) {
            hasCycle = true;
            break;
        }
    }

    if (hasCycle) {
        cout << "Cycle detected." << endl;
    } else {
        cout << "No cycle detected." << endl;
    }

    for (int i = 0; i < n; i++) {
        delete[] graph[i];
    }
    delete[] graph;
    delete[] visited;
    delete[] recursionStack;

    return 0;
}
