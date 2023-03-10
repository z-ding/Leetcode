class Solution {
public:
    class Node {
    public:
        int count;
        int start;
        int end;
        Node* left;
        Node* right;
        Node(int s, int e, int val) {
            start = s;
            end = e;
            count = val;
            left = nullptr;
            right = nullptr;
        }
    };

    Node* buildTree(vector<int>& v, int start, int end) {
        //cout << "build " << start << "," << end << endl;
        if (start == end) {
            return new Node(start, start, v[start]);
        }
        int mid = (start + end) / 2;
        Node* l = buildTree(v, start, mid);
        Node* r = buildTree(v, mid + 1, end);
        Node* parent = new Node(start, end, l->count + r->count);
        parent->left = l;
        parent->right = r;
        return parent;
    }
    void viewTree(Node* node) {
        if (node == nullptr) {
            return;
        }
        cout << node->start << "-" << node->end << ":" << node->count << endl;
        viewTree(node->left);
        viewTree(node->right);

        return;
    }

    int query(Node* node, int s, int e) {
        if (s == node->start && e == node->end) {
            return node->count;
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
    void update(Node* node, int index) {
        if (index == node->start && index == node->end) {
            node->count--;
            return;
        }
        int mid = (node->start + node->end) / 2;
        if (index <= mid) {
            update(node->left, index);
        }
        else {
            update(node->right, index);
        }
        node->count = node->left->count + node->right->count;
    }
    vector<int> countSmaller(vector<int>& nums) {
        vector<int> res(nums.size(), 0);
        map<int, int> mp;//number: freq
        for (int i = 0; i < nums.size(); i++) {
            mp[nums[i]]++;
        }
        /*
        e.g [5,2,6,1,5]
        the map look like:
        1:1
        2:1
        5:2
        6:1
        for the first 5, we will return 1+1=2, then we should decrement the amount of 5 so that for 6 it will only get the 5 after it. so the map will look like
        1:1
        2:1
        5:1
        6:1
        if we do a running sum every time, we will get a TLE. so we should use a segment tree to store the running sum dynamicly
        we can use a vector to store the appearing time of each number and maintain a hash map to remember the value for each index
        initially, our vector will be
        index: 0 1 2 3
               1 1 2 1
        the hashmap will be :{1:0, 2:1, 5:2, 6:3}
        segment tree will look like
                       5
                    (0-3)
             2                3
           (0-1)            (2-3)
        1       1       2       1
      (0-0)   (1-1)   (2-2)   (3-3)
        when we perform the first query, we will look for the index of 5 (2), so we should get the value of 0-1 which is 2. now we will decrement value of 2-2 to 1 and update the tree. next we should get the value for 2, since the index of 2 is 1, it means we should look for 0-0 in the tree and then decrement value of 1-1 to 0

        */
        //convert the mp to vector and hashmap
        vector<int> freq;
        unordered_map<int, int> ref;
        for (auto& e : mp) {
            ref.emplace(e.first, freq.size());
            freq.push_back(e.second);
        }
        Node* root = buildTree(freq, 0, freq.size() - 1);
        //viewTree(root);
        for (int i = 0; i < nums.size(); i++) {
            int queryindex = ref[nums[i]];
            if (queryindex > 0) {
                res[i] = query(root, 0, queryindex - 1);
            }
            update(root, queryindex);
            //cout << i << " check update " << endl;
            //viewTree(root);
        }
        return res;
    }
};