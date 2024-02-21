class Solution {
public:
    int countDistinct(vector<int>& nums, int k, int p) {
        //starting from each index, check until longest length possible
        //put len and hash info into a hash map
        vector<long long> power = { 1ll };
        const long long pw = 211;
        long long mod = 1e9 + 9;
        for (int i = 1; i < nums.size(); i++) {
            long long x = power.back() * pw % mod;
            power.push_back(x);
        }
        unordered_map<int, unordered_set<int>> mp;
        for (int i = 0; i < nums.size(); i++) {
            int len = 0;
            int div = 0;
            long long hash = 0;
            while (div <= k && i + len < nums.size()) {
                if (nums[i + len] % p == 0) div++;
                if (div <= k) {
                    //take nums[i+len]
                    hash = (hash + nums[i + len] * power[len] % mod) % mod;
                    len++;
                    mp[len].emplace(hash);
                }
            }
        }
        int res = 0;
        for (auto& e : mp) {
            //cout << e.first << "," << e.second.size() << endl;
            res += e.second.size();
        }
        return res;
    }
};