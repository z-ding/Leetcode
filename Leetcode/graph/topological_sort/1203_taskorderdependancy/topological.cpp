class Solution {
public:
    vector<int> topo(unordered_map<int, vector<int>>& mp, vector<int>& indegree, int n) {
        queue<int> q;
        vector<int> res;
        for (int i = 0; i < n; i++) {
            if (indegree[i] == 0) q.push(i);
        }
        int node = 0;
        while (!q.empty()) {
            int cur = q.front();
            //cout << cur << endl;
            node++;
            res.push_back(cur);
            q.pop();
            for (int i = 0; i < mp[cur].size(); i++) {
                int next = mp[cur][i];
                indegree[next]--;
                if (indegree[next] == 0) q.push(next);
            }
        }
        if (node != n) return {};
        return res;
    }
    vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {
        /*
        multiple items -> group: n to 1 relationship
        so we can get a topological sequence of group list
        then we get topological list of items in each group
        */
        //change group number with -1 into unique index
        for (int i = 0; i < group.size(); i++) {
            if (group[i] == -1) {
                group[i] = m;
                m++;
            }
        }
        unordered_map<int, vector<int>> gp_mp;
        vector<int> gp_id(m, 0);
        for (int i = 0; i < beforeItems.size(); i++) {
            for (int j = 0; j < beforeItems[i].size(); j++) {
                //group[x] must come before group[i]
                int x = beforeItems[i][j];
                if (group[x] != group[i]) {
                    gp_mp[group[x]].push_back(group[i]);
                    gp_id[group[i]]++;

                }

            }
        }
        vector<int> gp = topo(gp_mp, gp_id, m);
        if (gp.size() != m) return {};
        unordered_map<int, vector<int>> item_mp;
        vector<int> item_id(n, 0);
        for (int i = 0; i < beforeItems.size(); i++) {
            item_id[i] += beforeItems[i].size();
            for (int j = 0; j < beforeItems[i].size(); j++) {
                //group[x] must come before group[i]
                int x = beforeItems[i][j];
                item_mp[x].push_back(i);
            }
        }
        vector<int> item = topo(item_mp, item_id, n);
        if (item.size() != n) return {};
        unordered_map<int, vector<int>> u;
        for (int i = 0; i < item.size(); i++) {
            u[group[item[i]]].push_back(item[i]);
        }
        vector<int> res;
        for (int i = 0; i < gp.size(); i++) {
            for (int j = 0; j < u[gp[i]].size(); j++) {
                res.push_back(u[gp[i]][j]);
            }
        }
        return res;
    }
};