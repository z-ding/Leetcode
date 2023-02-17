class NumMatrix {
public:
    /*
    original matrix. Imaging there are some 0s on top row and left column
    a   b   c               0   0    0    0

    d   e   f               0   a1   b1   c1

    g   h   i               0   d1   e1   f1

                            0   g1   h1   i1


    Presum matrix: each value at position [i,j] represents the rectangle from [0,0] to [i,j] in original matrix
    for each index, we will sum up itself, the number to its left and the number on its top and then minus the number on its topleft since it's added twice (see example e1)
    a1 = a+0+0-0 = a;
    b1 = a1 + 0 + b - 0 = a + b;
    c1 = b1 + 0 + c -0 = a+b+c
    d1 = 0+a1+d-0 = a + d;
    e1 = d1 + b1 + e - a1 = a+d + a+ b +e -a = a +d+b+e;
    f1 = e1 + c1 + f - b1 = a+b+d+e+a+b+c-a-b+f = a+c=b+c+d+e+f;
    ...

    Next we will generate the sum for each combination of r1,r2,c1, c2
         c1    c2
      0   0    0    0

      0   a1   b1   c1

      0   d1   e1   f1  r1

      0   g1   h1   i1  r2

      the r1,r2,c1, c2 above represents the sum of rectangle from d to h
      which can be represented as sum[r2][c2](h1) - sum[r1-1][c2](b1) - sum[r2][c1-1](0) +
      sum[r1-1][c1-1](0)
    */
    vector<vector<int>> sum;
    NumMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size() + 1;
        int n = matrix[0].size() + 1;
        for (int i = 0; i < m; i++) {
            vector<int> v;
            for (int j = 0; j < n; j++) {
                v.push_back(0);
            }
            sum.push_back(v);
        }
        for (int i = 1; i < n; i++) {
            sum[0][i] = 0;//top row
        }
        for (int i = 1; i < m; i++) {
            sum[i][0] = 0; //;left column
        }
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                sum[i][j] = sum[i - 1][j] + sum[i][j - 1] + matrix[i - 1][j - 1] - sum[i - 1][j - 1];
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        //now we are given r1,r2,c1, c2 in original matrix, we can calculate the sum by using the 
        //r1+1,r2+1,c1+1, c2+1 since our sum matrix is bigger than original matrix
        return sum[row2 + 1][col2 + 1] - sum[row1][col2 + 1] - sum[row2 + 1][col1] + sum[row1][col1];
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */