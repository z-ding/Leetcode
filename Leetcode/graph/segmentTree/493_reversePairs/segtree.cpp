class Solution {
public:
    class Node {//seg tree node
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
    Node* build(vector<int>& nums, int s, int e) {
        if (s == e) {
            return new Node(s, s, nums[s]);
        }
        int mid = (s + e) / 2;
        Node* l = build(nums, s, mid);
        Node* r = build(nums, mid + 1, e);
        Node* parent = new Node(s, e, l->val + r->val);
        parent->left = l;
        parent->right = r;
        return parent;
    }
    void update(Node* node, int s, int e) {
        if (node->start == s && node->end == e) {
            if (node->val > 0) {
                node->val--;
            }
            return;
        }
        int mid = (node->start + node->end) / 2;
        if (e <= mid) {
            update(node->left, s, e);
        }
        else if (s > mid) {
            update(node->right, s, e);
        }
        else {
            update(node->left, s, mid);
            update(node->right, mid + 1, e);
        }
        node->val = node->left->val + node->right->val;
        return;
    }
    int query(Node* node, int s, int e) {
        if (node->start == s && node->end == e) {
            return node->val;
        }
        int mid = (node->start + node->end) / 2;
        if (e <= mid) {
            return query(node->left, s, e);
        }
        else if (s > mid) {
            return query(node->right, s, e);
        }
        else {
            return query(node->left, s, mid) + query(node->right, mid + 1, e);
        }

    }
    void viewtree(Node* node) {
        if (node == nullptr) {
            return;
        }
        cout << node->start << "," << node->end << ":" << node->val << endl;
        viewtree(node->left);
        viewtree(node->right);
    }
    int reversePairs(vector<int>& nums) {
        map<int, int> mp;
        for (int i = 0; i < nums.size(); i++) {
            mp[nums[i]]++;
        }
        vector<int> count;
        unordered_map<int, int> ref;
        for (auto& e : mp) {//maintain a hash map of value: index in count
            ref[e.first] = count.size();
            count.push_back(e.second);
        }
        Node* root = build(count, 0, count.size() - 1);
        //viewtree(root);
        int res = 0;
        for (int i = 0; i < nums.size(); i++) {
            int limit = nums[i] / 2;
            if (nums[i] % 2 == 0 || nums[i] < 0) {
                limit--;
            }
            //find out the key in mp that is <=limit 
            auto it = mp.upper_bound(limit);//> limit
            //cout << i << "limit " << limit << endl;
            if (it != mp.begin()) {//not the smallest item in mp
                it--; //<= limit
                int number = it->first;//index in count ref[number]
                res = res + query(root, 0, ref[number]);
                if (number >= nums[i]) {
                    res--;
                }
                //cout << i << "," << ref[number] << ":" <<res << endl;
            }
            update(root, ref[nums[i]], ref[nums[i]]);
        }
        return res;
    }
};