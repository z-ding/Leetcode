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
        }

        dfs(0, seats);
        return res;
    }
};