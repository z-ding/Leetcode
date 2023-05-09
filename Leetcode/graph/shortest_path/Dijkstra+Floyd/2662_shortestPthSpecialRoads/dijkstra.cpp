class Solution {
public:
    int minimumCost(vector<int>& start, vector<int>& target, vector<vector<int>>& specialRoads) {
        unordered_map<int, pair<int, int>> index;
        int n = specialRoads.size();
        int cur = 0;
        unordered_map<int, vector<pair<int, int>>> mp;
        for (int i = 0; i < n; i++) {
            int a = cur;
            index[cur] = { specialRoads[i][0],specialRoads[i][1] };
            cur++;
            int b = cur;
            index[cur] = { specialRoads[i][2],specialRoads[i][3] };
            cur++;
            //create edges for special roads
            pair<int, int> p = { b,specialRoads[i][4] };//target node, distance
            mp[a].push_back(p);
        }
        index[cur] = { start[0],start[1] };
        cur++;
        index[cur] = { target[0],target[1] };
        //create edges for all nodes
        for (auto& node1 : index) {
            for (auto& node2 : index) {
                if (node1 == node2) {
                    continue;
                }
                int x1 = node1.second.first;
                int y1 = node1.second.second;
                int x2 = node2.second.first;
                int y2 = node2.second.second;
                int dist = abs(x1 - x2) + abs(y1 - y2);
                mp[node1.first].push_back({ node2.first,dist });
                mp[node2.first].push_back({ node1.first,dist });
            }
        }
        vector<int> dist(cur + 1, INT_MAX);
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>> > pq;
        dist.back() = abs(start[0] - target[0]) + abs(start[1] - target[1]);
        dist[cur - 1] = 0;
        pq.push({ 0,cur - 1 });
        while (!pq.empty()) {
            int distance = pq.top()[0];
            int i = pq.top()[1];
            pq.pop();
            for (int j = 0; j < mp[i].size(); j++) {
                int next = mp[i][j].first;
                int d = mp[i][j].second;
                if (distance + d < dist[next]) {
                    dist[next] = distance + d;
                    pq.push({ dist[next],next });
                }
            }
        }
        return dist.back();
    }
};