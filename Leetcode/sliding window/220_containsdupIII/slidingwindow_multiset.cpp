class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int indexDiff, int valueDiff) {
        multiset<int> set;
        //first indexdiffs element
        int n = nums.size() - 1;
        int s = min(indexDiff, n);
        for (int i = 0; i <= s; i++) {
            set.insert(nums[i]);
        }
        int prev = INT_MAX;
        for (auto& e : set) {
            if (prev == INT_MAX) {
                prev = e;
                continue;
            }
            if (abs(e - prev) <= valueDiff) {
                //cout <<e <<"," << prev << endl;
                return true;
            }
            prev = e;
        }
        for (int i = indexDiff + 1; i < nums.size(); i++) {
            set.erase(nums[i - indexDiff - 1]);
            //check whether there exists an element that's within value diff with nums[i]
            //compare the element that's smaller than nums[i] and bigger than nums[i]
            auto it = set.lower_bound(nums[i]);//first element that's >= nums[i]
            if (it != set.end()) {
                if ((*it) - nums[i] <= valueDiff) {
                    //cout <<(*it) <<"," << nums[i] << endl;
                    return true;
                }
            }
            if (it != set.begin()) {
                it--;
                if (nums[i] - (*it) <= valueDiff) {
                    //cout <<(*it) <<"," << nums[i] << endl;
                    return true;
                }
            }
            set.insert(nums[i]);
        }
        return false;
    }
};