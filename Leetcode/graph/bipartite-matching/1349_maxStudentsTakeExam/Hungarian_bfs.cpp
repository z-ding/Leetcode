class Solution {
public:
    int maxStudents(vector<vector<char>>& seats) {
        int R = seats.size();
        int C = seats[0].size();
        pair<int, int> ini = { -1,-1 };
        vector<vector<pair<int, int>>> matching(R, vector<pair<int, int>>(C, ini));
        vector<vector<pair<int, int>>> check(R, vector<pair<int, int>>(C, ini));
        vector<vector<pair<int, int>>> prev(R, vector<pair<int, int>>(C, ini));
        queue<pair<int, int>> Q;
        int ans = 0;
        for (int row = 0; row < R; row++) {
            for (int col = 0; col < C; col++) {
                if (seats[row][col] == '.' && matching[row][col].first == -1) {
                    while (!Q.empty()) Q.pop();
                    pair<int, int> p = { row,col };
                    Q.push(p);
                    prev[row][col] = { -1,-1 }; // set row,col as the starting point
                    bool flag = false; // agumenting path not found yet
                    while (!Q.empty() && !flag) {
                        pair<int, int> u = Q.front();
                        int x = u.first;
                        int y = u.second;
                        vector<pair<int, int>> edges =
                        { {x - 1,y - 1},{x,y - 1},{x + 1,y
                        - 1},{x - 1,y + 1},{x,y + 1},{x + 1,y + 1} };
                        for (int i = 0; i < edges.size(); i++) {
                            pair<int, int> v = edges[i];
                            if (v.first < 0 || v.second < 0 || v.first == R || v.second == C || seats[v.first][v.second] != '.' || flag) {
                                continue;
                            }
                            if (check[v.first][v.second] != p) {
                                check[v.first][v.second] = p;
                                Q.push(matching[v.first][v.second]);
                                if (matching[v.first][v.second].first >= 0) { //a matched cell
                                    prev[matching[v.first][v.second].first][matching[v.first][v.second].second] = u;
                                }
                                else { // augumenting path found
                                    flag = true;
                                    pair<int, int> d = u, e = v;
                                    while (d.first != -1) {
                                        pair<int, int> t = matching[d.first][d.second];
                                        matching[d.first][d.second] = e;
                                        matching[e.first][e.second] = d;
                                        d = prev[d.first][d.second];
                                        e = t;
                                    }
                                }
                            }
                        }
                        Q.pop();
                    }
                    if (matching[row][col].first != -1) ++ans;
                }

            }

        }

        int available = 0;
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                if (seats[i][j] == '.') {
                    available++;
                }
            }
        }
        return available - ans;
    }
};