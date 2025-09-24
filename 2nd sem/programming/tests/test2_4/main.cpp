#include <iostream>
// завдання 4
using namespace std;

const int MAX = 100;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

struct QueueNode {
    TreeNode* node;
    int level;
};

void printOddLevels(TreeNode* root) {
    if (!root) return;

    QueueNode queue[MAX];
    int front = 0, rear = 0;

    queue[rear++] = {root, 0};

    int currentLevel = 0;
    int levelElements[MAX];
    int levelSize = 0;

    while (front < rear) {
        QueueNode qNode = queue[front++];
        TreeNode* node = qNode.node;
        int level = qNode.level;

        if (level != currentLevel) {
            // якщо рівень непарний — друкуємо
            if (currentLevel % 2 == 0) {
                cout << "[";
                for (int i = 0; i < levelSize; ++i) {
                    cout << levelElements[i];
                    if (i != levelSize - 1) cout << ", ";
                }
                cout << "]" << endl;
            }
            currentLevel = level;
            levelSize = 0;
        }

        levelElements[levelSize++] = node->val;

        if (node->left) queue[rear++] = {node->left, level + 1};
        if (node->right) queue[rear++] = {node->right, level + 1};
    }

    // вивід останнього рівня, якщо потрібно
    if (currentLevel % 2 == 0) {
        cout << "[";
        for (int i = 0; i < levelSize; ++i) {
            cout << levelElements[i];
            if (i != levelSize - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
}

// (дерево з прикладу)
TreeNode* buildExampleTree() {
    TreeNode* root = new TreeNode(8);
    root->left = new TreeNode(3);
    root->right = new TreeNode(10);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(6);
    root->left->right->left = new TreeNode(4);
    root->left->right->right = new TreeNode(7);
    root->right->right = new TreeNode(14);
    root->right->right->left = new TreeNode(13);
    return root;
}

int main() {
    TreeNode* root = buildExampleTree();
    cout << "Odd-level lists:" << endl;
    printOddLevels(root);
    return 0;
}
