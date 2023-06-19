class Solution {
public:
    vector<vector<vector<int>>> memo;
    int dfs(vector<int>& arr1, int cur, int prev, int a, vector<int>& nondup) {
        if (memo[cur][prev + 1][a] != -1) return memo[cur][prev + 1][a];
        int noswap = 10000;
        int swap = 10000;
        int target = 0;
        //cout << cur << "," << prev << "," << a << endl;
        if (cur == arr1.size()) return 0;
        if (prev != -1) {
            if (a == 1) {
                target = arr1[prev];
            }
            else {
                target = nondup[prev];
            }
        }
        if (prev == -1 || arr1[cur] > target) {//no swap
            noswap = dfs(arr1, cur + 1, cur, 1, nondup);
        }
        //find the next bigger number vs cur number
        auto it = upper_bound(nondup.begin(), nondup.end(), target);
        if (it != nondup.end()) {
            int x = it - nondup.begin();
            swap = dfs(arr1, cur + 1, x, 2, nondup) + 1;
        }
        memo[cur][prev + 1][a] = min(swap, noswap);
        return memo[cur][prev + 1][a];

    }
    int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) {
        sort(arr2.begin(), arr2.end());
        vector<int> nondup = { arr2[0] };
        //remove duplicated numbers in arr2 as they are useless
        for (int i = 1; i < arr2.size(); i++) {
            if (arr2[i] != arr2[i - 1]) {
                nondup.push_back(arr2[i]);
            }
        }
        int n = max(arr1.size(), arr2.size());
        vector<vector<int>> v(n + 2, vector<int> {-1, -1, -1});
        for (int i = 0; i <= n; i++) {
            memo.push_back(v);
        }
        int res = dfs(arr1, 0, -1, 1, nondup);
        if (res == 10000) return -1;
        return res;
    }
};