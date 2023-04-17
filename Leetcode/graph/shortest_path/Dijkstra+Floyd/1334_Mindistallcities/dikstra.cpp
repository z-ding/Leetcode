class Solution {
public:
    typedef pair<int, int> pi;
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        //starting from each city, find the shortest distance to each city
        unordered_map<int, vector<pair<int, int>>> mp;
        for (int i = 0; i < edges.size(); i++) {
            mp[edges[i][0]].push_back({ edges[i][1],edges[i][2] });
            mp[edges[i][1]].push_back({ edges[i][0],edges[i][2] });
        }
        vector<int> city(n, 0);
        for (int i = 0; i < n; i++) {
            //dijkstra from each node
            vector<int> dist(n, 100000);
            priority_queue<pi, vector<pi>, greater<pi>> pq;//distance, node
            //update starting point
            dist[i] = 0;
            pi p = { 0,i };
            pq.push(p);
            while (!pq.empty()) {
                int cur = pq.top().second;
                int dis = pq.top().first;
                pq.pop();
                //process the node with the smallest distance to the starting point
                for (int i = 0; i < mp[cur].size(); i++) {
                    int next = mp[cur][i].first;
                    if (dis + mp[cur][i].second < dist[next]) {
                        //new route with shorter distance found
                        dist[next] = dis + mp[cur][i].second;
                        pi p = { dist[next],next };
                        pq.push(p);
                    }
                }
            }
            for (int j = 0; j < n; j++) {
                if (dist[j] <= distanceThreshold) {
                    city[i]++;//a route found
                }
            }
        }
        int minc = 100000;
        int res = -1;
        for (int i = 0; i < n; i++) {
            //cout << i << ":" << city[i] << endl;
            if (city[i] <= minc) {
                minc = city[i];
                res = i;
            }
        }
        return res;
    }
};