class Solution {
public:
    /*
          0 1 2 3 4
    e.g. [1,2,2,3,3] - I
         [1,1,2,2,3]  - II
         if every number appears twice before mid (example II) && mid is even number, mid and mid+1 should be the same number. so if mid is even and mid != mid+1, the single element apprears before mid. else it appears after mid (example I). Likewise for the odd number situation

    */
    int bsearch(vector<int>& nums, int left, int right) {
        //cout << left << right << endl;
        int mid = (left + right) / 2;
        if (left > right) {
            return nums[left];
        }
        if (mid % 2 == 0) {
            if (mid + 1 == nums.size()) {
                //mid is the last number of the array
                return nums[mid];
            }
            else {
                if (nums[mid] != nums[mid + 1]) {
                    return bsearch(nums, left, mid - 1);
                }
                else {
                    return bsearch(nums, mid + 1, right);
                }
            }
        }
        else {
            if (mid - 1 == -1) {
                //mid is the last number of the array
                return nums[0];
            }
            else {
                if (nums[mid] != nums[mid - 1]) {
                    return bsearch(nums, left, mid - 1);
                }
                else {
                    return bsearch(nums, mid + 1, right);
                }
            }
        }
        return -1;
    }
    int singleNonDuplicate(vector<int>& nums) {
        return bsearch(nums, 0, nums.size() - 1);
    }
};