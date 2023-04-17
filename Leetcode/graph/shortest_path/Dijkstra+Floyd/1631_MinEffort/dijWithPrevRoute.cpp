class Solution {
public:
    typedef pair<int, int> p;
    typedef pair<int, p> ip;//pair<effort, pair<row,col>> -- push to min heap
    priority_queue<ip, vector<ip>, greater<ip> > pq;//min heap of pair<effort, pair<row,col>> 
    inline int dijkstra(vector<vector<int>>& heights, vector<vector<int>>& efforts, vector<vector<int>>& visited, vector<vector<p>>& prev) {
        while (!pq.empty()) {
            //use the point with lowest distance to the starting point(0,0)
            int row = pq.top().second.first;
            int col = pq.top().second.second;
            int effort = pq.top().first;
            //cout << row << "," << col << ":" <<effort << endl;
            if (row == heights.size() - 1 && col == heights[0].size() - 1) {
                return effort;
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
                if (r >= 0 && r < heights.size() && c >= 0 && c < heights[0].size() && visited[r][c] != 1) {//unvisited neighbour
                    //if the new effort is less than current effort of the neighbour, update it
                    int neweffort = max(effort, abs(heights[r][c] - heights[row][col]));
                    if (neweffort < efforts[r][c]) {
                        efforts[r][c] = neweffort;
                        //put this node into min heap
                        p p1 = { r,c };
                        ip p0 = make_pair(neweffort, p1);
                        pq.push(p0);
                        p p2 = { row,col };
                        prev[r][c] = p2;
                    }
                }
            }
        }
        return 10000000;
    }
    int minimumEffortPath(vector<vector<int>>& heights) {
        vector<int> v(heights[0].size(), 10000000);//initialize as max. value
        vector<vector<int>> effort(heights.size(), v);//record min effort for each point in the grid
        vector<vector<int>> visited(heights.size(), v);
        //mark the effort of starting point as 0
        effort[0][0] = 0;
        p p1 = { 0,0 };
        ip p0 = make_pair(0, p1);
        vector<p> v1(heights[0].size(), p1);
        vector<vector<p>> prev(heights.size(), v1);  //record previous location (not required by the problem)  
        pq.push(p0);//push starting point to the min heap
        int res = dijkstra(heights, effort, visited, prev);
        for (int i = 0; i < prev.size(); i++) {
            for (int j = 0; j < prev[0].size(); j++) {
                cout << prev[i][j].first << "," << prev[i][j].second << ":" << effort[i][j] << " | ";
            }
            cout << endl;
        }
        return res;
    }
};