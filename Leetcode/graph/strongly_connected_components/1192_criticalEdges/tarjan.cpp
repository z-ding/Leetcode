class Solution {
public:
    unordered_map<int, vector<int>> mp;
    unordered_set<int> visited;
    vector<int> order; //order of visit
    vector<int> group; //belong to which group
    int x = 0;
    int tarjan(int cur, int prev) {
        if (visited.find(cur) != visited.end()) {
            //visited
            group[cur] = min(min(group[prev], x), group[cur]);
            return group[cur];
        }
        //unvisited node
        visited.emplace(cur);
        order[cur] = x;
        group[cur] = x;
        for (int i = 0; i < mp[cur].size(); i++) {
            int next = mp[cur][i];
            if (next == prev) continue;
            x++;
            group[cur] = min(group[cur], tarjan(next, cur));
            x--;
        }
        return group[cur];
    }
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        for (int i = 0; i < n; i++) {
            order.push_back(-1);
            group.push_back(1000000);
        }
        for (int i = 0; i < connections.size(); i++) {
            mp[connections[i][0]].push_back(connections[i][1]);
            mp[connections[i][1]].push_back(connections[i][0]);
        }
        tarjan(0, -1);
        vector<vector<int>> res;
        for (int i = 0; i < connections.size(); i++) {
            int x = connections[i][0];
            int y = connections[i][1];
            if (group[x] != group[y]) res.push_back(connections[i]);
        }
        return res;
    }
};