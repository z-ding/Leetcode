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
    TreeNode* invert(TreeNode* node) {
        if (node == nullptr) {
            return nullptr;
        }
        //post order traversal
        invert(node->left); //go to left subtree
        invert(node->right);//go to right subtree
        //go to node, swap left and right
        TreeNode* copy = node->right;
        node->right = node->left;
        node->left = copy;
        return node;
    }
    TreeNode* invertTree(TreeNode* root) {
        return invert(root);
    }
};