class Solution {
public:
    class Node {
    public:
        int low;
        int high;
        int height;
        int split;
        Node* left;
        Node* right;
        Node(int l, int h, int hei, int s) {
            low = l;
            high = h;
            height = hei;
            split = s;
            left = nullptr;
            right = nullptr;
        }
    };

    Node* root = new Node(0, INT_MAX, 0, -1); //default: no split
    void buildTree(Node* node, int start, int end, int height) {
        if (node->split != -1) {//not a leaf node, find the leaf node where we should attach the node
            if (end <= node->split) {//go to left
                buildTree(node->left, start, end, height);
            }
            else if (start >= node->split) {//go to right
                buildTree(node->right, start, end, height);
            }
            else {
                buildTree(node->left, start, node->split, height);
                buildTree(node->right, node->split, end, height);
            }
            return;
        }
        //a leaf node found
        if (node->low == start && node->high == end) {//covers the same range as the node
            node->height = max(node->height, height);//no need to split, update the height
        }
        else if (node->low == start) {//split at end
            node->split = end;
            //create new node for [start, end] and [end,high]
            Node* l = new Node(start, end, max(node->height, height), -1);
            Node* r = new Node(end, node->high, node->height, -1);
            node->left = l;
            node->right = r;
        }
        else if (node->high == end) {//split at start
            node->split = start;
            //create new node for [low start] and [start,high]
            Node* l = new Node(node->low, start, node->height, -1);
            Node* r = new Node(start, node->high, max(node->height, height), -1);
            node->left = l;
            node->right = r;
        }
        else {//range covered by the node, split at start (split at end is also ok)
            node->split = start;
            //create new node for [low, start] and [start, high]
            Node* l = new Node(node->low, start, node->height, -1);
            Node* r = new Node(start, node->high, node->height, -1);
            node->left = l;
            node->right = r;
            //now, range should fall in [start,high] build the tree recursively for range[start,end]
            buildTree(node->right, start, end, height);
        }
        return;
    }
    typedef tuple<int, int, int> t;
    vector<t> leaf; //save all leaf nodes
    void viewTree(Node* node) {
        if (node == nullptr) {
            return;
        }
        //cout << node-> low <<"," << node -> high << " split" << node-> split << ":" << node ->height << endl;//for debug only
        if (node->split == -1) {
            t le = make_tuple(node->low, node->high, node->height);
            leaf.emplace_back(le);
        }
        viewTree(node->left);
        viewTree(node->right);
    }
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        vector<vector<int>> res;
        if (buildings.size() == 1) {
            vector<int> v = { buildings[0][0],buildings[0][2] };
            res.emplace_back(v);
            v = { buildings[0][1],0 };
            res.emplace_back(v);
            return res;
        }
        for (int i = 0; i < buildings.size(); i++) {
            buildTree(root, buildings[i][0], buildings[i][1], buildings[i][2]);
        }
        viewTree(root);
        //the interval is sorted in leaf and non of them is overlapping, now merge the adjacent interval with same height and push the intervals to the res
        if (get<2>(leaf[0]) != 0) {//add first interval to result only if the height >0
            vector<int> v = { get<0>(leaf[0]),get<2>(leaf[0]) };
            res.emplace_back(v);
        }
        for (int i = 1; i < leaf.size(); i++) {
            int s = get<0>(leaf[i]);
            int e = get<1>(leaf[i]);
            int h = get<2>(leaf[i]);
            //cout << s <<"," <<  e << ":" << h << endl;
            if (res.size() == 0) {
                vector<int> v = { s,h };
                res.emplace_back(v);
                continue;
            }
            if (h != res.back()[1]) {//add to res since a new height is found
                vector<int> v = { s,h };
                res.emplace_back(v);
            }
        }
        if (res.back()[0] == 2147483646 && res.back()[1] != 0) {// add the ending for intmax
            vector<int> v = { 2147483647,0 };
            res.emplace_back(v);
        }
        return res;
    }
};