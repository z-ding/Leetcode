class Solution {
public:
    vector<string> prefix;
    vector<vector<string>> res;
    inline bool ispal(string s) {
        if (s.size() == 0) {
            return false;
        }
        string r = s;
        reverse(s.begin(), s.end());
        if (s == r) {
            return true;
        }
        else {
            return false;
        }
    }
    void par(string s, int pos) {
        if (pos == s.size() || s.size() == 0) {
            return;
        }

        string pre = s.substr(0, pos + 1);
        if (ispal(pre)) {//prefix is Palindrome
            prefix.push_back(pre);
            string tail;
            if (pos + 1 < s.size()) {
                tail = s.substr(pos + 1);
            }
            if (ispal(tail)) {
                prefix.push_back(tail);
                res.push_back(prefix);
                prefix.pop_back();
            }
            par(tail, 0);
            prefix.pop_back();
        }

        par(s, pos + 1);

        return;
    }
    vector<vector<string>> partition(string s) {
        if (ispal(s)) {
            vector<string> v = { s };
            res.push_back(v);
        }
        par(s, 0);
        return res;
    }
};