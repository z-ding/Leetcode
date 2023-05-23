class Solution {
public:
    vector<int> path;
    unordered_map<int, vector<pair<int, int>>> mp;
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>> > pq;
    int dij(int src, int dest, int target, int n) {
        vector<int> dist(n, 1000000001);
        dist[src] = 0;
        pq.push({ 0,src });//dist, node, how many edges in the shortest paths is -1
        while (!pq.empty()) {
            int dis = pq.top()[0];
            int cur = pq.top()[1];
            pq.pop();
            for (int i = 0; i < mp[cur].size(); i++) {
                int next = mp[cur][i].first;
                int weight = mp[cur][i].second;
                if (weight == -1) {
                    weight = 1000000001;
                }
                if (dis + weight < dist[next]) {
                    dist[next] = dis + weight;
                    path[next] = cur;
                    pq.push({ dist[next],next });
                }
            }
        }
        return dist[dest];
    }

    vector<vector<int>> modifiedGraphEdges(int n, vector<vector<int>>& edges, int source, int destination, int target) {
        for (int i = 0; i < edges.size(); i++) {
            mp[edges[i][0]].push_back({ edges[i][1],edges[i][2] });
            mp[edges[i][1]].push_back({ edges[i][0],edges[i][2] });
        }
        for (int i = 0; i < n; i++) {
            path.push_back(-1);
        }
        int x = dij(source, destination, target, n);
        vector<vector<int>> res;
        if (x < target) {
            return res;
        }
        path.clear();
        for (int i = 0; i < n; i++) {
            path.push_back(-1);
        }
        //change one -1 edge to 1 each time
        bool found = false;

        if (x == target) {
            found = true;
        }
        for (int i = 0; i < edges.size(); i++) {
            if (edges[i][2] == -1) {
                int parent = edges[i][0];
                int node = edges[i][1];
                int index = -1;
                int index2 = -1;
                for (int i = 0; i < mp[parent].size(); i++) {
                    if (mp[parent][i].first == node) {
                        index = i;
                        break;
                    }
                }
                for (int i = 0; i < mp[node].size(); i++) {
                    if (mp[node][i].first == parent) {
                        index2 = i;
                        break;
                    }
                }
                mp[parent][index].second = 1;
                mp[node][index2].second = 1;
                x = dij(source, destination, target, n);
                //cout << i << ":" << x << endl;
                if (x <= target) {
                    //change this value to 1+ diff between target and shortest distance
                    mp[parent][index].second += (target - x);
                    mp[node][index2].second += (target - x);
                    found = true;
                    break;
                }
            }
        }
        if (!found) {
            return res;
        }
        for (int i = 0; i < edges.size(); i++) {
            if (edges[i][2] != -1) {
                res.push_back(edges[i]);
            }
            else {
                for (int j = 0; j < mp[edges[i][0]].size(); j++) {
                    if (mp[edges[i][0]][j].first == edges[i][1]) {
                        edges[i][2] = mp[edges[i][0]][j].second;
                        break;
                    }
                }
                if (edges[i][2] == -1) {
                    edges[i][2] = 2000000000;
                }
                res.push_back(edges[i]);
            }
        }
        return res;
    }
};