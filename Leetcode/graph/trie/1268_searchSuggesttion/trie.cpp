class Solution {
public:
    class trieNode {
    public:
        map<char, trieNode*> children;
        bool isEnd;
        trieNode(map<char, trieNode*>& c, bool e) {//constructor
            children = c;
            isEnd = e;
        }
    };
    map<char, trieNode*> c;
    trieNode* root = new trieNode(c, false); //a placeholder rootnode
    void insert(string word) {
        int index = 0;
        trieNode* curNode = root;
        bool markend = false;
        while (index < word.size()) {
            if (curNode->children.find(word[index]) == curNode->children.end()) {
                //this index doesn't exist in current node's children, create a new subtree here
                //put the rest of the word in this new subtree
                for (int i = index; i < word.size(); i++) {
                    map<char, trieNode*> ch;
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
    }
    void viewTrie(trieNode* node) {
        if (node == nullptr) {
            return;
        }
        for (auto& e : node->children) {
            cout << e.first << endl;
            viewTrie(e.second);
        }
    }
    void firstthree(string& b, vector<string>& v, trieNode* node) {
        //if (v.size() == 3){
            //return;
        //}
        if (node == nullptr) {
            return;
        }

        for (auto& e : node->children) {
            if (v.size() < 3) {
                b = b + e.first;
                //cout << b << endl;
                if (e.second->isEnd) {
                    v.push_back(b);
                    firstthree(b, v, e.second);
                }
                else {
                    firstthree(b, v, e.second);
                }
                b.pop_back();
            }
        }
    }
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        //insert word in products into the trie
        for (int i = 0; i < products.size(); i++) {
            insert(products[i]);
        }
        //viewTrie(root);
        vector<vector<string>> res;
        //search
        trieNode* curNode = root;
        for (int i = 0; i < searchWord.size(); i++) {
            vector<string> v;
            if (curNode->children.find(searchWord[i]) == curNode->children.end()) {
                //no word starts with root[index], no need to continue
                for (int j = i; j < searchWord.size(); j++) {
                    res.push_back(v);
                }
                return res;
            }
            /*there are some words starting with searchWord[i]
            e.g. we are searching for ape in the trie below. when we type a, we should get
            apple, ape and aqua. when we type p, we should get apple and ape,
            finally when we type e, we should get ape only
                        root
                 a                       b
                / \ \                  ......
                p  q t
               /\   \
               p e   u
              /       \
              l         a
             /
             e

            */
            //we should move the curNode->children[searchWord[i]] which is for the word start with a
            curNode = curNode->children[searchWord[i]];
            string b = searchWord.substr(0, i + 1);
            if (curNode->isEnd && v.size() < 3) {
                v.push_back(b);
            }
            //now we should return first three words by using dfs 
            //cout << "index " << i << endl;
            firstthree(b, v, curNode);
            //for (int i=0; i< v.size();i++){
                //cout << v[i] << "," ;
            //}
            //cout << endl;
            res.push_back(v);
        }
        return res;
    }
};