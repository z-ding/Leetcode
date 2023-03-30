class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int left = 0;
        int right = 0;
        int res = 0;
        int product = 1;
        int prevend = -1;
        int valid = 0;
        while (right < nums.size()) {
            product *= nums[right];
            if (nums[right] < k) {
                res++;
            }
            while (product >= k && left < right) {
                product /= nums[left];
                left++;
            }
            if (product < k) {
                //cout << left << "," << right << endl;
                res = res + right - left;

            }
            right++;

        }
        return res;
    }
};