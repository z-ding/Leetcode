class Solution {
public:
    int memo[1000][1001][2];
    int dfs(vector<int>& nums, int pos, int prev, int take) {//prev max position included
        if (pos == nums.size()) return 0;
        //cout << pos << "," << prev << endl;
        if (memo[pos][prev + 1][take] != -1) return memo[pos][prev + 1][take];
        int len1 = 0;
        int len2 = 0;
        if (prev == -1 || nums[pos] % nums[prev] == 0) {//can include this pos
            len1 = 1 + dfs(nums, pos + 1, pos, 1);
        }
        //not include this pos
        len2 = dfs(nums, pos + 1, prev, 0);
        if (len1 > len2) {
            memo[pos][prev + 1][1] = len1;
            return len1;
        }
        else {
            memo[pos][prev + 1][0] = len2;
            return len2;
        }
    }
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        memset(memo, -1, sizeof(memo));
        int len = dfs(nums, 0, -1, 0);
        //cout << len << endl;
        int n = nums.size();
        int idx = -1;
        for (int i = 0; i < n; i++) {//pos
            for (int j = 0; j <= i; j++) {//prev pos
                if (memo[i][j][1] == len) {
                    idx = i;
                    i = 10000;
                    break;
                }
            }
        }
        len--;
        vector<int> res = { nums[idx] };
        //take idx, now idx+1 is the prev idx in the memo
        while (len) {
            //cout << idx << len << endl;
            int x = idx + 1;
            while (x < n) {
                if (memo[x][idx + 1][1] == len) {
                    res.push_back(nums[x]);
                    idx = x;
                    len--;
                    break;
                }
                x++;
            }
        }
        return res;
    }
};