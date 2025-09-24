#include <iostream>
using namespace std;

// завдання 5

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// допоміжна функція для глибини обходу обчислення суми
int sumRootToLeafHelper(TreeNode* node, int current) {
    if (!node) return 0;

    // формуємо нове число: зсув вліво (додаємо біт) + поточне значення вузла
    current = (current << 1) | node->val;

    // якщо ми на листі — повертаємо сформоване число
    if (!node->left && !node->right)
        return current;

    // рекурсивно додаємо суми з лівого і правого піддерев
    return sumRootToLeafHelper(node->left, current) + sumRootToLeafHelper(node->right, current);
}

// основна функція
int sumRootToLeaf(TreeNode* root) {
    return sumRootToLeafHelper(root, 0);
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(0);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(0);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(1);

    int result = sumRootToLeaf(root);
    cout << "Sum of all root-to-leaf binary numbers: " << result << endl;

    return 0;
}
