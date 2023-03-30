class Solution {
public:
    pair<int, int> dfs(vector<int>& nums, int pos, int hurdlepos, vector<vector<pair<int, int>>>& memo) {
        if (memo[pos][hurdlepos + 1].first != -1) {
            return memo[pos][hurdlepos + 1];
        }
        if (pos == nums.size()) {
            pair<int, int> p = { 0,1 };
            memo[pos][hurdlepos + 1] = p;
            return p;
        }
        int l1 = 0; int l2 = 0; int w1 = 0; int w2 = 0;
        if (hurdlepos == -1 || nums[pos] > nums[hurdlepos]) {//can include pos in the subseq
            l1 = 1 + dfs(nums, pos + 1, pos, memo).first;
            w1 = dfs(nums, pos + 1, pos, memo).second;
        }
        //not include pos
        l2 = dfs(nums, pos + 1, hurdlepos, memo).first;
        w2 = dfs(nums, pos + 1, hurdlepos, memo).second;
        pair<int, int> res;
        if (l1 > l2) {
            res = { l1,w1 };
        }
        else if (l1 < l2) {
            res = { l2,w2 };
        }
        else {
            res = { l2,w1 + w2 };
        }
        memo[pos][hurdlepos + 1] = res;
        return res;
    }
    int findNumberOfLIS(vector<int>& nums) {
        pair<int, int> p = { -1,-1 };
        vector<pair<int, int>> v(nums.size() + 2, p);
        vector<vector<pair<int, int>>> memo(nums.size() + 2, v);
        return dfs(nums, 0, -1, memo).second;
    }
};