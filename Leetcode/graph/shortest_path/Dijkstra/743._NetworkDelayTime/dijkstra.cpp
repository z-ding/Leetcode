class Solution {
public:
    vector<int> distance;
    typedef pair<int, int> pi; //current distance, node pair
    priority_queue<pi, vector<pi>, greater<pi> > pq;//minheap, ordered by the first element in the pair (distance), 0 indexed
    unordered_map<int, vector<pi>> network;//0 indexed
    void dijkstra() {
        while (!pq.empty()) {
            //start from the top of min heap where the distance to the starting point is the smallest
            int node = pq.top().second;
            int dis = pq.top().first;
            //cout << node << "dis " << dis << endl;
            pq.pop();
            //process the neighbour of current node
            for (int i = 0; i < network[node].size(); i++) {
                int neighbour = network[node][i].first;

                int cost = network[node][i].second;
                if (dis + cost < distance[neighbour]) {
                    //cout << "updating" << neighbour << endl;
                    //calculate the new distance from this node to neighbour node
                    //cout << "neigh" << cost << endl;
                    //update if newdis is smaller than the current distance to neighbour node
                    distance[neighbour] = dis + cost;
                    pi p = { distance[neighbour],neighbour };
                    pq.push(p);
                }
            }
        }
        return;
    }
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {

        for (int i = 0; i < times.size(); i++) {
            if (network.find(times[i][0] - 1) == network.end()) {
                pi p = { times[i][1] - 1,times[i][2] };
                vector<pi> v;
                v.emplace_back(p);
                network.emplace(times[i][0] - 1, v);
            }
            else {
                pi p = { times[i][1] - 1,times[i][2] };
                network[times[i][0] - 1].push_back(p);
            }
        }
        pi d;
        for (int i = 0; i < n; i++) {
            distance.push_back(100000);
        }

        d = { 0,k - 1 }; //distance, node
        distance[k - 1] = 0;
        pq.push(d);

        dijkstra();
        int res = -1;
        for (int i = 0; i < distance.size(); i++) {
            //cout << distance[i] << endl;
            res = max(res, distance[i]);
        }
        if (res == 100000) {
            return -1;
        }
        return res;
    }
};