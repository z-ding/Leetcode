class Solution {
public:
    bool dfs(pair<int, int> u, vector<vector<char>>& seats, vector<vector<pair<int, int>>>& check, vector<vector<pair<int, int>>>& matching)
    {
        int x = u.first; int y = u.second;
        vector<pair<int, int>> edges = { {x - 1,y - 1},{x,y - 1},{x + 1,y - 1},{x - 1,y + 1},{x,y + 1},{x + 1,y + 1} };
        for (int i = 0; i < edges.size(); i++) {
            pair<int, int> v = edges[i];
            if (v.first < 0 || v.second < 0 || v.first == seats.size() || v.second == seats[0].size() || seats[v.first][v.second] != '.') {
                continue;
            }
            if (check[v.first][v.second].first == -1) {     // not in alternative path
                check[v.first][v.second] = u; // record in alternative path
                if (matching[v.first][v.second].first == -1 || dfs(matching[v.first][v.second], seats, check, matching)) {
                    // find an augumenting path, record the route and return true
                    matching[v.first][v.second] = u;
                    matching[u.first][u.second] = v;
                    return true;
                }
            }
        }
        return false; // no augumenting path, return false
    }
    int maxStudents(vector<vector<char>>& seats) {
        int R = seats.size();
        int C = seats[0].size();
        pair<int, int> ini = { -1,-1 };
        vector<vector<pair<int, int>>> matching(R, vector<pair<int, int>>(C, ini));
        //vector<vector<pair<int,int>>> prev(R, vector<pair<int,int>>(C, ini));
        queue<pair<int, int>> Q;
        int ans = 0;

        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                pair<int, int> u = { i,j };
                if (seats[i][j] == '.' && matching[u.first][u.second].first == -1) {
                    vector<vector<pair<int, int>>> check(R, vector<pair<int, int>>(C, ini));
                    if (dfs(u, seats, check, matching))
                        ++ans;
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