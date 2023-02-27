class Solution {
public:
    bool isSubsequence(string s, string t) {
        if (s.size() > t.size()) {
            return false;
        }
        int indexs = 0;
        for (int i = 0; i < t.size(); i++) {
            if (t[i] == s[indexs]) {
                indexs++;
            }
        }
        if (indexs == s.size()) {
            return true;
        }
        return false;
    }
};