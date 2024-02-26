class Solution {
public:
    class UF {
    public:
        vector<int> par;
        vector<int> rank;
        int seperate;//number of seperate component
        UF(int n, int m) {
            for (int i = 0; i < n; i++) {
                par.push_back(i);
                rank.push_back(1);
            }
            seperate = m;
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
    };
    bool canTraverseAllPairs(vector<int>& nums) {
        if (nums.size() == 1) return true;
        int m = 0;
        for (auto& x : nums) m = max(m, x);
        vector<int> prime(m + 1, 1);
        auto u = new UF(m + 1, nums.size());
        for (int i = 2; i < sqrt(m); i++) {
            if (prime[i] == 1) {//knock out multiple
                for (int j = 2; i * j <= m; j++) {
                    if (prime[i * j] == 1) {
                        prime[i * j] = 0;
                    }
                }
            }
        }
        vector<int> p;
        for (int i = 2; i < m + 1; i++) {
            if (prime[i] == 1) p.push_back(i);
        }
        unordered_map<int, int> s;
        for (auto& x : nums) s[x]++;
        if (s.find(1) != s.end() && s[1] > 1) return false;
        for (auto& x : p) {
            for (int j = 2; j < m + 1; j++) {
                if (j * x >= m + 1) break;
                if (s.find(j * x) != s.end()) {
                    u->unionnodes(x, j * x);
                    //cout << x << "," << j*x << endl;
                }
            }
        }
        int root = -1;
        for (auto& e : s) {
            if (root == -1) root = u->findfather(e.first);
            if (root != -1 && u->findfather(e.first) != root) return false;
        }
        return true;
    }
};