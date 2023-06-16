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
    bool equationsPossible(vector<string>& equations) {
        //process == and union them into group
        UF* u = new UF(26);
        for (int i = 0; i < equations.size(); i++) {
            if (equations[i][1] == '=') {
                int x1 = int(equations[i][0]) - 97;
                int x2 = int(equations[i][3]) - 97;
                //cout << x1 << x2 << endl;
                u->unionnodes(x1, x2);
            }
        }
        vector<int> parent;
        for (int i = 0; i < 26; i++) {
            int p = i;
            while (p != u->par[p]) {
                p = u->par[p];
            }
            parent.push_back(p);
        }
        for (int i = 0; i < equations.size(); i++) {
            if (equations[i][1] == '!') {
                int x1 = int(equations[i][0]) - 97;
                int x2 = int(equations[i][3]) - 97;
                if (parent[x1] == parent[x2]) return false;
            }
        }
        return true;
    }
};