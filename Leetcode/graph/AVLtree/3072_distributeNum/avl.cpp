class Solution {
public:
    struct AVL {
        struct AVLnode {
            int element;
            AVLnode* left;
            AVLnode* right;
            int height;
            int size;//number of nodes and child nodes
            AVLnode(int x, AVLnode* l, AVLnode* r, int h = 0, int s = 1) : element{ x }, left{ l }, right{ r }, height{ h }, size{ s } {}
        };

        AVLnode* root;
        AVL() {
            root = nullptr;
        }
        int height(AVLnode* t) {
            return t == nullptr ? -1 : t->height;
        }
        void updateSize(AVLnode* node) {
            if (node != nullptr) {
                node->size = getSize(node->left) + getSize(node->right) + 1;
            }
        }
        int getSize(AVLnode* node) {
            return (node != nullptr) ? node->size : 0;
        }
        void insert(int x, AVLnode*& t) {
            if (t == nullptr)
                t = new AVLnode(x, nullptr, nullptr);
            else if (x <= t->element)
                insert(x, t->left);
            else if (t->element < x)
                insert(x, t->right);
            updateSize(t);
            balance(t);
        }

        void balance(AVLnode*& t) {

            if (t == nullptr) return;
            if (height(t->left) - height(t->right) > 1) {
                if (height(t->left->left) >= height(t->left->right)) rotateWithLeftChild(t);
                else rotateWithrightLeftChild(t);
            }
            else {
                if (height(t->right) - height(t->left) > 1) {
                    if (height(t->right->right) >= height(t->right->left)) rotateWithRightChild(t);
                    else rotateWithWithLeftRightChild(t);
                }
            }
            t->height = max(height(t->left), height(t->right)) + 1;
            updateSize(t);
        }

        void rotateWithLeftChild(AVLnode*& k2) {
            AVLnode* k1 = k2->left;
            k2->left = k1->right;
            k1->right = k2;
            k2->height = max(height(k2->left), height(k2->right)) + 1;
            k1->height = max(height(k1->left), k2->height) + 1;
            updateSize(k2);
            updateSize(k1);
            k2 = k1;
        }
        void rotateWithRightChild(AVLnode*& k2) {
            AVLnode* k1 = k2->right;
            k2->right = k1->left;
            k1->left = k2;
            k2->height = max(height(k2->right), height(k2->left)) + 1;
            k1->height = max(height(k1->right), k2->height) + 1;
            updateSize(k2);
            updateSize(k1);
            k2 = k1;
        }

        void rotateWithrightLeftChild(AVLnode*& k3) {
            rotateWithRightChild(k3->left);
            rotateWithLeftChild(k3);
        }

        void rotateWithWithLeftRightChild(AVLnode*& k3) {
            rotateWithLeftChild(k3->right);
            rotateWithRightChild(k3);
        }
        int greaterCount(AVLnode* node, int key) {
            if (node == nullptr) {
                return 0;
            }
            if (key < node->element) {
                return getSize(node->right) + 1 + greaterCount(node->left, key);
            }
            else {
                return greaterCount(node->right, key);
            }
        }
        void traverse(AVLnode* node) {
            if (node == nullptr) return;
            traverse(node->left);
            cout << node->element << "," << node->size << endl;
            traverse(node->right);
        }
    };
    vector<int> resultArray(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return nums;
        vector<int> arr1, arr2;
        AVL tree1, tree2;
        arr1.push_back(nums[0]);
        arr2.push_back(nums[1]);
        tree1.insert(nums[0], tree1.root);
        tree2.insert(nums[1], tree2.root);
        for (int i = 2; i < n; i++) {
            int cnt1 = tree1.greaterCount(tree1.root, nums[i]);
            int cnt2 = tree2.greaterCount(tree2.root, nums[i]);
            //cout << nums[i] << ":" << cnt1 << " " << cnt2 << endl;
            //cout <<"tra" << endl;
            //tree2.traverse(tree2.root);
            if (cnt1 > cnt2) {
                arr1.push_back(nums[i]);
                tree1.insert(nums[i], tree1.root);
            }
            else if (cnt1 < cnt2) {
                arr2.push_back(nums[i]);
                tree2.insert(nums[i], tree2.root);
            }
            else {
                int size1 = tree1.getSize(tree1.root), size2 = tree2.getSize(tree2.root);
                //cout << " " << size1 << " " << size2 << endl;
                if (size1 > size2) {
                    arr2.push_back(nums[i]);
                    tree2.insert(nums[i], tree2.root);
                }
                else {
                    arr1.push_back(nums[i]);
                    tree1.insert(nums[i], tree1.root);
                }
            }
        }
        arr1.insert(arr1.end(), arr2.begin(), arr2.end());
        return arr1;
    }
};