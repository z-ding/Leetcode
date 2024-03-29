class Solution {
public:
    class trieNode {
    public:
        unordered_map<char, trieNode*> children;
        bool isEnd;
        trieNode(unordered_map<char, trieNode*>& c, bool e) {//constructor
            children = c;
            isEnd = e;
        }
    };
    //initialize an empty trie
    unordered_map<char, trieNode*> c;
    trieNode* root = new trieNode(c, false);

    void viewTrie(trieNode* node) {
        if (node == nullptr) {
            return;
        }
        for (auto& e : node->children) {
            cout << e.first << endl;
            viewTrie(e.second);
        }
    }
    void insert(string& word) {
        int index = 0;
        trieNode* curNode = root;
        bool markend = false;
        while (index < word.size()) {
            if (curNode->children.find(word[index]) == curNode->children.end()) {
                //this index doesn't exist in current node's children, create a new subtree here
                //put the rest of the word in this new subtree
                for (int i = index; i < word.size(); i++) {
                    unordered_map<char, trieNode*> ch;
                    bool end = false;
                    if (i == word.size() - 1) {
                        end = true;
                    }
                    trieNode* n = new trieNode(ch, end);
                    curNode->children.emplace(word[i], n);
                    curNode = curNode->children[word[i]];
                    markend = true;
                }
                return;
            }
            else {//found this index in current node's children, go to this children and check next index
                curNode = curNode->children[word[index]];
                index++;
            }
            if (index == word.size() && !markend) { //whole word exist in the trie, mark the curnode as end
                curNode->isEnd = true;
            }
        }
        //cout << word << "inserted" << endl;
        //viewTrie(root);
    }
    bool search(string& word) {
        int index = 0;
        trieNode* curNode = root;
        while (index < word.size()) {
            //cout << index << endl;
            if (curNode->children.find(word[index]) == curNode->children.end()) {//not matching
                return false;
            }
            curNode = curNode->children[word[index]];
            index++;

        }
        if (curNode->isEnd) {
            return true;
        }
        return false;
    }
    bool startsWith(string& prefix) {
        int index = 0;
        trieNode* curNode = root;
        while (index < prefix.size()) {
            //cout << index << endl;
            if (curNode->children.find(prefix[index]) == curNode->children.end()) {//not matching
                return false;
            }
            curNode = curNode->children[prefix[index]];
            index++;

        }
        return true;
    }
    int lcp(string& prefix) {
        int index = 0;
        trieNode* curNode = root;
        while (index < prefix.size()) {
            //cout << index << endl;
            if (curNode->children.find(prefix[index]) == curNode->children.end()) {//not matching
                return index;
            }
            curNode = curNode->children[prefix[index]];
            index++;
        }
        return index;
    }
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
        for (auto& x : arr2) {
            string s = to_string(x);
            insert(s);
        }
        int res = 0;
        for (auto& x : arr1) {
            string s = to_string(x);
            res = max(res, lcp(s));
        }
        return res;
    }
};