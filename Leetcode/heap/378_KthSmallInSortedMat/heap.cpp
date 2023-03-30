class Solution {
public:
    typedef tuple<int, int, int> t;
    inline bool push(vector<vector<int>>& matrix, int x, int y) {
        if (x == matrix.size() || y == matrix[0].size()) {
            return false;
        }
        if (matrix[x][y] == INT_MAX) {
            return false;
        }
        return true;
    }
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        priority_queue<t, vector<t>, greater<t>> pq;
        tuple t0 = make_tuple(matrix[0][0], 0, 0);
        pq.push(t0);
        int c = 0;
        int res = matrix[0][0];
        matrix[0][0] = INT_MAX;
        while (!pq.empty() && c < k) {
            int x = get<1>(pq.top());
            int y = get<2>(pq.top());
            c++;
            res = get<0>(pq.top());//k th min number
            //cout << x << y << ";" << res << endl;
            pq.pop();
            if (push(matrix, x + 1, y)) {
                tuple t1 = make_tuple(matrix[x + 1][y], x + 1, y);
                pq.push(t1);
                matrix[x + 1][y] = INT_MAX;//mark pushed number as intmax
            }
            if (push(matrix, x, y + 1)) {
                tuple t1 = make_tuple(matrix[x][y + 1], x, y + 1);
                pq.push(t1);
                matrix[x][y + 1] = INT_MAX;
            }
        }
        return res;
    }
};