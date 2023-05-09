class Solution {
public:
    class UF {
    public:
        vector<int> par;
        vector<int> rank;
        int seperate;//number of seperate component
        UF(int n) {
            for (int i = 0; i <= n; i++) {
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


    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
        sort(edges.begin(), edges.end(), [](vector<int>& a, vector<int>& b) {
            return a[0] > b[0];//build the graph with type 3 edges first
            });
        UF* alice = new UF(n);
        UF* bob = new UF(n);
        int cnt = 0;//edges needed
        for (int i = 0; i < edges.size(); i++) {
            if (edges[i][0] == 3) {//add to both alice and bob
                cnt += alice->unionnodes(edges[i][1], edges[i][2]) | bob->unionnodes(edges[i][1], edges[i][2]);
            }
            else if (edges[i][0] == 2) {
                cnt += bob->unionnodes(edges[i][1], edges[i][2]);
            }
            else {
                cnt += alice->unionnodes(edges[i][1], edges[i][2]);
            }
        }
        if (bob->isConnected() && alice->isConnected()) {
            return edges.size() - cnt;
        }
        return -1;
    }
};