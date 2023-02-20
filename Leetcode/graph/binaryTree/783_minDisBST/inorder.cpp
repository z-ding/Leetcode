/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int mind = 100000;
    int prev = -1;
    void inorder(TreeNode* node) {
        if (node == nullptr) {
            return;
        }

        inorder(node->left);
        if (prev != -1) {
            mind = min(mind, node->val - prev);
        }
        prev = node->val;
        inorder(node->right);
    }
    int minDiffInBST(TreeNode* root) {
        inorder(root);
        return mind;
    }
};