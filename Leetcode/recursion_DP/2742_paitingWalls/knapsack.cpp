class Solution {
public:
    vector<vector<int>> memo;
    int dfs(vector<int>& cost, vector<int>& time, int pos, int limit, int n, int paidtime) {
        if (paidtime > n) return 1000000000;
        if (pos == n) {
            if (paidtime < 0) return 1000000000;
            return 0;
        }
        if (memo[pos][paidtime + n] != -1) return memo[pos][paidtime + n];
        int c1 = cost[pos] + dfs(cost, time, pos + 1, limit, n, paidtime + time[pos]);
        int c2 = dfs(cost, time, pos + 1, limit, n, paidtime - 1);
        memo[pos][paidtime + n] = min(c1, c2);
        return memo[pos][paidtime + n];
    }
    int paintWalls(vector<int>& cost, vector<int>& time) {
        /*
        Paid painters will be used for a maximum of N/2 units of time. There is no need to use paid painter for a time greater than this.
        */
        int n = time.size();
        int limit = n / 2;
        if (n % 2 == 1) limit++;
        vector<int> v(2 * n + 1, -1);//deal with temp negative index
        for (int i = 0; i < n; i++) memo.push_back(v);
        return dfs(cost, time, 0, limit, n, 0);
    }
};