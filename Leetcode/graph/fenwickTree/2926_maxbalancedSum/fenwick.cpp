class Solution {
public:
    long long worst = -1000000000;
    vector<long long> fenwick;
    inline int lowbit(int x) {
        return x & (-x);
    }
    void update(int i, long long val) {
        while (i < fenwick.size()) {
            fenwick[i] = max(fenwick[i], val);
            i += lowbit(i);
        }
    }
    long long query(int i) {
        long long ans = worst;
        while (i > 0) {
            ans = max(fenwick[i], ans);
            i -= lowbit(i);
        }
        return ans;
    }
    long long maxBalancedSubsequenceSum(vector<int>& nums) {
        int n = nums.size();
        //nums[j] - nums[i] >= j-i <=> nums[j] - j >= nums[i]-i
        vector<pair<int, int>> v;
        for (int i = 0; i < n; i++) v.push_back({ nums[i] - i,i });//value and index
        for (int i = 0; i <= n; i++) fenwick.push_back(worst);//1-indexed

        sort(v.begin(), v.end());//sort by value in asd order
        //now for each value in asd order, we want to pick the max sum of the index from [0...idx-1] and record the max value in dp array
        long long res = worst;
        for (int i = 0; i < n; i++) {
            int idx = v[i].second;
            long long prevmax = query(idx);//0..idx-1 -> 1 indexed
            long long curmax = (long long)nums[idx] + max(0ll, prevmax);
            res = max(res, curmax);
            update(idx + 1, curmax);

        }
        return res;
    }
};