class Solution {
public:
    long long res = 0;
    unordered_map<int, vector<int>> map;
    unordered_set<int> visited;
    int dfs(int cur, int seat) {
        int people = 1;
        visited.emplace(cur);
        for (int i = 0; i < map[cur].size(); i++) {
            if (visited.find(map[cur][i]) == visited.end()) {
                people += dfs(map[cur][i], seat);
            }
        }
        if (cur > 0) {
            res += (people + seat - 1) / seat;
        }
        //cout << cur << "," << people << ":" << res << endl;
        return people;
    }
    long long minimumFuelCost(vector<vector<int>>& roads, int seats) {
        vector<int> indegree(100000, 0);
        int n = 0;
        for (int i = 0; i < roads.size(); i++) {
            if (map.find(roads[i][0]) == map.end()) {
                vector<int> v = { roads[i][1] };
                map.emplace(roads[i][0], v);
            }
            else {
                map[roads[i][0]].push_back(roads[i][1]);
            }

            if (map.find(roads[i][1]) == map.end()) {
                vector<int> v = { roads[i][0] };
                map.emplace(roads[i][1], v);
            }
            else {
                map[roads[i][1]].push_back(roads[i][0]);
            }
            indegree[roads[i][1]]++;
            indegree[roads[i][0]]++;
            n = max(n, roads[i][1]);
            n = max(n, roads[i][0]);
        }
        queue<int> q;
        vector<int> r(n + 1, 0);
        for (int i = 0; i <= n; i++) {//start from leaf nodes
            if (indegree[i] == 1 && i != 0) {
                q.push(i);
                r[i]++;
            }
            //cout << indegree[i] << endl;
        }
        while (!q.empty()) {
            int person = q.front();
            indegree[person] = 0; //mark as visited
            q.pop();
            if (person != 0) {
                res += ceil((double)r[person] / seats);
            }
            //cout << person << "," << r[person] << ":" << res << endl;
            for (int i = 0; i < map[person].size(); i++) {
                int par = map[person][i];

                if (indegree[par]) {
                    indegree[par]--;
                    r[par] = r[par] + r[person];

                    if (indegree[par] == 1 && par != 0) {//no more unprocessed child, now it's a leafnode
                        //cout << "pare " << par << "," << indegree[par] << endl;
                        r[par]++;
                        q.push(par);
                    }
                }

            }
        }

        //dfs(0,seats);
        return res;
    }
};