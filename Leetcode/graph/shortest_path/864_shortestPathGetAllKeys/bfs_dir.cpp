class Solution {
public:
    int shortestPathAllKeys(vector<string>& grid) {
        vector<int> v(grid[0].size(), -1);
        vector<vector<int>> visited(grid.size(), v);//record keys on hand at each cell
        queue<vector<int>> q;//x, y , keys on hand
        int key = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                if (grid[i][j] == '@') {
                    visited[i][j] = 1;
                    q.push({ i,j,0 });
                }
                else if (int(grid[i][j]) >= 97 && int(grid[i][j]) <= 102) {//key
                    key++;
                }
            }
        }
        int step = 0;
        vector<int> dir = { 0,-1,0,1,0 };
        while (!q.empty()) {
            int n = q.size();
            while (n--) {
                int x = q.front()[0];
                int y = q.front()[1];
                int k = q.front()[2];//key combination on hand at pos (x,y)
                //cout << x << y << ":" << k << "step " << step << endl;
                if ((1 << key) - 1 == k) return step;//all keys found
                q.pop();
                for (int i = 0; i < 4; i++) {
                    int x1 = x + dir[i];
                    int y1 = y + dir[i + 1];
                    if (x1 < 0 || y1 < 0 || x1 == grid.size() || y1 == grid[0].size() || grid[x1][y1] == '#') {
                        continue;
                    }
                    if (visited[x1][y1] != -1) {//reached a previous visited cell, only visit the next cell if a new key is found
                        if ((k | visited[x1][y1]) == visited[x1][y1]) continue;
                    }
                    if (grid[x1][y1] >= 'A' && grid[x1][y1] <= 'F') {
                        //lock
                        int lock = int(grid[x1][y1]) - 65;//A-F: 0-5
                        if (((1 << lock) & k) == 0) {//not own corresponding key
                            continue;
                        }
                    }
                    int c = k;
                    if (grid[x1][y1] >= 'a' && grid[x1][y1] <= 'f') {
                        int Key = int(grid[x1][y1]) - 97;
                        c = c | (1 << Key);//update keys on hand
                    }
                    visited[x1][y1] = c;
                    q.push({ x1,y1,c });
                }
            }
            step++;
        }

        return -1;
    }
};