class Trie {
public:
    class node {
    public:
        bool isEnd;
        vector<node*> children;
        node(vector<node*>& c, bool e) {
            children = c;
            isEnd = e;
        }
    };
    node* root;
    Trie() {
        vector<node*> v(26, nullptr);
        root = new node(v, false);
    }

    void insert(string word) {
        int idx = 0;
        auto curNode = root;
        while (idx < word.size()) {
            if (curNode->children[word[idx] - 'a'] == nullptr) {
                for (int i = idx; i < word.size(); i++) {
                    vector<node*> v(26, nullptr);
                    bool e = false;
                    if (i == word.size() - 1) e = true;
                    auto nextNode = new node(v, e);
                    curNode->children[word[i] - 'a'] = nextNode;
                    curNode = nextNode;
                }
                break;
            }
            else {
                curNode = curNode->children[word[idx] - 'a'];
                idx++;
                if (idx == word.size()) curNode->isEnd = true;
            }
        }
    }

    bool search(string word) {
        //cout << word << endl;
        auto curNode = root;
        for (int i = 0; i < word.size(); i++) {
            //cout << i << endl;
            if (curNode->children[word[i] - 'a'] == nullptr) return false;
            curNode = curNode->children[word[i] - 'a'];
        }
        //cout <<"end" << endl;
        if (curNode->isEnd) return true;
        return false;
    }

    bool startsWith(string prefix) {
        auto curNode = root;
        for (int i = 0; i < prefix.size(); i++) {
            if (curNode->children[prefix[i] - 'a'] == nullptr) return false;
            curNode = curNode->children[prefix[i] - 'a'];
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */