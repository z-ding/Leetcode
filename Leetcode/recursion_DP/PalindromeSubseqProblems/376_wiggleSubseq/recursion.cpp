class Solution {
public:
    int wiggle(vector<int>& nums, int cur, int prevdiff, vector<vector<int>>& memo) {//prevdiff 2: neg, 1: pos, 0: 0 or non-exist
        if (memo[cur][prevdiff] != -1) {
            return memo[cur][prevdiff];
        }
        if (cur == nums.size()) {
            memo[cur][0] = 0; memo[cur][1] = 0; memo[cur][2] = 0;
            return 0;
        }

        int diff = 0;
        int l0 = 0; int l1 = 0;
        if (cur > 0 && nums[cur] > nums[cur - 1]) {
            diff = 1;
        }
        else if (cur > 0 && nums[cur] < nums[cur - 1]) {
            diff = 2;
        } //else: cur ==0 || nums[cur] == nums[cur-1]: diff remains as 0
        //cout << cur << "," << prevdiff << "," << diff << endl;
        if ((!cur || diff) && (!prevdiff || prevdiff != diff)) { //prevdiff ==0 || prevdiff and diff have different sign. (if diff ==0, this number can't be put into the seq unless it's the first number in the array)
            l1 = 1 + wiggle(nums, cur + 1, diff, memo);//put this number into the subseq
        }
        l0 = wiggle(nums, cur + 1, prevdiff, memo); //not put this number into the subseq
        memo[cur][prevdiff] = max(l1, l0);
        return memo[cur][prevdiff];
    }
    int wiggleMaxLength(vector<int>& nums) {
        vector<int> v(3, -1);
        vector<vector<int>> memo(nums.size() + 1, v);
        return wiggle(nums, 0, 0, memo);
    }
};