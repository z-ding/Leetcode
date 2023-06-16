class Solution {
public:
    const int kMod = 1e9 + 7;
    //first number remains unchanged, then interleaving left and right sub tree
    int divide(vector<int>& nums, vector<vector<int>>& cnk) {
        if (nums.size() <= 2) return 1;
        long long ans = 1;
        const int n = nums.size();
        vector<int> left;
        vector<int> right;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] < nums[0]) {
                left.push_back(nums[i]);
            }
            else {
                right.push_back(nums[i]);
            }
        }
        int l = left.size();
        int r = right.size();
        ans = ((long long)cnk[l + r][l] * (long long)divide(left, cnk) % (long long)kMod) * (long long)divide(right, cnk) % (long long)kMod;
        return (int)ans;
    }
    int numOfWays(vector<int>& nums) {
        const int n = nums.size();
        vector<vector<int>> cnk(n + 1, vector<int>(n + 1, 1));
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j < i; ++j)
                cnk[i][j] = (cnk[i - 1][j] + cnk[i - 1][j - 1]) % kMod;
        return divide(nums, cnk) - 1;
    }
};