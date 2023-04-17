class Solution {
public:
    typedef vector<int> v;
    inline void pushq(vector<vector<int>>& grid, vector<vector<int>>& cost, int r, int c, int cur, priority_queue<v, vector<v>, greater<v> >& pq) {
        if (r < 0 || c < 0 || r == cost.size() || c == cost[0].size()) {
            return;
        }
        if (cur >= cost[r][c]) {
            return;
        }
        cost[r][c] = cur;
        pq.push({ cur,r,c,grid[r][c] });
        return;
    }
    int minCost(vector<vector<int>>& grid) {
        priority_queue<v, vector<v>, greater<v> > pq;
        v vi(grid[0].size(), 1000);
        vector<v> cost(grid.size(), vi);
        cost[0][0] = 0;
        pq.push({ 0,0,0,grid[0][0] });//cost, row, col,direction
        while (!pq.empty()) {
            int c = pq.top()[0];
            int row = pq.top()[1];
            int col = pq.top()[2];
            int dir = pq.top()[3];
            pq.pop();
            switch (dir) {
            case 1://right
                pushq(grid, cost, row, col + 1, c, pq);
                pushq(grid, cost, row, col - 1, c + 1, pq);
                pushq(grid, cost, row + 1, col, c + 1, pq);
                pushq(grid, cost, row - 1, col, c + 1, pq);
                break;
            case 2://left
                pushq(grid, cost, row, col + 1, c + 1, pq);
                pushq(grid, cost, row, col - 1, c, pq);
                pushq(grid, cost, row + 1, col, c + 1, pq);
                pushq(grid, cost, row - 1, col, c + 1, pq);
                break;
            case 3://down
                pushq(grid, cost, row, col + 1, c + 1, pq);
                pushq(grid, cost, row, col - 1, c + 1, pq);
                pushq(grid, cost, row + 1, col, c, pq);
                pushq(grid, cost, row - 1, col, c + 1, pq);
                break;
            case 4://up
                pushq(grid, cost, row, col + 1, c + 1, pq);
                pushq(grid, cost, row, col - 1, c + 1, pq);
                pushq(grid, cost, row + 1, col, c + 1, pq);
                pushq(grid, cost, row - 1, col, c, pq);
                break;
            }
        }
        return cost.back().back();
    }
};