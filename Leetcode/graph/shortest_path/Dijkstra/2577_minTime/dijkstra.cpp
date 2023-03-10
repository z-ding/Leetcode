class Solution {
public:
    typedef pair<int, int> p;
    typedef pair<int, p> ip;//pair<time, pair<row,col>> -- push to min heap
    priority_queue<ip, vector<ip>, greater<ip> > pq;//min heap of pair<time, pair<row,col>> 
    int minimumTime(vector<vector<int>>& grid) {
        //if we can either jump downwards or rightwards from [0,0] we can jump to the destination since we can jump repeatly between [0,0] and our next step to earn the time we need
        if (grid[0][1] > 1 && grid[1][0] > 1) {
            return -1;
        }
        //from each cell, we can jump to any adjacent cell if it's in bound, in order to reach the destination faster,we should be greedy and choose the adjacent cell with the minimum distance from [0,0] (Dijkstra's Algorithm)
        //here we have one constraint. if t+1 < adjacent cell's value, we need to take adjacent cell's value or adjacent cell's value+1 since we have to jump backwards to kill some time
        vector<int> v(grid[0].size(), 10000000);//initialize as max. value
        vector<vector<int>> time(grid.size(), v);//record min time for each point in the grid
        vector<vector<int>> visited(grid.size(), v);
        //mark the effort of starting point as 0
        time[0][0] = 0;
        p p1 = { 0,0 };
        ip p0 = make_pair(0, p1);
        pq.push(p0); //put starting point to the minheap and start our Algorithm
        while (!pq.empty()) {
            int row = pq.top().second.first;
            int col = pq.top().second.second;
            int t = pq.top().first;
            if (row == grid.size() - 1 && col == grid[0].size() - 1) {//reached
                return t;
            }
            //add it to visited set and pop it
            visited[row][col] = 1;
            pq.pop();
            //examine its unvisited neighbours         
            p right = { row,col + 1 };
            p left = { row, col - 1 };
            p up = { row - 1,col };
            p down = { row + 1,col };
            vector<p> neighbours = { right,left,up,down };
            for (int i = 0; i < neighbours.size(); i++) {
                int r = neighbours[i].first;
                int c = neighbours[i].second;
                if (r >= 0 && r < grid.size() && c >= 0 && c < grid[0].size() && visited[r][c] != 1) {//unvisited neighbour
                    int timeToReach = t + 1;
                    if (timeToReach < grid[r][c]) {//we have to jump around until grid[r][c]
                        if ((grid[r][c] - t) % 2 == 0) {
                            timeToReach = grid[r][c] + 1;//we have to jump even number of times
                        }
                        else {
                            timeToReach = grid[r][c];
                        }
                    }
                    if (timeToReach < time[r][c]) {
                        time[r][c] = timeToReach;
                        //put this node into min heap
                        p p1 = { r,c };
                        ip p0 = make_pair(timeToReach, p1);
                        pq.push(p0);
                    }
                }
            }
        }
        return -1;
    }
};