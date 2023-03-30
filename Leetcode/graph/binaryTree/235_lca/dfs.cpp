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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr || root == p || root == q) {
            return root;
        }
        TreeNode* left = nullptr;
        TreeNode* right = nullptr;
        if (p->val < root->val && q->val < root->val) {
            left = lowestCommonAncestor(root->left, p, q);
        }
        else if (p->val > root->val && q->val > root->val) {
            right = lowestCommonAncestor(root->right, p, q);
        }
        else {
            left = lowestCommonAncestor(root->left, p, q);
            right = lowestCommonAncestor(root->right, p, q);
        }
        if (left != nullptr && right != nullptr) {

            return root;
        }
        if (left != nullptr) {
            return left;
        }
        if (right != nullptr) {
            return right;
        }
        return nullptr;
    }
};