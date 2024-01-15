class Solution {
public:
    class trieNode {
    public:
        vector<int> children;
        vector<trieNode*> childptr;
        trieNode(int l, int r) {//constructor
            children = { l,r };
            childptr = { nullptr,nullptr };
        }
    };
    trieNode* root = new trieNode(0, 0);
    void insert(int num, int n) {
        trieNode* curNode = root;
        while (n >= 0) {
            int bit = (num >> n) & 1;
            if (curNode->children[bit] == 0) {
                //this index doesn't exist in current node's children, create a new subtree here
                //put the rest of the word in this new subtree
                for (int i = n; i >= 0; i--) {
                    trieNode* n = new trieNode(0, 0);
                    int x = (num >> i) & 1;
                    curNode->children[x] = 1;
                    curNode->childptr[x] = n;
                    curNode = curNode->childptr[x];
                }
                return;
            }
            else {//found this index in current node's children, go to this children and check next index
                curNode = curNode->childptr[bit];
                n--;
            }
        }
    }
    int res = 0;
    void maxxor(trieNode* node, int num, int d) {

        if (d == -1) return;
        int cur = (num >> d) & 1;
        if (node->children[0] + node->children[1] == 1) {
            int c = 0;
            if (node->children[1] == 1) c = 1;
            if (cur != c) res += (1 << d);
            maxxor(node->childptr[c], num, d - 1);
        }
        else {//two children, go to the one different as cur
            res += (1 << d);
            int ch = 0;
            if (cur == 0) ch = 1;
            maxxor(node->childptr[ch], num, d - 1);
        }


    }
    int findMaximumXOR(vector<int>& nums) {
        int digit = 0;
        for (auto x : nums) digit = max(x, digit);
        string m = bitset<32>(digit).to_string();
        int idx = 0;
        for (int i = 0; i < 32; i++) {
            if (m[i] == '1') {
                idx = i;
                break;
            }
        }
        int len = 31 - idx;
        for (auto x : nums) {
            insert(x, len);
        }
        int ans = 0;
        for (auto x : nums) {
            res = 0;
            //cout << s << endl;
            maxxor(root, x, len);
            ans = max(ans, res);
            //cout << ans << "," << x << endl;
        }
        return ans;
    }
};