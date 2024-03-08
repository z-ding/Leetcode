/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:
    int nextroot = 0;
    int idx = 0;
    string inorderindexing(TreeNode* root) {
        if (root == nullptr) return "";
        string s;
        s += inorderindexing(root->left);
        s = s + to_string(idx) + "," + to_string(root->val) + ",";
        root->val = idx;
        idx++;
        s += inorderindexing(root->right);
        return s;
    }
    string inorder(TreeNode* root) {
        if (root == nullptr) return "";
        string s;
        s += inorder(root->left);
        s = s + to_string(root->val) + ",";
        s += inorder(root->right);
        return s;
    }
    void deref(TreeNode* root, unordered_map<int, int>& re) {
        if (root == nullptr) return;
        deref(root->left, re);
        int index = root->val;
        root->val = re[index];
        deref(root->right, re);
    }
    string preorder(TreeNode* root) {
        if (root == nullptr) return "";
        string s = to_string(root->val) + ",";
        s += preorder(root->left);
        s += preorder(root->right);
        return s;
    }
    string serialize(TreeNode* root) {
        string a = inorderindexing(root);
        a += ":";
        a += inorder(root);
        a += "|";
        a += preorder(root);
        //cout << a << endl;
        return a;
    }
    TreeNode* recon(vector<int>& inOrder, vector<int>& preOrder, int preidx, int l, int r) {
        if (preidx >= preOrder.size()) return nullptr;
        TreeNode* root = new TreeNode(preOrder[preidx]);
        //find preidx val in range [l,r] in inorder
        //cout << preidx <<"," << l << r << endl;
        if (l <= r) {
            int split = l;
            bool hasLeft = false;
            for (int i = l; i <= r; i++) {
                if (inOrder[i] != preOrder[preidx]) {
                    hasLeft = true;//i belongs to left subtree
                    split = i;
                }
                else {//find root val in inOrder, split at i
                    break;
                }
            }
            //build all available left subtree first
            if (hasLeft) {
                nextroot++;
                root->left = recon(inOrder, preOrder, nextroot, l, split);
            }
            //build right subtree if there is any
            if (hasLeft && split + 2 <= r) {//split +1 is current root
                //[split +2 , r] is right subtree
                nextroot++;
                root->right = recon(inOrder, preOrder, nextroot, split + 2, r);
            }
            else if (!hasLeft && split + 1 <= r) {//split is current root
                nextroot++;
                root->right = recon(inOrder, preOrder, nextroot, split + 1, r);
            }
        }
        return root;
    }
    // Decodes your encoded data to tree.

    TreeNode* deserialize(string data) {
        //for (auto &x:ref) cout << x.first << "," << x.second << endl;
        vector<int> inOrder;
        vector<int> preOrder;
        vector<int> refidx;
        string t;
        int a = 2;
        for (int i = 0; i < data.size(); i++) {
            if (data[i] != ',' && data[i] != '|' && data[i] != ':') t += data[i];
            else if (data[i] == '|') {
                a = 1;
            }
            else if (data[i] == ':') {
                a = 0;
            }
            else {//data[i] != ','
                if (a == 0) inOrder.push_back(stoi(t));
                else if (a == 1) preOrder.push_back(stoi(t));
                else {//a ==2
                    refidx.push_back(stoi(t));
                }
                t = "";
            }
        }
        unordered_map<int, int> re;
        for (int i = 0; i < refidx.size(); i += 2) {
            re[refidx[i]] = refidx[i + 1];
        }
        /*
        cout << "inorder" << endl;
        for (auto &x:inOrder) cout << x << ",";
        cout << endl;
        cout << "preOrder" << endl;
        for (auto &x:preOrder) cout << x << ",";
        cout << endl;
        */
        auto root = recon(inOrder, preOrder, 0, 0, inOrder.size() - 1);
        deref(root, re);
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));