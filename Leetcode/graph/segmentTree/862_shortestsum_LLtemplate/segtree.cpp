class Solution {
public:
    class SegTreeNode {
    public:
        int start;
        int end;
        long long sum;//min
        SegTreeNode* left;
        SegTreeNode* right;
        SegTreeNode(int s, int e, long long val) {//constructor
            start = s;
            end = e;
            sum = val;
            left = nullptr;
            right = nullptr;
        }

    };
    inline SegTreeNode* buildTree(int start, int end, vector<long long>& nums) {//build tree
        if (start == end) {
            return new SegTreeNode(start, start, nums[start]);//a leaf node
        }
        int mid = (start + end) / 2;
        SegTreeNode* leftSubTree = buildTree(start, mid, nums);
        SegTreeNode* rightSubTree = buildTree(mid + 1, end, nums);
        SegTreeNode* parent = new SegTreeNode(start, end, min(leftSubTree->sum, rightSubTree->sum));
        parent->left = leftSubTree;
        parent->right = rightSubTree;
        return parent;
    }
    inline long long querySum(SegTreeNode* root, int i, int j) {//i and j are start and end range of the query. i<j
        if (i > j) return LLONG_MAX;
        if (root->end == j && root->start == i) {//found the leaf node
            return root->sum;
        }
        int mid = (root->start + root->end) / 2;
        if (j <= mid) {//whole range falls in left subtree
            return querySum(root->left, i, j);
        }
        else if (i > mid) {
            return querySum(root->right, i, j);//whole range falls in right subtree
        }
        else { // part of the range falls in left and part in right
            return min(querySum(root->left, i, mid), querySum(root->right, mid + 1, j));
        }
    }
    void bsearch(SegTreeNode* root, int l, int r, long long ub, int& ans, vector<long long>& p) {
        if (l > r) return;
        int mid = (l + r) / 2;
        if (p[mid] <= ub) ans = max(ans, mid);
        auto cur = querySum(root, mid + 1, r);
        if (cur <= ub) {//answer exists in mid +1 ...r, no need to search l..mid part
            bsearch(root, mid + 1, r, ub, ans, p);
        }
        else bsearch(root, l, mid - 1, ub, ans, p);


    }
    int shortestSubarray(vector<int>& nums, int k) {
        vector<long long> prefix = { 0 };
        long long sum = 0;
        for (auto& x : nums) {
            sum += (long long)x;
            prefix.push_back(sum);
        }
        auto root = buildTree(0, nums.size() - 1, prefix);
        int res = 1000000;
        for (int i = 1; i < prefix.size(); i++) {
            long long upperbound = prefix[i] - k;
            //cout << i << ":" << upperbound << endl;
            //find the biggest idx j where j< i && prefix[j] <= upperbound
            int idx = -1;
            bsearch(root, 0, i - 1, upperbound, idx, prefix);
            if (idx != -1) res = min(res, i - idx);
        }
        if (res == 1000000) return -1;
        return res;
    }
};