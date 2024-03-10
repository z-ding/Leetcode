class Solution {
public:
    class trieNode {
    public:
        unordered_map<char, trieNode*> children;
        bool isEnd;
        int count;
        trieNode(unordered_map<char, trieNode*>& c, bool e, int cou) {//constructor
            children = c;
            isEnd = e;
            count = cou;
        }
    };
    //initialize an empty trie
    unordered_map<char, trieNode*> c;
    trieNode* root = new trieNode(c, false, 0);
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
                    trieNode* n = new trieNode(ch, end, 1);
                    curNode->children.emplace(word[i], n);
                    curNode = curNode->children[word[i]];
                    markend = true;
                }
                return;
            }
            else {//found this index in current node's children, go to this children and check next index              
                curNode = curNode->children[word[index]];
                curNode->count++;
                index++;
            }
            if (index == word.size() && !markend) { //whole word exist in the trie, mark the curnode as end
                curNode->isEnd = true;
            }
        }
        //cout << word << "inserted" << endl;
        //viewTrie(root);
    }
    bool startWith(string& word) {
        int index = 0;
        trieNode* curNode = root;
        while (index < word.size()) {
            //cout << index << endl;
            //cout << curNode->children[word[index]] -> count << endl;
            if (curNode->children.find(word[index]) == curNode->children.end() || curNode->children[word[index]]->count == 0) {//not matching
                //cout <<"false" << endl;
                return false;
            }
            curNode = curNode->children[word[index]];
            index++;

        }
        //if (curNode->isEnd) {//for search 
            //return true;
        //}
        return true;
    }
    void remove(string& word) {
        int index = 0;
        trieNode* curNode = root;
        while (index < word.size()) {
            curNode = curNode->children[word[index]];
            curNode->count--;
            index++;

        }
    }
    void viewTrie(trieNode* node) {
        if (node == nullptr) {
            return;
        }
        cout << node->count << endl;
        cout << "children:" << endl;
        for (auto& e : node->children) {
            cout << e.first << endl;
            viewTrie(e.second);
        }
    }
    vector<string> shortestSubstrings(vector<string>& arr) {
        for (auto& x : arr) {
            for (int i = 0; i < x.size(); i++) {
                for (int j = i; j < x.size(); j++) {
                    string s = x.substr(i, j - i + 1);
                    insert(s);
                }
            }
        }
        //cout <<"original trie" << endl;
        //viewTrie(root);

        vector<string> res;
        for (auto& x : arr) {
            for (int i = 0; i < x.size(); i++) {
                for (int j = i; j < x.size(); j++) {
                    string s = x.substr(i, j - i + 1);
                    remove(s);
                }
            }
            //cout << "removed " << x << endl;
            //viewTrie(root);
            int len = 10000;
            int left = -1;
            int right = -1;
            for (int i = 0; i < x.size(); i++) {
                for (int j = i; j < x.size(); j++) {
                    if (j - i + 1 > len) break;
                    string s = x.substr(i, j - i + 1);
                    if (!startWith(s)) {
                        if (j - i + 1 < len) {
                            len = j - i + 1;
                            left = i;
                            right = j;
                        }
                        else if (j - i + 1 == len) {
                            bool rep = false;
                            int d = 0;
                            for (int cur = i; cur <= j; cur++) {
                                int comp = left + d;
                                if (x[cur] < x[comp]) {
                                    rep = true;
                                    break;
                                }
                                else if (x[cur] > x[comp]) break;
                                d++;
                            }
                            if (rep) {
                                left = i;
                                right = j;
                            }
                        }
                        break;
                    }
                }
            }
            if (len < 10000) res.push_back(x.substr(left, len));
            else res.push_back("");
            for (int i = 0; i < x.size(); i++) {
                for (int j = i; j < x.size(); j++) {
                    string s = x.substr(i, j - i + 1);
                    insert(s);
                }
            }
            //cout <<"insert back " << x << endl;
            //viewTrie(root); 
        }
        return res;
    }
};