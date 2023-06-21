class Solution {
public:
    /*
    critical edge:
        a. if we don't use this edge, the weight of the new MST increases
    pseudo critical edge: if we use this edge, the weight of the MST is minimal. if we don't use this edge, the weight of the new MST is minimal (opposite of critical edge a)
    */
    unordered_set<int> critical;
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
    int findMST(vector<vector<int>>& edges, int n) {
        UF* u = new UF(n);
        int w = 0;
        int e = 0;
        for (int i = 0; i < edges.size(); i++) {
            //cout << edges[i][3] << endl;
            if (edges[i][4] == 0) continue;
            if (u->unionnodes(edges[i][0], edges[i][1])) {
                w += edges[i][2];
                e++;
                if (e == n - 1) return w;
            }
        }
        return 1000000000;
    }
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        //sort the edge list by distance in ascending order, attach an index for each edge
        for (int i = 0; i < edges.size(); i++) {
            edges[i].push_back(i);
            edges[i].push_back(1);//this edge can be use
        }
        sort(edges.begin(), edges.end(), [](vector<int>& a, vector<int>& b) {
            return a[2] < b[2];
            });
        //find a MST using
        int mst = findMST(edges, n);
        //cout << mst << endl;
        //finding critical edge
        vector<vector<int>> res(2, vector<int> {});
        for (int i = 0; i < edges.size(); i++) {
            edges[i][4] = 0;//mark i th edge as not usable
            int x = findMST(edges, n);
            if (x > mst) {
                critical.emplace(edges[i][3]);
                res[0].push_back(edges[i][3]);
            }
            edges[i][4] = 1;
        }
        //finding pseudo critical edges
        for (int i = 0; i < edges.size(); i++) {
            if (critical.find(edges[i][3]) != critical.end()) continue;
            //put i th element in the front
            edges.insert(edges.begin(), edges[i]);
            edges.erase(edges.begin() + i + 1);
            //cout << "mst" << edges[0][3] << endl;
            int x = findMST(edges, n);
            if (x == mst) {
                res[1].push_back(edges[0][3]);
            }
            edges.insert(edges.begin() + i + 1, edges[0]);
            edges.erase(edges.begin());
        }
        return res;
    }
};