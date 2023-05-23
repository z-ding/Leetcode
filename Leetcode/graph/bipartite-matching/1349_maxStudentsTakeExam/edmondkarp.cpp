class Solution {
public:
    /*
        if we imagine the seats matrix as two set of seats in odd columns and seats in even columns, we can convert this matrix to a bipartite graph. we can add one dummy source node and one dummy sink node and use the max flow algo to solve this problem
        neighbouring seats where students can cheat will have an edge between them and our target is figure out the max. number of student that can go from source node to sink node
        for simplicy, we can use index to represent each seat. seat at row r and column c will have the index of r* width of seats matrix + c
    */
    vector<int> bfs(vector<vector<int>>& network) {
        // find a path from s to t that every (u, v) in p satisfies c_f(u, v) > 0
        vector<int> parents(network.size(), -1);
        queue<int> q;
        q.push(0);//source node
        int u = 0;
        while (!q.empty() && parents.back() == -1) {
            u = q.front();
            q.pop();
            for (int v = 0; v < parents.size(); v++) {
                if (network[u][v] > 0 && parents[v] == -1) {
                    q.push(v);
                    parents[v] = u;
                }
            }
        }
        vector<int> path;
        u = parents.back();
        if (u != -1) {
            path.push_back(parents.size() - 1);
        }
        while (u != 0) {
            if (u == -1) return {};
            path.push_back(u);
            u = parents[u];
        }
        reverse(path.begin(), path.end());
        return path;
    }
    int maxStudents(vector<vector<char>>& seats) {
        //construct the capacity matrix
        int m = seats.size();
        int n = seats[0].size();
        //we will have non-broken seats +2 in our graph
        int available = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (seats[i][j] == '.') {
                    available++;
                }
            }
        }
        vector<int> v(available + 2, 0);
        vector<vector<int>> network(available + 2, v);
        vector<int> vv(n, -1);
        unordered_map<int, pair<int, int>> mp;//record 1-1 relationship of index and [x,y]
        vector<vector<int>> s(m, vv);//record index for valid seat
        int index = 0;//index 0 is reserved for dummy source node       
        for (int x = 0; x < m; x++) {
            for (int y = 0; y < n; y++) {
                if (seats[x][y] == '#') {
                    continue;//we don't need to add broken seats into our graph
                }
                index++;
                mp[index] = { x,y };
                s[x][y] = index;
            }
        }
        for (int x = 0; x < m; x++) {
            for (int y = 0; y < n; y++) {
                if (seats[x][y] == '#' || y % 2 == 1) {//only add capacity from odd col to even col
                    continue;//we don't need to add broken seats into our graph
                }
                int iu = s[x][y];
                vector<pair<int, int>> edges = { {x - 1,y - 1},{x,y - 1},{x + 1,y - 1},{x - 1,y + 1},{x,y + 1},{x + 1,y + 1} };//possible edges for cheating
                for (int i = 0; i < edges.size(); i++) {
                    pair<int, int> v = edges[i];
                    if (v.first < 0 || v.second < 0 || v.first == m || v.second == n || seats[v.first][v.second] != '.') {//not a valid edge
                        continue;
                    }
                    //found a edge
                    int iv = s[v.first][v.second];
                    network[iu][iv] = 1;
                }
            }
            //update the capacity of source and link node to infinity
            for (int i = 1; i < network.size() - 1; i++) {
                int col = mp[i].second;
                if (col % 2 == 0) {
                    network[0][i] = 1;
                }
                else {
                    network[i][available + 1] = 1;
                }


            }
        }
        int max_flow = 0;
        vector<int> path = bfs(network);
        while (path.size()) {
            // calculate residual capacity c_f(p)
            int residual_capacity = available;
            int u = 0;
            cout << "path" << endl;
            for (int v : path) {
                residual_capacity = min(residual_capacity, network[u][v]);
                u = v;
                //cout << v << "," <<residual_capacity << endl;
            }
            // increment max flow
            max_flow += residual_capacity;
            u = 0;
            // update residual network
            for (int v : path) {
                network[u][v] -= residual_capacity;
                network[v][u] += residual_capacity;
                u = v;
            }
            path = bfs(network);
        }
        return available - max_flow;
    }
};