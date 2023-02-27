class Solution {
public:
    /*
    observation
        s1: abc
        s2: ac
        as a== a, the problem is same as finding the superseq of a + (bc,c)
        now b != c, the problem is same as finding the shorter subseq of ab + (c,c) || ac + (bc,"")
    */
    string res;
    string empty;
    string super(string& s1, string& s2, int i, int j, vector<vector<string>>& memo, int m, int n) {
        if (memo[i][j] != "1") {
            return memo[i][j];
        }
        if (i == m && j == n) {
            memo[i][j] = empty;
            return memo[i][j];
        }
        if (i == m) {
            //e.g. s2: XXXXjX, jx is the string needed
            memo[i][j] = s2.substr(j);
            return  memo[i][j];
        }
        if (j == n) {
            memo[i][j] = s1.substr(i);
            return  memo[i][j];
        }
        //i, j both in bound
        //int l1 = 1000; int l21 = 1000;int l22 = 1000;
        if (s1[i] == s2[j]) {
            memo[i][j] = s1[i] + super(s1, s2, i + 1, j + 1, memo, m, n);
        }
        else {
            string a = s2[j] + super(s1, s2, i, j + 1, memo, m, n); //take s2[j]
            string b = s1[i] + super(s1, s2, i + 1, j, memo, m, n);//take s1[i]
            if (a.size() > b.size()) {
                memo[i][j] = b;
            }
            else {
                memo[i][j] = a;
            }
        }
        return memo[i][j];
    }
    string shortestCommonSupersequence(string& str1, string& str2) {
        const int m = str1.size() + 1;
        const int n = str2.size() + 1;
        //vector<string> v(n+1,"1");
        //vector<vector<string>> memo(m+1,v);
        //return super(str1,str2,0,0,memo,m,n);
        string dp[m][n];
        for (int i = 0; i < m - 1; i++) {
            dp[i][n - 1] = str1.substr(i);
        }
        for (int i = 0; i < n - 1; i++) {
            dp[m - 1][i] = str2.substr(i);
        }
        for (int i = m - 2; i >= 0; i--) {
            for (int j = n - 2; j >= 0; j--) {
                if (str1[i] == str2[j]) {
                    dp[i][j] = str1[i] + dp[i + 1][j + 1];
                }
                else {
                    if (dp[i][j + 1].size() < dp[i + 1][j].size()) { // take j
                        dp[i][j] = str2[j] + dp[i][j + 1];
                    }
                    else {
                        dp[i][j] = str1[i] + dp[i + 1][j];
                    }
                }
            }
        }
        return dp[0][0];
    }
};