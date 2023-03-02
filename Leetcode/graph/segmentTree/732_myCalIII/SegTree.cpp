class MyCalendarThree {
public:
    int max_count = 0;
    class SegTreeNode {
    public:
        int interval_start;
        int interval_end;
        int count;//number of events
        int split; //interval splited at which location. if not splited, -1 => a leaf ndoe
        SegTreeNode* left;
        SegTreeNode* right;
        SegTreeNode(int s, int e, int val) {//constructor
            interval_start = s;
            interval_end = e;
            count = val;
            split = -1;
            left = nullptr;
            right = nullptr;
        }
    };
    void build(int start, int end, SegTreeNode* root) {
        if (root->split != -1) {//this is not a leaf node, we need to find the correct leaf node to insert our node
            //e.g. current interval [2,10] split at 5
            if (start >= root->split) {//new interval falls on the right subtree
                build(start, end, root->right);//go right
            }
            else if (end <= root->split) {//new interval falls on the left subtree
                build(start, end, root->left);
            }
            else {//new interval falls partially in the left and partially in the right subtree
                //e.g. new interval: [4,6]
                //find [4,5] in left subtree and [5,6] in right subtree
                build(start, root->split, root->left);
                build(root->split, end, root->right);
            }
            return;
        }
        //now we are at a leaf node, we can split this leaf node 
        //e.g. leaf node: [2,10] split at -1
        if (root->interval_start == start && root->interval_end == end) {
            //new interval [2,10], no need to split, increment root count
            root->count++;
            max_count = max(max_count, root->count);
        }
        else if (root->interval_start == start) {
            //new interval [2,4],split current interval into [2,4] &[4,10], increment the count of [2,4]
            root->split = end;
            root->left = new SegTreeNode(start, end, root->count + 1);
            root->right = new SegTreeNode(end, root->interval_end, root->count);
            max_count = max(max_count, root->count + 1);
        }
        else if (root->interval_end == end) {
            //new interval [8,10] split current interval into [2,8] &[8,10], increment the count of [8,4]
            root->split = start;
            root->left = new SegTreeNode(root->interval_start, start, root->count);
            root->right = new SegTreeNode(start, end, root->count + 1);
            max_count = max(max_count, root->count + 1);
        }
        else {
            //new interval [3,7] split current interval into [2,3] &[3,10] and put the new interval recursively in [3,10]
            root->split = start;
            root->left = new SegTreeNode(root->interval_start, start, root->count);
            root->right = new SegTreeNode(start, root->interval_end, root->count);
            build(start, end, root->right);
        }
    }
    SegTreeNode* root = new SegTreeNode(0, 1000000000, 0);
    MyCalendarThree() {

    }

    int book(int startTime, int endTime) {
        build(startTime, endTime, root);
        return max_count;
    }
};

/**
 * Your MyCalendarThree object will be instantiated and called as such:
 * MyCalendarThree* obj = new MyCalendarThree();
 * int param_1 = obj->book(startTime,endTime);
 */