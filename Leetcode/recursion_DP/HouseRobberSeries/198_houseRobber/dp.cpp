class Solution {
public:
    unordered_map<int, int> memo;
    int profit(vector<int>& nums, int house) {
        if (memo.find(house) != memo.end()) {
            return memo[house];
        }
        if (house >= nums.size()) { //no more house to rob
            memo.emplace(house, 0);
            return 0;
        }

        int profit1 = nums[house] + profit(nums, house + 2);//rob this house
        int profit2 = profit(nums, house + 1); //not rob this house
        memo.emplace(house, max(profit1, profit2));
        return memo[house];
    }
    int rob(vector<int>& nums) {
        //return profit(nums,0);
        const int n = nums.size() + 2;
        int dp[n];
        dp[n - 1] = 0;
        dp[n - 2] = 0;
        for (int i = n - 3; i >= 0; i--) {
            dp[i] = max(nums[i] + dp[i + 2], dp[i + 1]);
        }
        return dp[0];
    }
};