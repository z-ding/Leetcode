class Solution {
public:
    inline int bisearch(vector<int>& nums, int l, int r, int target) {
        int mid = (l + r) / 2;
        //cout << l << "," << r << ":" << mid << endl;
        if (l > r) {
            if (l >= nums.size()) {
                return nums.size() - 1;
            }
            if (r < 0) {
                return 0;
            }
            if (nums[l] < target) {
                return l;
            }
            else {
                return r;
            }
        }
        if (target == nums[mid]) {
            while (mid < nums.size() && nums[mid] == target) {
                mid++;
            }
            return mid - 1;
        }
        else if (target < nums[mid]) {
            return bisearch(nums, l, mid - 1, target);
        }
        else {
            return bisearch(nums, mid + 1, r, target);
        }
        return -1;
    }
    //memorize the number we have already searched
    unordered_map<int, int> memol;
    unordered_map<int, int> memou;
    long long countFairPairs(vector<int>& nums, int lower, int upper) {
        sort(nums.begin(), nums.end());
        long long res = 0;
        for (int i = 0; i < nums.size(); i++) {
            int lb = lower - nums[i] - 1;
            int ub = upper - nums[i];
            if (ub < nums[i]) {
                break;
            }
            //find the number of element that >=lb && <=ub
            int l = -1;
            int r = -1;
            if (memol.find(lb) != memol.end() && memou.find(ub) != memou.end()) {
                l = memol[lb];
                r = memou[ub];
            }
            else if (memol.find(lb) != memol.end()) {
                l = memol[lb];
                r = bisearch(nums, 0, nums.size() - 1, ub);
                memou.emplace(ub, r);
            }
            else if (memou.find(ub) != memou.end()) {
                r = memou[ub];
                l = bisearch(nums, 0, nums.size() - 1, lb) + 1;
                memol.emplace(lb, l);
            }
            else {
                l = bisearch(nums, 0, nums.size() - 1, lb) + 1;
                r = bisearch(nums, 0, nums.size() - 1, ub);
                memol.emplace(lb, l);
                memou.emplace(ub, r);
            }

            if (r == i) {
                break;
            }
            if (l <= i) {
                l = i + 1;
            }
            if (l == nums.size()) {
                continue;
            }
            //cout << i << ":" << r << l << endl;
            res += (r - l + 1);
        }
        return res;
    }
};