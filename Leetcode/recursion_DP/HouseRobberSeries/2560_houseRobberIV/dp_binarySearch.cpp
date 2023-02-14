class Solution {
public:

    int rob(vector<int>& nums, int house, int capacity, vector<int>& memo) {//return the max number of house that can be robbed given a capacity limit
        if (memo[house] != -1) {
            return memo[house];
        }
        if (house >= nums.size()) {
            memo[house] = 0;
            return 0;
        }
        int r = 0; int nr = 0;
        if (nums[house] > capacity) {
            nr = rob(nums, house + 1, capacity, memo);
        }
        else {
            nr = rob(nums, house + 1, capacity, memo);
            r = 1 + rob(nums, house + 2, capacity, memo);
        }
        memo[house] = max(r, nr);
        return memo[house];
    }
    int dp(vector<int>& nums, int cap) {
        const int n = nums.size() + 2;
        int dp[n];
        dp[n - 1] = 0;
        dp[n - 2] = 0;
        for (int i = n - 3; i >= 0; i--) {
            if (nums[i] > cap) {
                //can't rob this house
                dp[i] = dp[i + 1];
            }
            else {
                dp[i] = max(dp[i + 1], 1 + dp[i + 2]);
            }
        }
        return dp[0];
    }
    int minCapability(vector<int>& nums, int k) {
        int lb = 1000000000;
        int ub = 0;
        for (int i = 0; i < nums.size(); i++) {
            lb = min(lb, nums[i]);
            ub = max(ub, nums[i]);
        }
        int canrob = 0;
        int mid = 0;
        int res = 1000000000;
        while (lb <= ub) {
            vector<int> memo(nums.size() + 2, -1);
            mid = (lb + ub) / 2;
            //canrob = rob(nums,0,mid, memo);
            canrob = dp(nums, mid);
            //cout << lb << "," << ub << ":" << canrob << endl;
            if (canrob < k) {
                lb = mid + 1;
            }
            else {
                res = min(res, mid);
                ub = mid - 1;
            }

        }
        return res;
    }
};