class NumArray {
public:
    class SegTreeNode {
    public:
        int start;
        int end;
        int sum;//can be max/min according to the requirement
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

    /*
    leaf nodes of the segment tree is the original array, the parents are the sum of left node and right node. The tree has to be balanced so that the height is logN
    e.g. [1,3,5] the tree can be visualized as follows x-y represents the range in the original array/ We will build it in a recursive way
            9
           0-2
        4       5
       0-1     2-2
    1       3
   0-0     1-1
    */
    inline SegTreeNode* buildTree(int start, int end, vector<int>& nums) {//build tree
        if (start == end) {
            return new SegTreeNode(start, start, nums[start]);//a leaf node
        }
        int mid = (start + end) / 2;
        SegTreeNode* leftSubTree = buildTree(start, mid, nums);
        SegTreeNode* rightSubTree = buildTree(mid + 1, end, nums);
        SegTreeNode* parent = new SegTreeNode(start, end, leftSubTree->sum + rightSubTree->sum);
        parent->left = leftSubTree;
        parent->right = rightSubTree;
        return parent;
    }

    /*
    inline void viewTree(SegTreeNode* root){
        if (root == nullptr){
            return;
        }
        cout << root->start << "-" << root -> end << ":" <<root -> sum << endl;
        viewTree(root -> left);
        viewTree(root -> right);
    }*/

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
        root->sum = root->left->sum + root->right->sum; //update parent's sum since child's value is updated
        return;
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
            return querySum(root->left, i, mid) + querySum(root->right, mid + 1, j);
        }
    }
    SegTreeNode* tree;
    NumArray(vector<int>& nums) {
        tree = buildTree(0, nums.size() - 1, nums);
        //viewTree(tree);
    }

    void update(int index, int val) {
        updateValue(index, val, tree);
        //viewTree(tree);
    }

    int sumRange(int left, int right) {
        return querySum(tree, left, right);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */