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

        //if we don't rob the first house, we can rob the lasy one
        if (nums.size() == 1) {
            return nums[0];
        }
        const int n = nums.size() + 2;
        int dp1[n];
        dp1[n - 1] = 0;
        dp1[n - 2] = 0;
        for (int i = n - 3; i >= 1; i--) { //don't rob the first house
            dp1[i] = max(nums[i] + dp1[i + 2], dp1[i + 1]);
        }
        //if we rob the first house, we couldn't rob the last one
        int dp2[n];
        dp2[n - 1] = 0;
        dp2[n - 2] = 0;
        dp2[n - 3] = 0;

        for (int i = n - 4; i >= 0; i--) { //don't rob the first house
            dp2[i] = max(nums[i] + dp2[i + 2], dp2[i + 1]);
        }
        return max(dp1[1], dp2[0]);
    }
};