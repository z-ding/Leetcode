/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* lcs(TreeNode* node, TreeNode* p, TreeNode* q) {
        if (node == nullptr || node == p || node == q) {
            return node;
        }

        TreeNode* left = lcs(node->left, p, q);
        TreeNode* right = lcs(node->right, p, q);
        if (left != nullptr && right != nullptr) {
            return node;//lcs
        }

        if (left != nullptr) {
            return left;
        }
        if (right != nullptr) {
            return right;
        }
        return nullptr;//left == nullptr && right == nullptr
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        return lcs(root, p, q);
    }
};