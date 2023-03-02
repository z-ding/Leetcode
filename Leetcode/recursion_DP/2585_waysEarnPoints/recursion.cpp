class Solution {
public:
    int dfs(vector<vector<int>>& types, int pos, int amt, int target, vector<vector<vector<int>>>& memo) {
        //cout << pos << "," << amt << ":" << target << endl;
        if (pos == types.size()) {
            if (target < 0) {
                memo[pos][amt][0] = 0;
            }
            else {

            }
            return 0;
        }
        if (target < 0) {
            memo[pos][amt][0] = 0;
            return 0;
        }
        if (memo[pos][amt][target + 1] != -1) {
            return memo[pos][amt][target + 1];
        }

        if (target == 0) {
            memo[pos][amt][target + 1] = 1;
            return 1;
        }

        //take 1 more number from this position
        int take = 0;
        if (amt < types[pos][0]) {
            take = dfs(types, pos, amt + 1, target - types[pos][1], memo);
        }
        //not take number from this position, take from next position
        int nottake = dfs(types, pos + 1, 0, target, memo);
        memo[pos][amt][target + 1] = (take + nottake) % 1000000007;
        return memo[pos][amt][target + 1];
    }
    int waysToReachTarget(int target, vector<vector<int>>& types) {
        vector<vector<vector<int>>> memo;
        for (int i = 0; i < types.size(); i++) {
            vector<vector<int>> vv;
            for (int j = 0; j <= types[i][0]; j++) {
                vector<int> v;
                for (int k = 0; k <= target + 1; k++) {//-1,0,...,target
                    v.push_back(-1);
                }
                vv.push_back(v);
            }
            memo.push_back(vv);
        }
        vector<int> v1 = { -1,-1 };
        vector<vector<int>> vv1;
        vv1.push_back(v1);
        memo.push_back(vv1);
        return dfs(types, 0, 0, target, memo);
    }
};