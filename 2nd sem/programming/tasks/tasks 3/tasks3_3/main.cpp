#include <iostream>
using namespace std;

// завдання 3

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// функція для знаходження LCA
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || root == p || root == q) return root;

    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);

    if (left && right) return root;  // p і q у різних піддеревах
    return left ? left : right;      // повертаємо ненульову гілку
}

int main() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(5);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(2);
    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(4);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(8);

    TreeNode* node1 = root->left; // 5
    TreeNode* node2 = root->right; // 1
    TreeNode* lca = lowestCommonAncestor(root, node1, node2);
    cout << "LCA of " << node1->val << " and " << node2->val << " is: " << lca->val << endl;

    node1 = root->left;        // 5
    node2 = root->left->right->right; // 4
    lca = lowestCommonAncestor(root, node1, node2);
    cout << "LCA of " << node1->val << " and " << node2->val << " is: " << lca->val << endl;

    return 0;
}
