#include <iostream>
// завдання 3
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// ця функція обчислює глибину піддерев і перевіряє баланс
int checkBalance(TreeNode* node, int d, bool& isBalanced) {
    if (!node) return 0;

    int leftDepth = checkBalance(node->left, d, isBalanced);
    int rightDepth = checkBalance(node->right, d, isBalanced);

    if (abs(leftDepth - rightDepth) > d) {
        isBalanced = false;
    }

    return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
}

// функція для перевірки балансу
bool isDHeightBalanced(TreeNode* root, int d) {
    bool isBalanced = true;
    checkBalance(root, d, isBalanced);
    return isBalanced;
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);

    int d;
    cout << "Enter the allowed depth difference (d): ";
    cin >> d;

    bool result = isDHeightBalanced(root, d);
    if (result)
        cout << "The tree is balanced for d = " << d << endl;
    else
        cout << "The tree is NOT balanced for d = " << d << endl;

    return 0;
}
