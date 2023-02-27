class Solution {
public:
    string shortestCommonSupersequence(string str1, string str2) {
        const int m = str1.size() + 1;
        const int n = str2.size() + 1;
        string res;
        //vector<string> v(n+1,"1");
        //vector<vector<string>> memo(m+1,v);
        //return super(str1,str2,0,0,memo,m,n);
        int dp[m][n];
        for (int i = 0; i <= m - 1; i++) {
            dp[i][n - 1] = m - 1 - i;
        }
        for (int i = 0; i <= n - 1; i++) {
            dp[m - 1][i] = n - 1 - i;
        }
        for (int i = m - 2; i >= 0; i--) {
            for (int j = n - 2; j >= 0; j--) {
                if (str1[i] == str2[j]) {
                    dp[i][j] = 1 + +dp[i + 1][j + 1];
                }
                else {
                    if (dp[i][j + 1] < dp[i + 1][j]) { // take j
                        dp[i][j] = 1 + dp[i][j + 1];
                    }
                    else {
                        dp[i][j] = 1 + dp[i + 1][j];
                    }
                }
            }
        }
        int a = 0; int b = 0;
        //reconstruct the superseq based on min step
        while (a < m - 1 && b < n - 1) {
            if (str1[a] == str2[b]) {
                res += str1[a];
                a++;
                b++;
            }
            else {
                if (dp[a + 1][b] > dp[a][b + 1]) {//take b & dp[a][b+1]
                    res += str2[b];
                    b++;
                }
                else {
                    res += str1[a];
                    a++;
                }
            }
        }
        if (a < m - 1) {
            res += str1.substr(a);
            return res;
        }
        if (b < n - 1) {
            res += str2.substr(b);
            return res;
        }
        /*
        for (int i=0; i<m;i++){
            for (int j=0; j<n;j++){
                cout << dp[i][j] << ",";
            }
            cout << endl;
        }*/
        return res;
    }
};