class Solution {
public:
    /*
    Iterators, pointers and references referring to elements removed by the function are invalidated. All other iterators, pointers and references keep their validity.
so s.erase(it) invalides it.
s.erase(it++) works, because it++ returns copy of iterator. For example,++it wouldn't work.
    */
    int minimumVisitedCells(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<set<int>> rows(m);//a set for each column to record which rows are unvisited
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                rows[i].insert(j);//in the beginning, rows 0,1,2,... n-1 are unvisited
            }
        }
        vector<set<int>> cols(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cols[i].insert(j);
            }
        }
        rows[0].erase(0);
        cols[0].erase(0);
        queue<pair<int, int>> q;
        q.push({ 0, 0 });
        int steps = 1;
        while (!q.empty()) {
            int s = q.size();
            while (s--) {
                auto [r, c] = q.front();
                q.pop();
                //cout << r << "," << c << ":" << steps << endl;
                if (r == n - 1 and c == m - 1) return steps;
                auto it = rows[c].lower_bound(r + 1);//next unvisited row in column c
                while (it != rows[c].end() && *it <= r + grid[r][c]) {
                    q.push({ *it,c });
                    cols[*it].erase(c);
                    rows[c].erase(it++);

                }
                it = cols[r].lower_bound(c + 1);
                while (it != cols[r].end() && *it <= c + grid[r][c]) {
                    q.push({ r,*it });
                    rows[*it].erase(r);
                    cols[r].erase(it++);
                    /*
                    cout << c << "erasing " << endl;
                    for (auto &e: cols[0]){
                        cout << e << " " ;
                    }
                    cout << endl;*/
                }
            }
            steps++;
        }
        return -1;
    }
};