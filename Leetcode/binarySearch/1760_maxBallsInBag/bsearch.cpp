class Solution {
public:
    //guess the max balls and calculate how many operations we need to achieve this result
    int bsearch(int left, int right, int limit, vector<int>& nums, int ops) {
        int mid = (left + right) / 2;//guess
        //cout << left << right << mid << endl;
        if (left > right) {
            return left;
        }
        int op = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > mid) {
                if (nums[i] % mid == 0) {
                    op = op + nums[i] / mid - 1;
                }
                else {
                    op = op + nums[i] / mid;
                }
            }
        }
        //cout << op << endl;
        if (op > limit) {//try to make bigger guess
            return bsearch(mid + 1, right, limit, nums, op);//means answer should be bigger
        }
        else {//try to make smaller guess
            return bsearch(left, mid - 1, limit, nums, op);
        }
    }
    int minimumSize(vector<int>& nums, int maxOperations) {
        //int minb = 1000000000;
        int maxb = 1;
        for (int i = 0; i < nums.size(); i++) {
            //minb = min(minb, nums[i]);
            maxb = max(maxb, nums[i]);
        }
        return bsearch(1, maxb, maxOperations, nums, 1);
    }
};