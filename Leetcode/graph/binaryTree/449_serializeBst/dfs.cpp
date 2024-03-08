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

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (root == nullptr) return "";
        string s = to_string(root->val) + ",";
        s += serialize(root->left);
        s += serialize(root->right);
        return s;
    }

    // Decodes your encoded data to tree.
    TreeNode* recon(vector<int>& v, int rootidx, int l, int r) {
        //cout << rootidx << "," << l << "," << r << endl;
        if (rootidx >= v.size()) return nullptr;
        TreeNode* root = new TreeNode(v[rootidx]);
        if (l <= r) {
            int split = l;
            bool lt = false;
            for (int i = l; i <= r; i++) {
                if (v[i] <= v[rootidx]) {
                    lt = true;
                    split = i;
                }
                else break;//split stop at the left subtree inclusive
            }
            TreeNode* left;
            if (lt) {//a valid leftsubtree exist
                TreeNode* left = recon(v, l, l + 1, split);
                root->left = left;
                //right subtree start with split +1
                if (split + 1 <= r) {
                    TreeNode* right = recon(v, split + 1, split + 2, r);
                    root->right = right;
                }
            }
            else {//no left subtree, right subtree start with l
                TreeNode* right = recon(v, l, l + 1, r);
                root->right = right;
            }
            //cout << rootidx << "," << l << "," << r << "left done" << endl;
            //cout << rootidx << "," << l << "," << r << "right done " << endl;
        }

        return root;
    }
    TreeNode* deserialize(string data) {
        vector<int> v;
        string t;
        for (int i = 0; i < data.size(); i++) {
            if (data[i] != ',') t += data[i];
            else {
                v.push_back(stoi(t));
                t = "";
            }
        }
        return recon(v, 0, 1, v.size() - 1);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec* ser = new Codec();
// Codec* deser = new Codec();
// string tree = ser->serialize(root);
// TreeNode* ans = deser->deserialize(tree);
// return ans;