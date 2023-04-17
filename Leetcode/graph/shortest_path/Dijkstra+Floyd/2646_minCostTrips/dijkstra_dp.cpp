class Solution {
public:
    unordered_map<int, vector<int>> mp;
    typedef pair<int, int> pi;

    int dfs(int cur, vector<int>& weight, bool canhalf, int parent, vector<vector<vector<int>>>& memo) {//max amount of cost that can be halved
        //half current position
        //cout << cur << "," << canhalf << endl;
        if (memo[cur][parent + 1][canhalf] != -1) {
            return memo[cur][parent + 1][canhalf];
        }
        int h1 = 0;
        int h2 = 0;
        if (canhalf) {
            h1 = weight[cur] / 2;
            for (int i = 0; i < mp[cur].size(); i++) {
                int next = mp[cur][i];
                if (next != parent) {
                    h1 += dfs(next, weight, false, cur, memo);
                }
            }
        }
        //don't half
        for (int i = 0; i < mp[cur].size(); i++) {
            int next = mp[cur][i];
            if (next != parent) {
                h2 += dfs(next, weight, true, cur, memo);
            }
        }
        memo[cur][parent + 1][canhalf] = max(h1, h2);
        return memo[cur][parent + 1][canhalf];
    }
    int minimumTotalPrice(int n, vector<vector<int>>& edges, vector<int>& price, vector<vector<int>>& trips) {
        vector<int> count(n, 0);//number of time to visit each node      
        for (int i = 0; i < edges.size(); i++) {
            mp[edges[i][0]].push_back(edges[i][1]);
            mp[edges[i][1]].push_back(edges[i][0]);
        }
        for (int i = 0; i < trips.size(); i++) {
            if (trips[i][0] == trips[i][1]) {
                count[trips[i][0]]++;
                continue;
            }
            vector<int> dist(n, 100000000);
            vector<int> prevvertex(n, -1);
            priority_queue<pi, vector<pi>, greater<pi> > pq;
            dist[trips[i][0]] = price[0];
            pi p = { price[0],trips[i][0] };
            pq.push(p);
            while (!pq.empty()) {
                int dis = pq.top().first;
                int cur = pq.top().second;
                pq.pop();
                for (int i = 0; i < mp[cur].size(); i++) {
                    int next = mp[cur][i];
                    if (dis + price[next] < dist[next]) {
                        dist[next] = dis + price[next];
                        p = { dist[next],next };
                        prevvertex[next] = cur;
                        pq.push(p);
                    }
                }
            }
            //update the count for the best route
            int parent = trips[i][1];
            //cout <<"dest " << trips[i][1] << endl;
            while (parent != trips[i][0]) {
                count[parent]++;
                parent = prevvertex[parent];
                //cout <<"via " << parent << endl;
            }
            count[trips[i][0]]++;
        }

        vector<int> weight(n, 0);
        int ttl = 0;
        for (int i = 0; i < count.size(); i++) {
            weight[i] = count[i] * price[i];
            //cout << weight[i] << endl;
            ttl += weight[i];
        }
        int maxhalf = 0;
        vector<int> v(2, -1);//canhalf
        vector<vector<int>> vv(n + 1, v);
        vector<vector<vector<int>>> memo(n, vv);
        int cur = dfs(0, weight, true, -1, memo);
        maxhalf = max(maxhalf, cur);
        return ttl - maxhalf;
    }
};