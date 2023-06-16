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
    int minCostConnectPoints(vector<vector<int>>& points) {
        //step 0: create edge list with distance to each point
        vector<vector<int>> v;
        for (int i = 0; i < points.size(); i++) {
            for (int j = i + 1; j < points.size(); j++) {
                int d = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
                //from, to, distance
                v.push_back({ i,j,d });
            }
        }
        //step 1: sort the edge list by distance in ascending order
        sort(v.begin(), v.end(), [](vector<int>& a, vector<int>& b) {
            return a[2] < b[2];
            });
        //step 2: choose edge one by one from the lowest distance, add them to the result if there is no cycle, ignore that edge if there is a cycle
        //detect cycle using union find
        int n = v.size();
        if (n == 1) return v[0][2];
        UF* u = new UF(n);
        int edges = 0;
        int res = 0;
        for (int i = 0; i < v.size(); i++) {
            if (u->unionnodes(v[i][0], v[i][1])) {
                //no cycle
                res += v[i][2];
                edges++;
            }
            if (edges == points.size() - 1) break;
        }
        return res;
    }
};