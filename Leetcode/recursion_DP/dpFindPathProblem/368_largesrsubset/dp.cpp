class Solution {
public:
    int memo[1001][1001];
    int dfs(vector<int>& nums, int pos, int prev) {//prev max position included
        if (pos == nums.size()) {
            memo[pos][prev + 1] = 0;
            return 0;
        }
        //cout << pos << "," << prev << endl;
        if (memo[pos][prev + 1] != -1) return memo[pos][prev + 1];
        int len1 = 0;
        int len2 = 0;
        if (prev == -1 || nums[pos] % nums[prev] == 0) {//can include this pos
            len1 = 1 + dfs(nums, pos + 1, pos);
        }
        //not include this pos
        len2 = dfs(nums, pos + 1, prev);
        memo[pos][prev + 1] = max(len1, len2);
        return memo[pos][prev + 1];
    }
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        memset(memo, -1, sizeof(memo));
        vector<int> res;
        int len = dfs(nums, 0, -1);
        //cout << len << endl;
        int n = nums.size();
        int prev = -1;
        for (int i = 0; i < n; i++) {//this pos
            if (!len) break;
            //cout << i << "," << len << endl;
            if (memo[i][prev + 1] != len) continue;
            //exclude memo[i][prev+1] == memo[i+x][prev+1]
            bool takei = true;
            for (int j = i + 1; j < n; j++) {
                if (memo[j][prev + 1] == len) {
                    takei = false;
                    break;
                }
            }
            if (takei) {
                res.push_back(nums[i]);
                prev = i;
                len--;
            }
        }
        return res;
    }
};