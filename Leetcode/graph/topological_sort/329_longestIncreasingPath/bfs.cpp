class Solution {
public:
    inline int countedge(vector<vector<int>>& matrix, int r, int c, int baseline) {
        if (r < 0 || c < 0 || r == matrix.size() || c == matrix[0].size()) {
            return 0;
        }
        //cout <<"comparing " << r << c << ":" << matrix[r][c] << "with " << baseline<< endl;
        if (matrix[r][c] < baseline) {
            return 1;
        }
        else {
            return 0;
        }
    }

    vector<pair<int, int>> findways(vector<vector<int>>& matrix, int r, int c, int baseline, vector<pair<int, int>>& ways) {
        if (r < 0 || c < 0 || r == matrix.size() || c == matrix[0].size()) {
            return ways;
        }

        if (matrix[r][c] > baseline) {
            pair<int, int> p = { r,c };
            ways.push_back(p);
        }
        return ways;
    }
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        //count how many income edge there could be for a node
        int m = matrix.size();
        int n = matrix[0].size();
        vector<int> v(n, 0);
        vector<vector<int>> edges(m, v);
        vector<vector<int>> lp(m, v);
        queue<tuple<int, int, int>> q;//r,c,len
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                edges[i][j] = edges[i][j] + countedge(matrix, i + 1, j, matrix[i][j]);
                edges[i][j] = edges[i][j] + countedge(matrix, i - 1, j, matrix[i][j]);
                edges[i][j] = edges[i][j] + countedge(matrix, i, j - 1, matrix[i][j]);
                edges[i][j] = edges[i][j] + countedge(matrix, i, j + 1, matrix[i][j]);
                if (edges[i][j] == 0) {//no incoming edge, push to q
                    tuple<int, int, int> t = make_tuple(i, j, 1);
                    q.push(t);
                    lp[i][j] = 1;
                }
                //cout << i << j << "edge" << edges[i][j] << endl;
            }

        }
        int res = 1;
        while (!q.empty()) {
            int s = q.size();
            while (s--) {
                int r = get<0>(q.front());
                int c = get<1>(q.front());
                int len = get<2>(q.front());
                //cout << r << c << ":" << matrix[r][c] << ":" << len << endl;
                q.pop();//process this node with no incoming edge
                vector<pair<int, int>> ways;
                ways = findways(matrix, r + 1, c, matrix[r][c], ways);
                ways = findways(matrix, r - 1, c, matrix[r][c], ways);
                ways = findways(matrix, r, c + 1, matrix[r][c], ways);
                ways = findways(matrix, r, c - 1, matrix[r][c], ways);
                for (int i = 0; i < ways.size(); i++) {
                    int x = ways[i].first;
                    int y = ways[i].second;
                    edges[x][y]--;
                    if (!edges[x][y]) {//there is no other incoming edge anymore
                        int longest = max(len + 1, lp[x][y]);
                        tuple<int, int, int> t = make_tuple(x, y, longest);
                        lp[x][y] = longest;
                        q.push(t);
                        res = max(longest, res);
                    }
                }
            }
        }
        return res;
    }
};