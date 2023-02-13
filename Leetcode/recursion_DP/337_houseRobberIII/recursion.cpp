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
    unordered_map<TreeNode*, int> memo;
    int robber(TreeNode* node) {
        if (memo.find(node) != memo.end()) {
            return memo[node];
        }
        if (node == nullptr) {
            memo.emplace(node, 0);
            return 0;
        }
        //cout << node -> val << endl;
        //not rob this house
        int nr = robber(node->left) + robber(node->right);
        //rob this house
        int r = 0;
        if (node->left == nullptr && node->right == nullptr) {
            r = node->val;
        }
        else if (node->left == nullptr && node->right != nullptr) {
            r = node->val + robber(node->right->left) + robber(node->right->right);
        }
        else if (node->left != nullptr && node->right == nullptr) {
            r = node->val + robber(node->left->left) + robber(node->left->right);
        }
        else {
            r = node->val + robber(node->left->left) + robber(node->left->right) + robber(node->right->left) + robber(node->right->right);
        }
        memo.emplace(node, max(r, nr));
        return memo[node];
    }
    int rob(TreeNode* root) {
        return robber(root);
    }
};