class Solution {
public:
    vector<vector<int>> res;
    unordered_map<int, vector<int>> mp;
    unordered_map<int, int> indegree;
    int n;
    void dfs(int node) {
        while (mp[node].size()) {
            int next = mp[node].back();
            mp[node].pop_back();
            dfs(next);
            res.push_back({ node,next });

        }
    }
    vector<vector<int>> validArrangement(vector<vector<int>>& pairs) {
        n = pairs.size();
        for (int i = 0; i < n; i++) {
            int s = pairs[i][0];
            int e = pairs[i][1];
            mp[s].push_back(e);
            indegree[s]--;
            indegree[e]++;
        }
        int start = -1;
        for (auto& e : indegree) {
            if (e.second < 0) {//more outgoing edges
                start = e.first;
                break;
            }
        }
        if (start == -1) start = mp.begin()->first;
        dfs(start);
        reverse(res.begin(), res.end());
        return res;
    }
};