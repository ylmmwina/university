#include <iostream>
using namespace std;

// завдання 1

// структура вузла бінарного дерева
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// глобальна змінна для збереження максимальної суми
int maxSum = -1000000000;

// допоміжна функція для обчислення максимальної суми
int maxPathSumHelper(TreeNode* root) {
    if (root == nullptr) return 0;

    // рекурсивно знаходимо максимум зліва і справа
    int left = max(0, maxPathSumHelper(root->left));
    int right = max(0, maxPathSumHelper(root->right));

    // оновлюємо глобальну змінну, якщо поточна сума більша
    int currentMax = root->val + left + right;
    if (currentMax > maxSum) maxSum = currentMax;

    // повертаємо максимум із піддерева, який можна використати вище
    return root->val + max(left, right);
}

int maxPathSum(TreeNode* root) {
    maxSum = -1000000000; // скидаємо значення перед запуском
    maxPathSumHelper(root);
    return maxSum;
}

int main() {
    TreeNode* root = new TreeNode(-10);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

    cout << "Maximum path amount: " << maxPathSum(root) << endl;

    return 0;
}
