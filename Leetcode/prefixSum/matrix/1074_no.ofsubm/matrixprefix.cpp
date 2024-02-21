class Solution {
public:
    /*
                  c1  c2
                x x   x   x
            r1  x o   o   x
            r2  x o   o   x
                x x   x   x
            submatrix sum r1,r2,c1,x2 =
            sum[r2][c2] - sum[r2][c1-1] - sum[r1-1][c2] + sum[r1-1][c1-1]
            if we have a nested for loop for r1 and r2 and iterate in column with a hashmap, we can have the number of submatrices for each r1, r2 combination
    */
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        //prefix sum, prefix[i][j] is the ttl sum of area [0,0] to [i,j]
        vector<vector<int>> prefix = matrix;
        //top row and left col
        for (int i = 1; i < matrix[0].size(); i++)  prefix[0][i] = prefix[0][i - 1] + matrix[0][i];
        for (int i = 1; i < matrix.size(); i++)  prefix[i][0] = prefix[i - 1][0] + matrix[i][0];
        for (int i = 1; i < matrix.size(); i++) {
            for (int j = 1; j < matrix[0].size(); j++) {
                prefix[i][j] = prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1] + matrix[i][j];
            }
        }
        int res = 0;
        /*
        for (int i=0; i< matrix.size(); i++){//r1
            for (int j=0; j< matrix[0].size();j++){//r2
                cout << prefix[i][j] << ",";
            }
            cout << endl;
        }*/
        for (int i = 0; i < matrix.size(); i++) {//r1
            for (int j = i; j < matrix.size(); j++) {//r2
                unordered_map<int, int> freq;
                for (int k = 0; k < matrix[0].size(); k++) {//col
                    //get the sum r1,r2,0,col and check the diff with the target, see whether the diff appeared in hash map before
                    //sum[r2][c2] - sum[r2][c1-1] - sum[r1-1][c2] + sum[r1-1][c1-1] -- c1 ==0
                    int cur = prefix[j][k];
                    if (i > 0) cur -= prefix[i - 1][k];
                    if (cur == target) {
                        // cout << i << ","<< j << "," << k << ":" << "++" << endl;
                        res++;
                    }
                    int t = cur - target;
                    if (freq.find(t) != freq.end()) {
                        res += freq[t];
                        //cout << i << "," << j << "," << k << ": +=" << freq[t] <<  endl;
                    }
                    //cout << i << "," << j << "," << k << ": " << cur << endl;
                    freq[cur]++;
                }
            }
        }
        return res;
    }
};