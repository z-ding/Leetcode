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
    string serialize(TreeNode* root) {
        if (root == nullptr) return ".,";
        string s = to_string(root->val) + ",";
        s += serialize(root->left);
        s += serialize(root->right);
        return s;
    }
    // Decodes your encoded data to tree.
    int idx = 0;
    TreeNode* deser(vector<int>& v) {
        //cout << idx << "," << v[idx] << endl;
        if (v[idx] == 1001) return nullptr;
        auto root = new TreeNode(v[idx]);
        idx++;
        root->left = deser(v);
        idx++;
        root->right = deser(v);
        return root;
    }
    TreeNode* deserialize(string data) {
        //cout << data << endl;
        vector<int> preOrder;
        string t;
        for (int i = 0; i < data.size(); i++) {
            if (data[i] != ',' && data[i] != '.') t += data[i];
            else if (data[i] == '.') {
                preOrder.push_back(1001);//nullptr
            }
            else {//data[i] != ','
                if (t.size()) {
                    preOrder.push_back(stoi(t));
                    t = "";
                }
            }
        }
        //for (auto &x:preOrder) cout << x << ",";
        if (preOrder.size() == 1) return nullptr;//nullptr tree
        return deser(preOrder);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));