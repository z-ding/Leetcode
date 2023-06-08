class Solution {
public:
    vector<vector<int>> memo;
    int dfs(int r, int c, vector< multiset<pair<int, int>>>& rows, vector< multiset<pair<int, int>>>& cols, vector<vector<int>>& mat) {
        if (memo[r][c] != -1) return memo[r][c];
        auto it_r = rows[r].find({ mat[r][c],c });
        auto it_c = cols[c].find({ mat[r][c],r });
        it_r++;//next bigger item in the same row
        it_c++; //next bigger item in the same col
        int l1 = 1; int l2 = 1;
        //cout << r << "," << c << endl;
        while (it_r != rows[r].end() && mat[r][it_r->second] == mat[r][c]) {
            it_r++;
        }
        if (it_r != rows[r].end()) {
            int va = mat[r][it_r->second];
            vector< multiset<pair<int, int>>::iterator> v = { it_r };
            it_r++;
            while (it_r != rows[r].end() && mat[r][it_r->second] == va) {
                v.push_back(it_r);
                it_r++;
            }
            for (int i = 0; i < v.size(); i++) {
                int l = 1 + dfs(r, v[i]->second, rows, cols, mat);
                l1 = max(l, l1);
            }

        }
        while (it_c != cols[c].end() && mat[it_c->second][c] == mat[r][c]) {
            it_c++;
        }
        if (it_c != cols[c].end()) {
            int va = mat[it_c->second][c];
            vector< multiset<pair<int, int>>::iterator> v = { it_c };
            it_c++;
            while (it_c != cols[c].end() && mat[it_c->second][c] == va) {
                v.push_back(it_c);
                it_c++;
            }
            //cout <<"col" << endl;
            for (int i = 0; i < v.size(); i++) {
                int l = 1 + dfs(v[i]->second, c, rows, cols, mat);
                l2 = max(l2, l);
            }

        }
        memo[r][c] = max(l1, l2);
        return memo[r][c];
    }
    int maxIncreasingCells(vector<vector<int>>& mat) {
        multiset<pair<int, int>> m;
        vector< multiset<pair<int, int>>> rows(mat.size(), m);//for each row: val, col number
        vector< multiset<pair<int, int>>> cols(mat[0].size(), m);//for each col: val, row number
        for (int i = 0; i < mat.size(); i++) {
            for (int j = 0; j < mat[0].size(); j++) {
                //mat[i][j] belongs to i th row and j th col
                int val = mat[i][j];
                rows[i].insert({ val,j });
                cols[j].insert({ val,i });
            }
        }
        /*
        for (int i=0; i< rows.size();i++){
            for (auto &e: rows[i]){
                cout << e.first << "," << e.second << " | " ;
            }
            cout << endl;
        }

        for (int i=0; i< cols.size();i++){
            for (auto &e: cols[i]){
                cout << e.first << "," << e.second << " | " ;
            }
            cout << endl;
        }*/
        int res = 0;
        vector<int> v(mat[0].size(), -1);
        for (int i = 0; i < mat.size(); i++) {
            memo.push_back(v);
        }
        for (int i = 0; i < mat.size(); i++) {
            for (int j = 0; j < mat[0].size(); j++) {
                int cur = dfs(i, j, rows, cols, mat);
                //cout << i << j << "," << cur << endl;
                res = max(cur, res);
            }
        }
        return res;
    }
};