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
    //from each index, find the ending index of that interval, then search for the interval with the largest number of price from ending index +1
    vector<unordered_map<int, int>> memo;
    int maxnum(int start, vector<int>& prizePositions, int k, int interval) {
        if (memo[interval].find(start) != memo[interval].end()) {
            return memo[interval][start];
        }
        if (interval == 2) {
            memo[interval].emplace(start, 0);
            return 0;
        }
        if (start == prizePositions.size()) {
            memo[interval].emplace(start, 0);
            return 0;
        }
        int startnum = prizePositions[start];
        int end = bisearch(prizePositions, 0, prizePositions.size() - 1, startnum + k);
        int curprize = end - start + 1;
        //cout << start << "," << end << endl;
        if (end + 1 == prizePositions.size()) {
            memo[interval].emplace(start, curprize);
            return curprize;
        }
        //start from this index
        int sum1 = curprize + maxnum(end + 1, prizePositions, k, interval + 1);
        //not start from this index
        int next = bisearch(prizePositions, 0, prizePositions.size() - 1, startnum) + 1;
        int sum2 = maxnum(next, prizePositions, k, interval);
        int res = max(sum1, sum2);
        memo[interval].emplace(start, res);
        return res;
    }
    int maximizeWin(vector<int>& prizePositions, int k) {
        unordered_map<int, int> u;
        for (int i = 0; i <= 2; i++) {
            memo.emplace_back(u);
        }
        return maxnum(0, prizePositions, k, 0);
    }
};