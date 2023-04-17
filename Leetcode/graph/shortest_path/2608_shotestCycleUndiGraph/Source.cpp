class Solution {
public:

    int findShortestCycle(int n, vector<vector<int>>& edges) {
        int res = 10000;
        vector<int> indegree(n, 0);
        unordered_map<int, vector<int>> mp;
        for (int i = 0; i < edges.size(); i++) {
            mp[edges[i][0]].push_back(edges[i][1]);
            mp[edges[i][1]].push_back(edges[i][0]);
        }

        //bfs from each node, check whether we can reach a previous node
        for (int i = 0; i < n; i++) {
            queue<pair<int, int>> q;//node, distance from starting node
            vector<int> dis(n, 10000);
            vector<int> parent(n, -1);
            pair<int, int> p = { i,0 };
            q.push(p);
            dis[i] = 0;
            while (!q.empty()) {
                int cur = q.front().first;
                int d = q.front().second;
                q.pop();
                for (int i = 0; i < mp[cur].size(); i++) {
                    int next = mp[cur][i];
                    if (d + 1 < dis[next]) {
                        dis[next] = d + 1;
                        parent[next] = cur;
                        pair<int, int> p = { next,d + 1 };
                        q.push(p);
                    }
                    else {
                        if (parent[next] != cur && parent[cur] != next) {//cycle detected
                            res = min(res, dis[next] + d + 1);
                        }
                    }
                }

            }
        }
        if (res == 10000) {
            return -1;
        }
        return res;
    }
};