class Solution {
public:
    /*
    index      0 1 2 3 4
            s1 a b c d e
            s2 a c d e
            index 0 matches, so the problem can be converted to 1+ lcs(s1.substr(1),s2.substr(1))
            index 1 doesn't match, so the problem can be converted to
            max(lcs(s1.substr(1),s2.substr(2)), lcs(s1.substr(2),s2.substr(1))

    */
    vector<vector<int>> memo;
    int lcs(string& s1, string& s2, int i, int j) {
        if (memo[i][j] != -1) {
            return memo[i][j];
        }
        if (i == s1.size() || j == s2.size()) {
            memo[i][j] = 0;
            return 0;
        }
        int l1 = 0;
        int l2 = 0;
        if (s1[i] == s2[j]) {
            l1 = 1 + lcs(s1, s2, i + 1, j + 1);
        }
        else {
            l2 = max(lcs(s1, s2, i + 1, j), lcs(s1, s2, i, j + 1));
        }
        memo[i][j] = max(l1, l2);
        return memo[i][j];
    }
    int longestCommonSubsequence(string text1, string text2) {
        for (int i = 0; i <= text1.size(); i++) {
            vector<int> v;
            for (int j = 0; j <= text2.size(); j++) {
                v.push_back(-1);
            }
            memo.push_back(v);
        }
        return lcs(text1, text2, 0, 0);
    }
};