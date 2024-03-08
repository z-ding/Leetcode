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
    struct AVL {
        struct AVLnode {
            int element;
            AVLnode* left;
            AVLnode* right;
            int height;
            AVLnode(int x, AVLnode* l, AVLnode* r, int h = 0) : element{ x }, left{ l }, right{ r }, height{ h } {}
        };

        AVLnode* root;
        AVL() {
            root = nullptr;
        }
        int height(AVLnode* t) {
            return t == nullptr ? -1 : t->height;
        }
        void insert(int x, AVLnode*& t) {
            if (t == nullptr)
                t = new AVLnode(x, nullptr, nullptr);
            else if (x < t->element)
                insert(x, t->left);
            else if (t->element < x)
                insert(x, t->right);
            balance(t);
        }

        void balance(AVLnode*& t) {

            if (t == nullptr) return;
            if (height(t->left) - height(t->right) > 1) {
                if (height(t->left->left) >= height(t->left->right)) rotateWithLeftChild(t);
                else rotateWithrightLeftChild(t);
            }
            else {
                if (height(t->right) - height(t->left) > 1) {
                    if (height(t->right->right) >= height(t->right->left)) rotateWithRightChild(t);
                    else rotateWithWithLeftRightChild(t);
                }
            }
            t->height = max(height(t->left), height(t->right)) + 1;
        }

        void rotateWithLeftChild(AVLnode*& k2) {
            AVLnode* k1 = k2->left;
            k2->left = k1->right;
            k1->right = k2;
            k2->height = max(height(k2->left), height(k2->right)) + 1;
            k1->height = max(height(k1->left), k2->height) + 1;
            k2 = k1;
        }
        void rotateWithRightChild(AVLnode*& k2) {
            AVLnode* k1 = k2->right;
            k2->right = k1->left;
            k1->left = k2;
            k2->height = max(height(k2->right), height(k2->left)) + 1;
            k1->height = max(height(k1->right), k2->height) + 1;
            k2 = k1;

        }

        void rotateWithrightLeftChild(AVLnode*& k3) {
            rotateWithRightChild(k3->left);
            rotateWithLeftChild(k3);
        }

        void rotateWithWithLeftRightChild(AVLnode*& k3) {

            rotateWithLeftChild(k3->right);
            rotateWithRightChild(k3);
        }
    };

    void traverseAndStore(TreeNode* root, vector<int>& temp) {
        if (root == nullptr) return;
        else temp.push_back(root->val);
        traverseAndStore(root->left, temp);
        traverseAndStore(root->right, temp);
    }

    void f(TreeNode*& ans, AVL::AVLnode*& temp) {
        if (temp == nullptr) return;
        else ans = new TreeNode(temp->element);

        f(ans->left, temp->left);
        f(ans->right, temp->right);


    }
    TreeNode* balanceBST(TreeNode* root) {
        vector<int> storeTree;

        traverseAndStore(root, storeTree);

        AVL* myAVL = new AVL();


        for (auto k : storeTree) {
            myAVL->insert(k, myAVL->root);
        }

        TreeNode* ans;

        AVL::AVLnode* temp = myAVL->root;

        f(ans, temp);



        return ans;
    }
};