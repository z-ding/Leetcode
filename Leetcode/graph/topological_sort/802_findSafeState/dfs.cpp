class Solution {
public:
    unordered_map<int, bool> res;
    bool dfs(vector<vector<int>>& graph, int cur) {

        if (res.find(cur) != res.end()) {
            return res[cur];
        }

        res.emplace(cur, false);
        if (graph[cur].size() == 0) {
            res[cur] = true;
            return true;
        }

        for (int i = 0; i < graph[cur].size(); i++) {
            int next = graph[cur][i];
            if (!dfs(graph, next)) {
                res[cur] = false;
                return false;
            }
        }
        res[cur] = true;
        return true;
    }
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        for (int i = 0; i < graph.size(); i++) {
            dfs(graph, i);
        }
        vector<int> ans;
        for (auto& e : res) {
            if (e.second) {
                ans.push_back(e.first);
            }
        }
        sort(ans.begin(), ans.end());
        return ans;
    }
};