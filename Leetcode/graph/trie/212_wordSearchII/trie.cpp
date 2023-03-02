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

    unordered_map<char, trieNode*> empty;
    trieNode* root = new trieNode(empty, false);
    void viewTrie(trieNode* node) {
        if (node == nullptr) {
            return;
        }
        for (auto& e : node->children) {
            cout << e.first << endl;
            viewTrie(e.second);
        }
    }
    void insert(string word) {
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
    }
    set<string> tmp;
    vector<string> res;
    string w;
    void search(vector<vector<char>>& board, int r, int c, trieNode* node, vector<vector<int>>& visited) {
        //cout << r << c << ":"  ;
        if (r == -1 || r == board.size() || c == -1 || c == board[0].size()) {
            return;
        }
        //we are at [r,c] and node in the trie. in the beginning we start from [i,j] & root
        //if board[r][c] is not in node's children, this is not a valid route. if it exists in node's children, we will traverse to neighbour cells and continue our searh
        if (node->children.find(board[r][c]) == node->children.end()) {
            //we don't mark it as visited in this case since it might be a valid route later
            return;
        }
        if (visited[r][c] == 1) {
            return;
        }
        visited[r][c] = 1;
        node = node->children[board[r][c]];//go to the correct subtree in the trie      
        //if word until board[r][c] happens to be the end of one word, push it to the result
        w += board[r][c];
        //cout << w << endl;
        if (node->isEnd) {
            tmp.insert(w);
        }
        //travrse to board[r][c]'s neighbour
        search(board, r + 1, c, node, visited);
        search(board, r - 1, c, node, visited);
        search(board, r, c + 1, node, visited);
        search(board, r, c - 1, node, visited);
        w.pop_back();//backtracking
        visited[r][c] = 0;//backtracking
        return;
    }

    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {

        //build the words into a trie
        for (int i = 0; i < words.size(); i++) {
            insert(words[i]);
        }
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                vector<int> v(board[0].size(), 0);
                vector<vector<int>> visited(board.size(), v);
                //cout << "visiting " << i << j << endl;
                search(board, i, j, root, visited);
            }
        }
        for (auto& e : tmp) {
            res.push_back(e);
        }
        //viewTrie(root);
        return res;
    }
};