class Solution {
public:
    /*
    array xxxxxxx
    index   i   j
    Range Sum from i to j:
    lb <= RS[ij] = PrefixSum[j] - PrefixSum[i-1] <=ub
    PrefixSum[j] <= ub + PrefixSum[i-1]
    PrefixSum[j] >= lb + PrefixSum[i-1]
    the question is converted to:
    Given an index i, find all index j which is after index i, so that that lb + PrefixSum[i-1] <= PrefixSum[j] <= ub + PrefixSum[i-1]
    */
    class Node {
    public:
        int start;
        int end;
        int val;
        Node* left;
        Node* right;
        Node(int s, int e, int v) {
            start = s;
            end = e;
            val = v;
            left = nullptr;
            right = nullptr;
        }
    };
    Node* root;
    Node* build(vector<int>& nums, int low, int high) {
        if (low == high) {
            return new Node(low, low, nums[low]);
        }
        int mid = (low + high) / 2;
        Node* left = build(nums, low, mid);
        Node* right = build(nums, mid + 1, high);
        Node* parent = new Node(low, high, left->val + right->val);
        parent->left = left;
        parent->right = right;
        return parent;
    }
    void view(Node* node) {
        if (node == nullptr) {
            return;
        }
        cout << node->start << "," << node->end << ":" << node->val << endl;
        view(node->left);
        view(node->right);
    }
    int query(Node* node, int l, int u) {
        if (l == node->start && u == node->end) {
            return node->val;
        }
        int mid = (node->start + node->end) / 2;
        if (l > mid) {
            return query(node->right, l, u);
        }
        if (u <= mid) {
            return query(node->left, l, u);
        }
        return query(node->left, l, mid) + query(node->right, mid + 1, u);
    }
    void update(Node* node, int index) {
        if (node->start == index && node->end == index) {
            node->val--;
            return;
        }
        int mid = (node->start + node->end) / 2;
        if (index <= mid) {
            update(node->left, index);
        }
        else {
            update(node->right, index);
        }
        node->val = node->left->val + node->right->val;

    }
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        vector<long long> prefix(nums.size() + 1, 0);
        long long ttl = 0;
        for (int i = 0; i < nums.size(); i++) {
            ttl += (long long)nums[i];
            prefix[i + 1] = ttl;
        }
        map<long long, int> mp;
        for (int i = 0; i < prefix.size(); i++) {
            mp[prefix[i]]++;
        }
        vector<int> vals;
        unordered_map<long long, int> index;
        for (auto& e : mp) {
            index.emplace(e.first, vals.size());
            vals.push_back(e.second);
        }
        root = build(vals, 0, vals.size() - 1);
        int res = 0;
        update(root, index[0]);
        for (int i = 1; i < prefix.size(); i++) {
            long long u = upper + prefix[i - 1];
            long long l = lower + prefix[i - 1];
            //find all j that's after i so that prefix[j] is between l and u
            auto it1 = mp.lower_bound(l); //>=l
            auto it2 = mp.upper_bound(u); //>u
            if (it1 == mp.end()) {
                update(root, index[prefix[i]]);
                continue;
            }
            if (it2 == mp.begin()) {//all element bigger than u, no element is illigible
                update(root, index[prefix[i]]);
                continue;
            }
            int q2 = 0;
            if (it2 == mp.end()) {//no element bigger than u, all element possible
                it2--;
                q2 = index[it2->first];
            }
            else {
                q2 = index[it2->first] - 1;
            }
            int q1 = index[it1->first];
            //cout << "querying " <<u<< l << "/" <<it1->first << "," << it2->first << endl;
            if (q1 <= q2) {
                res += query(root, q1, q2);
            }

            //cout << "res " << res << endl;
            //update: remove i from the segment tree           
            update(root, index[prefix[i]]);
        }
        return res;
    }
};