class Solution {
public:
    class UF {
    public:
        vector<int> par;
        vector<int> rank;
        int seperate;//number of seperate component
        UF(int n) {
            for (int i = 0; i < n; i++) {
                par.push_back(i);
                rank.push_back(0);
            }
            seperate = n;
        }
        int findfather(int x) {
            while (x != par[x]) {
                par[x] = par[par[x]];
                x = par[x];
            }
            return x;
        }
        int unionnodes(int x1, int x2) {//return 0 if the two component is already connected, 1 otherwise (union success)
            int p1 = findfather(x1);
            int p2 = findfather(x2);
            if (p1 == p2) {
                return 0;
            }
            if (rank[p1] > rank[p2]) {
                rank[p1] += rank[p2];
                par[p2] = p1;
            }
            else {
                rank[p2] += rank[p1];
                par[p1] = p2;
            }
            seperate -= 1;
            return 1;
        }
        bool isConnected() {
            return seperate <= 1;
        }
    };
    int latestDayToCross(int row, int col, vector<vector<int>>& cells) {
        //create a dummy source node and dummy destination node
        //if first row becomes land, connect it to source node, same for last row
        vector<vector<int>> grid(row, vector<int>(col, 1));
        int n = row * col + 2;//total node needed
        UF* u = new UF(n);
        //on last day, everything is water, so starting from last-1 day
        //cells[i] is land on day i-1;
        //node index (0 based): (row-1)*width+col
        vector<int> dir = { 0,1,0,-1,0 };
        for (int i = cells.size() - 1; i >= 0; i--) {
            int index = (cells[i][0] - 1) * col + cells[i][1];
            //cout <<"this" << cells[i][0]-1 << "," << cells[i][1]-1 << ":" << index <<endl;
            grid[cells[i][0] - 1][cells[i][1] - 1] = 0;
            if (cells[i][0] == 1) {//first row
                u->unionnodes(index, 0);
            }
            if (cells[i][0] == row) {//last row row
                u->unionnodes(index, n - 1);
            }
            for (int j = 0; j < 4; j++) {
                int nextr = cells[i][0] - 1 + dir[j];
                int nextc = cells[i][1] - 1 + dir[j + 1];
                int nexti = nextr * col + nextc + 1;
                if (nextr < 0 || nextc < 0 || nextr == row || nextc == col || grid[nextr][nextc] == 1) continue;
                //cout <<"next" << nextr << "," << nextc << ":" << nexti <<endl;
                u->unionnodes(index, nexti);
            }
            if (u->findfather(0) == u->findfather(n - 1)) return i;
        }
        return -1;
    }
};