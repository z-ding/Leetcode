class Solution {
public:
    unordered_map<int, int> mp;
    int memo[1000002][2];
    int dfs(int current, int used) {
        int best = 0;
        //look for current
        //use the real current
        if (memo[current][used] != -1) return memo[current][used];
        if (mp.find(current) != mp.end()) {
            best = max(best, 1 + dfs(current + 1, 1));
        }
        //use current -1 and increment it to make it as current
        if (mp.find(current - 1) != mp.end()) {
            /*
            if number to look at is 2, if we used a 1 in the previous recurssion
            we have to have another 1 so that we can increment it
            */
            if (mp[current - 1] > 1 || !used) {
                best = max(best, 1 + dfs(current + 1, false));
            }
        }
        memo[current][used] = best;
        return best;
    }
    int maxSelectedElements(vector<int>& nums) {
        for (auto& x : nums) mp[x]++;
        int res = 0;
        memset(memo, -1, sizeof(memo));
        for (auto& x : mp) {
            res = max(res, dfs(x.first, 0));
            res = max(res, dfs(x.first + 1, 0));
        }
        return res;
    }
};