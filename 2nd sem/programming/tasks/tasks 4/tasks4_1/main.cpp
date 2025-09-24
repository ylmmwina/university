#include <iostream>
// завдання 1
using namespace std;

// функція для обходу острова (глибина в першу чергу)
void dfs(int** grid, int n, int m, int i, int j) {
    // якщо координати вийшли за межі або поточна клітинка — не острів
    if (i < 0 || i >= n || j < 0 || j >= m || grid[i][j] == 0) {
        return;
    }

    // позначаємо поточну клітинку як відвідану
    grid[i][j] = 0;

    // рекурсивно обходимо суміжні клітинки
    dfs(grid, n, m, i + 1, j);
    dfs(grid, n, m, i - 1, j);
    dfs(grid, n, m, i, j + 1);
    dfs(grid, n, m, i, j - 1);
}

int main() {
    int n, m;
    cout << "Enter the number of rows: ";
    cin >> n;
    cout << "Enter the number of columns: ";
    cin >> m;

    int** grid = new int*[n];
    for (int i = 0; i < n; i++) {
        grid[i] = new int[m];
    }

    cout << "Enter the map values (0 for water, 1 for island):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    int islandCount = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            // якщо знаходимо новий острів
            if (grid[i][j] == 1) {
                islandCount++;
                dfs(grid, n, m, i, j);
            }
        }
    }

    cout << "Number of islands: " << islandCount << endl;

    for (int i = 0; i < n; i++) {
        delete[] grid[i];
    }
    delete[] grid;

    return 0;
}
