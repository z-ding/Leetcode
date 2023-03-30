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
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root != nullptr) {
            if (root->val < key) {
                root->right = deleteNode(root->right, key);
            }
            else if (root->val > key) {
                root->left = deleteNode(root->left, key);
            }
            else {//delete this node
                if (root->left == nullptr) {
                    return root->right;
                }
                else if (root->right == nullptr) {
                    return root->left;
                }
                else {
                    TreeNode* cur = root->right;
                    int val = 0;
                    while (cur) {
                        val = cur->val;
                        cur = cur->left;
                    }
                    root->val = val;
                    root->right = deleteNode(root->right, val);
                }
            }
        }
        return root;
    }
};