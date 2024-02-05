class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        deque<int> dq;
        int l = 0;
        int r = 0;
        while (r < nums.size()) {
            if (r - l >= k) {
                if (dq.front() == l) dq.pop_front();
                l++;
            }
            while (!dq.empty() && nums[r] > nums[dq.back()]) {
                dq.pop_back();
            }
            dq.push_back(r);
            if (r - l + 1 == k) res.push_back(nums[dq.front()]);
            r++;
        }
        return res;
    }
};