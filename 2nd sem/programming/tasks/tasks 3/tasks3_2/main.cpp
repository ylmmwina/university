#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// завдання 2

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// функція для zigzag level order обходу
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;

    queue<TreeNode*> q;
    q.push(root);
    bool leftToRight = true;

    while (!q.empty()) {
        int size = q.size();
        vector<int> level(size);

        for (int i = 0; i < size; ++i) {
            TreeNode* node = q.front(); q.pop();

            // визначаємо позицію для вставки
            int index = leftToRight ? i : (size - 1 - i);
            level[index] = node->val;

            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }

        // переходимо до наступного рівня з протилежним напрямком
        leftToRight = !leftToRight;
        result.push_back(level);
    }

    return result;
}

// функція для друку результату
void printZigzag(const vector<vector<int>>& levels) {
    cout << "[";
    for (size_t i = 0; i < levels.size(); ++i) {
        cout << "[";
        for (size_t j = 0; j < levels[i].size(); ++j) {
            cout << levels[i][j];
            if (j < levels[i].size() - 1) cout << ", ";
        }
        cout << "]";
        if (i < levels.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(6);

    vector<vector<int>> result = zigzagLevelOrder(root);
    cout << "Zigzag Level Order Traversal: ";
    printZigzag(result);

    return 0;
}
