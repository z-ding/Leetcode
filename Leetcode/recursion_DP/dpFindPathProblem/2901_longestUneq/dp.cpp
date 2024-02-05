class Solution {
public:
    int memo[1001][1003][2];
    inline int ham(string s1, string s2) {
        if (s1.size() != s2.size()) return 100;
        int d = 0;
        for (int i = 0; i < s1.size(); i++) {
            if (s1[i] != s2[i]) d++;
            if (d > 1) return 100;
        }
        return d;
    }
    int dfs(vector<string>& words, vector<int>& groups, int pos, int prevpos, int take) {
        if (pos == words.size()) return 0;
        if (memo[pos][prevpos + 1][take] != -1) return memo[pos][prevpos + 1][take];
        int l1 = 0; int l2 = 0;
        if (prevpos == -1 || groups[pos] != groups[prevpos]) {
            if (prevpos == -1 || ham(words[pos], words[prevpos]) == 1) {
                l1 = 1 + dfs(words, groups, pos + 1, pos, 1);
            }

        }
        l2 = dfs(words, groups, pos + 1, prevpos, 0);
        if (l1 > l2) {
            memo[pos][prevpos + 1][1] = l1;
            return l1;
        }
        else {
            memo[pos][prevpos + 1][0] = l2;
            return l2;
        }
    }


    vector<string> getWordsInLongestSubsequence(int n, vector<string>& words, vector<int>& groups) {
        memset(memo, -1, sizeof(memo));
        int x = dfs(words, groups, 0, -1, 0);
        vector<string> ans;
        //cout << x << endl;
        /*
        for (int i=0; i<n;i++){
            for (int j=0; j<=i;j++){
                cout << memo[i][j][0] << "," << memo[i][j][1] << "|" ;
            }
            cout << endl;
        }*/
        int startindex = -1;
        for (int i = 0; i < n; i++) {
            if (memo[i][0][1] == x) {
                startindex = i;
                break;
            }
        }
        int previndex = startindex;
        ans.push_back(words[startindex]);
        int curlen = x - 1;
        while (curlen) {
            for (int i = previndex + 1; i <= n; i++) {
                if (memo[i][previndex + 1][1] == curlen) {
                    ans.push_back(words[i]);
                    previndex = i;
                    curlen--;
                    break;
                }
            }
        }

        return ans;
    }
};