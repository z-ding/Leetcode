class Solution {
public:
    int memo[1001][1001];
    int dfs(string& str1, string& str2, int i, int j) {
        //cout << i << j << endl;
        if (i == str1.size() && j == str2.size()) return 0;
        if (i == str1.size()) return str2.size() - j;
        if (j == str2.size()) return str1.size() - i;
        if (memo[i][j] != -1) return memo[i][j];
        if (str1[i] == str2[j]) {
            int way = 1 + dfs(str1, str2, i + 1, j + 1); //take i || j doesn't matter
            memo[i][j] = way;
            return way;
        }
        else {
            int a = 1 + dfs(str1, str2, i + 1, j);//take i
            int b = 1 + dfs(str1, str2, i, j + 1);//take j
            memo[i][j] = min(a, b);
            return memo[i][j];
        }
    }
    string res;
    string shortestCommonSupersequence(string str1, string str2) {
        memset(memo, -1, sizeof(memo));
        int len = dfs(str1, str2, 0, 0);
        //cout << len << endl;
        int idx1 = 0;
        int idx2 = 0;
        while (idx1 < str1.size() && idx2 < str2.size()) {
            //cout << idx1 << "," << idx2 << endl;
            if (str1[idx1] == str2[idx2]) {
                res += str1[idx1];
                idx1++;
                idx2++;
            }
            else {
                if (memo[idx1][idx2] == 1 + memo[idx1 + 1][idx2]) {//take i
                    res += str1[idx1];
                    idx1++;
                }
                else {
                    res += str2[idx2];
                    idx2++;
                }
            }
            cout << idx1 << "," << idx2 << endl;
        }
        if (idx2 < str2.size()) {
            res += str2.substr(idx2);
        }
        if (idx1 < str1.size()) {
            res += str1.substr(idx1);
        }
        return res;
    }
};