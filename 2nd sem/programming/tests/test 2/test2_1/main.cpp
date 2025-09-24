#include <iostream>
// завдання 1
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// функція для обчислення глибини піддерева і одночасного знаходження максимальної різниці
int getDepth(TreeNode* node, int& maxDiff) {
    if (node == nullptr) return 0;

    int leftDepth = getDepth(node->left, maxDiff);
    int rightDepth = getDepth(node->right, maxDiff);

    int diff = abs(leftDepth - rightDepth);
    if (diff > maxDiff) {
        maxDiff = diff;
    }

    return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
}

// функція для знаходження максимальної різниці
int maxDepthDifference(TreeNode* root) {
    int maxDiff = 0;
    getDepth(root, maxDiff);
    return maxDiff;
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);

    int result = maxDepthDifference(root);
    cout << "Maximum depth difference between left and right subtree: " << result << endl;

    return 0;
}
