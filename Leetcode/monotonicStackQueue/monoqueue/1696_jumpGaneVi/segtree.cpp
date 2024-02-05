class Solution {
public:
    class SegTreeNode {
    public:
        int start;
        int end;
        int sum;//max
        SegTreeNode* left;
        SegTreeNode* right;
        SegTreeNode(int s, int e, int val) {//constructor
            start = s;
            end = e;
            sum = val;
            left = nullptr;
            right = nullptr;
        }

    };

    inline SegTreeNode* buildTree(int start, int end, vector<int>& nums) {//build tree
        if (start == end) {
            return new SegTreeNode(start, start, nums[start]);//a leaf node
        }
        int mid = (start + end) / 2;
        SegTreeNode* leftSubTree = buildTree(start, mid, nums);
        SegTreeNode* rightSubTree = buildTree(mid + 1, end, nums);
        SegTreeNode* parent = new SegTreeNode(start, end, max(leftSubTree->sum, rightSubTree->sum));
        parent->left = leftSubTree;
        parent->right = rightSubTree;
        return parent;
    }

    inline int querySum(SegTreeNode* root, int i, int j) {//i and j are start and end range of the query. i<j
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
            return max(querySum(root->left, i, mid), querySum(root->right, mid + 1, j));
        }
    }
    inline void updateValue(int index, int val, SegTreeNode* root) {
        //similar to binary search
        if (root->start == root->end && root->start == index) {//found the leaf node
            root->sum = val;
            return;
        }
        int mid = (root->start + root->end) / 2;
        if (index <= mid) {
            updateValue(index, val, root->left);
        }
        else {
            updateValue(index, val, root->right);
        }
        root->sum = max(root->left->sum, root->right->sum); //update parent's sum since child's value is updated
        return;
    }
    SegTreeNode* root;
    int maxResult(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> dp(n, -1000000000);
        dp.back() = nums.back();
        root = buildTree(0, n - 1, dp);
        //max score of getting to the last index via i
        for (int i = n - 2; i >= 0; i--) {
            int l = i + 1;
            int r = min(i + k, n - 1);
            int nextjump = querySum(root, l, r);//jump to this place will guarantee highest score
            dp[i] = nums[i] + nextjump;
            updateValue(i, dp[i], root);
        }
        return dp[0];
    }
};