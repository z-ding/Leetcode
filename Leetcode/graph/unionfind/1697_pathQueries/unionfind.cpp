class Solution {
public:
    vector<int> parent;
    vector<int> rank;
    unordered_map<int, vector<int>> mp;
    void findparent(int node) {
        //cout <<"calling " << node << endl;
        for (int i = 0; i < mp[node].size(); i++) {
            int nei = mp[node][i];
            //cout << "checking " << nei << endl;
            if (parent[node] != parent[nei]) {
                if (rank[parent[nei]] >= rank[parent[node]]) {//merge current node to neighbour's parent group
                    rank[parent[node]] = 0;
                    rank[parent[nei]]++;
                    parent[node] = parent[nei];
                    findparent(node);
                }
                else {//merge all nodes in neighbour's group into current node
                    rank[parent[node]]++;
                    rank[parent[nei]] = 0;
                    parent[nei] = parent[node];
                    findparent(nei);
                }
            }
        }
    }
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries) {
        vector<pair<vector<int>, int>> q;
        for (int i = 0; i < queries.size(); i++) {
            pair<vector<int>, int> p = make_pair(queries[i], i);
            q.push_back(p);
        }
        sort(q.begin(), q.end(), [](pair<vector<int>, int>& a, pair<vector<int>, int>& b) {
            return a.first[2] < b.first[2];
            });//sort according to limit in queries
        //union find from the smallest limit, check whether starting point and ending point is connected based on edges smaller than limit
        for (int i = 0; i < n; i++) {
            parent.push_back(i);
            rank.push_back(1);
        }
        sort(edgeList.begin(), edgeList.end(), [](vector<int>& a, vector<int>& b) {
            return a[2] < b[2];
            });
        int index = 0;
        vector<bool> res(queries.size(), false);
        for (int i = 0; i < q.size(); i++) {
            int limit = q[i].first[2];
            //cout << "LIMIT" << limit << endl;
            while (index < edgeList.size() && edgeList[index][2] < limit) {
                mp[edgeList[index][0]].push_back(edgeList[index][1]);
                mp[edgeList[index][1]].push_back(edgeList[index][0]);
                findparent(edgeList[index][0]);
                //findparent(edgeList[index][1]);
                /*
                cout << edgeList[index][0] << "," << edgeList[index][1] << endl;
                for (int i=0; i< parent.size();i++){
                    cout << parent[i] <<";";
                }
                cout << endl;*/
                //for (int i=0; i< parent.size();i++){
                    //cout << rank[i] <<";";
               // }
                //cout << endl;
                index++;
            }
            if (parent[q[i].first[0]] == parent[q[i].first[1]]) {
                res[q[i].second] = true;
            }
        }
        return res;
    }
};

//using UF template
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
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries) {
        vector<pair<vector<int>, int>> q;
        for (int i = 0; i < queries.size(); i++) {
            pair<vector<int>, int> p = make_pair(queries[i], i);
            q.push_back(p);
        }
        sort(q.begin(), q.end(), [](pair<vector<int>, int>& a, pair<vector<int>, int>& b) {
            return a.first[2] < b.first[2];
            });//sort according to limit in queries
        //union find from the smallest limit, check whether starting point and ending point is connected based on edges smaller than limit
        UF* mp = new UF(n);
        sort(edgeList.begin(), edgeList.end(), [](vector<int>& a, vector<int>& b) {
            return a[2] < b[2];
            });
        int index = 0;
        vector<bool> res(queries.size(), false);
        for (int i = 0; i < q.size(); i++) {
            int limit = q[i].first[2];
            while (index < edgeList.size() && edgeList[index][2] < limit) {
                mp->unionnodes(edgeList[index][0], edgeList[index][1]);
                index++;
            }
            if (mp->findfather(q[i].first[0]) == mp->findfather(q[i].first[1])) {

                res[q[i].second] = true;
            }
        }
        return res;
    }
};