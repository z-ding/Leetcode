class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int curmax = 0;
        int curmin = 0;
        int maxsofar = -1000000;
        int minsofar = 1000000;
        int arraysum = 0;
        for (int i = 0; i < nums.size(); i++) {
            curmax = max(curmax + nums[i], nums[i]);
            curmin = min(curmin + nums[i], nums[i]);
            maxsofar = max(curmax, maxsofar);
            minsofar = min(curmin, minsofar);
            arraysum += nums[i];
        }
        if (maxsofar < 0) {
            return maxsofar;
        }
        else {
            return max(maxsofar, arraysum - minsofar);
        }
    }
};