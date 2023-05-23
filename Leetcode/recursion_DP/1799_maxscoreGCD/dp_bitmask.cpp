class Solution {
public:
    unordered_map<int, int> dp[8][15][15];
    int dfs(vector<int>& nums, int op, int status, int n, int pos1, int pos2) {//status represents whether number is used at certain position. in the beginning should be 0
        int best = 0;

        if (op == n || pos1 == nums.size() || pos2 == nums.size()) {
            return 0;
        }
        if (dp[op][pos1][pos2].find(status) != dp[op][pos1][pos2].end()) {
            return dp[op][pos1][pos2][status];
        }
        for (int i = pos1; i < nums.size(); i++) {//pick i if i is available
            if (((1 << i) & status) != 0) {
                continue;
            }
            for (int j = pos2; j < nums.size(); j++) {//pick j if i is available
                if (i == j || ((1 << j) & status) != 0) {
                    continue;
                }
                int score = (op + 1) * gcd(nums[i], nums[j]) + dfs(nums, op + 1, status | (1 << i) | (1 << j), n, 0, 1);
                best = max(score, best);
            }
        }
        dp[op][pos1][pos2][status] = best;
        return best;
    }
    int maxScore(vector<int>& nums) {
        return dfs(nums, 0, 0, nums.size() / 2, 0, 1);
    }
};