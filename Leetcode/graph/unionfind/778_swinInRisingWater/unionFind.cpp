class Solution {
public:
    vector<vector<pair<int, int>>> parent;
    vector<vector<int>> rank;
    map<int, pair<int, int>> mp;
    void findparent(vector<vector<int>>& grid, int r, int c, int cellr, int cellc) {

        if (r < 0 || c < 0 || r == grid.size() || c == grid[0].size()) {
            return;
        }
        if (grid[r][c] != -1) {//not a connected cell
            return;
        }
        if (parent[r][c] == parent[cellr][cellc]) {
            return;
        }
        int pr = parent[r][c].first;
        int pc = parent[r][c].second;
        int pr1 = parent[cellr][cellc].first;
        int pc1 = parent[cellr][cellc].second;
        //cout << "checking parent" << pr << "," << pc << ";" << pr1 << "," << pc1 << endl;
        if (rank[pr][pc] >= rank[pr1][pc1]) {//mark current cell's parent as parent[r][c]
            rank[pr][pc] ++;
            rank[pr1][pc1] = 0;
            pair<int, int> p = { pr,pc };
            parent[cellr][cellc] = p;
            findparent(grid, cellr + 1, cellc, cellr, cellc);
            findparent(grid, cellr - 1, cellc, cellr, cellc);
            findparent(grid, cellr, cellc + 1, cellr, cellc);
            findparent(grid, cellr, cellc - 1, cellr, cellc);
        }
        else {//mark all cells with parent {pr,pc}'s parent as current cell -- all neighbouring cell
            rank[pr][pc] = 0;
            rank[pr1][pc1]++;
            pair<int, int> p = { pr1,pc1 };
            parent[r][c] = p;
            findparent(grid, r + 1, c, r, c);
            findparent(grid, r - 1, c, r, c);
            findparent(grid, r, c + 1, r, c);
            findparent(grid, r, c - 1, r, c);
        }
    }
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        for (int i = 0; i < n; i++) {
            vector<pair<int, int>> v;
            vector<int> v1;
            for (int j = 0; j < n; j++) {
                pair<int, int> p = { i,j };
                v.push_back(p);
                v1.push_back(1);
                mp.emplace(grid[i][j], p);//sorted by value in asd order
            }
            parent.push_back(v);
            rank.push_back(v1);
        }
        int t = 0;
        for (auto& e : mp) {
            t = e.first;
            int x = e.second.first;
            int y = e.second.second;
            grid[x][y] = -1;
            findparent(grid, x - 1, y, x, y);
            findparent(grid, x + 1, y, x, y);
            findparent(grid, x, y - 1, x, y);
            findparent(grid, x, y + 1, x, y);
            /*
            cout << t << endl;
            for (int i=0; i< n;i++){
                for (int j=0; j< n;j++){
                    cout << parent[i][j].first << "," << parent[i][j].second << " ; ";
                }
                cout << endl;
            }*/
            if (parent[0][0] == parent[n - 1][n - 1]) {
                return t;
            }
        }
        return -1;
    }
};