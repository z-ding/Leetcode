class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int maxsum = nums[0];
        int maxprefix = nums[0];

        for (int i = 1; i < nums.size(); i++) {
            int curmax = nums[i];
            if (maxprefix > 0) {

                if (nums[i] > 0) {
                    curmax = maxprefix + nums[i];
                }
                else {
                    curmax = maxprefix;
                }
                maxprefix += nums[i];//pass to next position
            }
            else {
                maxprefix = nums[i];
            }

            maxsum = max(maxsum, curmax);

        }
        return maxsum;
    }
};