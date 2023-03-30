class Solution {
public:
    int dfs(string& s, int start, int end, int k, vector<vector<int>>& memo) {
        if (memo[start + 1][end + 1] != -1) {
            return memo[start + 1][end + 1];
        }
        if (end - start < k - 1) {
            memo[start + 1][end + 1] = 0;
            return 0;
        }

        vector<int> freq(26, 0);//a,97
        for (int i = start; i <= end; i++) {
            freq[int(s[i]) - 97]++;
        }
        int left = 0; int right = 0;

        for (int i = 0; i < 26; i++) {
            if (freq[i] < k && freq[i]>0) {
                for (int j = start; j <= end; j++) {
                    if (s[j] == char(i + 97)) {
                        left = dfs(s, start, j - 1, k, memo);
                        right = dfs(s, j + 1, end, k, memo);
                        memo[start + 1][end + 1] = max(left, right);
                        return memo[start + 1][end + 1];
                    }
                }

            }
        }
        memo[start + 1][end + 1] = end - start + 1;
        return memo[start + 1][end + 1];

    }
    int longestSubstring(string s, int k) {
        vector<int> v(s.size() + 2, -1);
        vector<vector<int>> memo(s.size() + 2, v);
        return dfs(s, 0, s.size() - 1, k, memo);
    }
};