class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        vector<int> v(n, 100000);
        vector<vector<int>> dist(n, v);
        for (int i = 0; i < edges.size(); i++) {
            dist[edges[i][0]][edges[i][1]] = edges[i][2];
            dist[edges[i][1]][edges[i][0]] = edges[i][2];
        }
        for (int i = 0; i < n; i++) {
            dist[i][i] = 0;
        }
        for (int k = 0; k < n; k++) {//intermediate vertice
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (dist[i][k] + dist[j][k] < dist[i][j]) {//a route via intemediate vertice k is shorter than a direct route dist[i][j]
                        dist[i][j] = dist[i][k] + dist[j][k];
                    }
                }
            }
        }
        int mincity = 100000;
        int res = -1;
        for (int i = 0; i < dist.size(); i++) {
            int city = 0;
            for (int j = 0; j < dist.size(); j++) {
                if (dist[i][j] <= distanceThreshold) {
                    city++;
                }
            }
            if (city <= mincity) {
                mincity = city;
                res = i;
            }
        }
        return res;
    }
};