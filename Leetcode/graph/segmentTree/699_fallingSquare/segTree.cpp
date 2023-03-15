class Solution {
public:
    class Node {
    public:
        int start;
        int end;
        int height;
        int split;
        Node* left;
        Node* right;
        Node(int s, int e, int h, int _s) {
            start = s;
            end = e;
            height = h;
            split = _s;
            left = nullptr;
            right = nullptr;
        }
    };

    Node* root = new Node(0, INT_MAX, 0, -1);
    int maxh = 0;
    int querymax(Node* node, int s, int e) {
        if (node->start == s && node->end == e) {
            return node->height;
        }
        if (s >= node->split) {
            return querymax(node->right, s, e);
        }
        else if (e <= node->split) {
            return querymax(node->left, s, e);
        }
        else {
            return max(querymax(node->right, node->split, e), querymax(node->left, s, node->split));
        }
    }
    void update(Node* node, int s, int e, int value) {
        if (node->start == s && node->end == e) {
            node->height = value;
            return;
        }
        if (s >= node->split) {
            update(node->right, s, e, value);
        }
        else if (e <= node->split) {
            update(node->left, s, e, value);
        }
        else {
            update(node->left, s, node->split, value);
            update(node->right, node->split, e, value);
        }
        //since this node is now splited to two node with diff heights, mark it as -1
        node->end = -1;
    }
    void build(Node* node, int s, int e, int h) {
        if (node->split != -1) {
            if (e <= node->split) {
                build(node->left, s, e, h);
            }
            else if (s >= node->split) {
                build(node->right, s, e, h);
            }
            else {// s < split < e, build [s,split] on left subtree and [split, e] on right subtree, split is either the left side of a square or the right side of a square
                build(node->left, s, node->split, h);
                build(node->right, node->split, e, h);
            }
            return;
        }
        //leaf node

        if (s == node->start && e == node->end) {//completely covered by a range, update the height of this range
            node->height += h;
        }
        else if (node->start == s) {//split node to [start, e] and [e,end]
            node->split = e;
            node->left = new Node(node->start, e, node->height + h, -1);
            node->right = new Node(e, node->end, node->height, -1);
        }
        else if (node->end == e) {//split node to [start, s] and [s,end]
            node->split = s;
            node->left = new Node(node->start, s, node->height, -1);
            node->right = new Node(s, node->end, node->height + h, -1);
        }
        else {//node -> start < s < e < node->end
            //split the node at s to [start, s ] and [s, end], then build tree on [s,end]
            node->split = s;
            node->left = new Node(node->start, s, node->height, -1);
            node->right = new Node(s, node->end, node->height, -1);
            build(node->right, s, e, h);
        }

    }

    void view(Node* node) {
        if (node == nullptr) {
            return;
        }
        cout << node->start << "," << node->end << " s " << node->split << ":" << node->height << endl;
        view(node->left);
        view(node->right);
    }
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        vector<int> res(positions.size(), 0);
        for (int i = 0; i < positions.size(); i++) {
            build(root, positions[i][0], positions[i][0] + positions[i][1], positions[i][1]);
            int cur = querymax(root, positions[i][0], positions[i][0] + positions[i][1]);
            //cout << cur << endl;
            maxh = max(maxh, cur);
            update(root, positions[i][0], positions[i][0] + positions[i][1], cur);
            //cout << i << "built" << endl;
            view(root);
            res[i] = maxh;
        }
        return res;

    }
};