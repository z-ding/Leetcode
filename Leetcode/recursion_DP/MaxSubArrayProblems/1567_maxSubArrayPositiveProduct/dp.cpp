class Solution {
public:
    int maxlen(vector<int>& nums, int start, int end) {
        if (start > end) {
            return 0;
        }
        int n = 0;
        int len = 0;
        int firstneg = -1;
        for (int i = start; i <= end; i++) {
            //count amount of neg number until index i
            if (nums[i] < 0) {
                if (firstneg == -1) {
                    firstneg = i;
                }
                n++;
            }
            if (n % 2 == 0) {//even number of negative number until index i
                len = max(len, i - start + 1);
            }
            else {
                if (firstneg != -1) {//do nothing first negative number
                    len = max(len, i - firstneg); //remove first neg number
                }
            }

        }
        //cout << start << "," << end << ":" << len << endl;
        return len;
    }
    int getMaxLen(vector<int>& nums) {
        int left = 0;
        int right = 0;
        int res = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == 0) {
                res = max(res, maxlen(nums, left, i - 1));
                left = i + 1;
                right = i + 1;
            }
        }
        if (right != nums.size()) {
            res = max(res, maxlen(nums, left, nums.size() - 1));
        }
        return res;
    }
};