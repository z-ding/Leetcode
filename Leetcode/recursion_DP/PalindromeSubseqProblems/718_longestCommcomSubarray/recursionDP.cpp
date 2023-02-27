class Solution {
public:
    int lrs(vector<int>& nums1, vector<int>& nums2, int i, int j, vector<vector<int>>& memo) {
        if (memo[i][j] != -1) {
            return memo[i][j];
        }
        if (i == nums1.size() || j == nums2.size()) {
            memo[i][j] = 0;
            return 0;
        }
        int l = 0;
        if (nums1[i] == nums2[j]) {
            l = 1 + lrs(nums1, nums2, i + 1, j + 1, memo);
        }
        memo[i][j] = l;
        return l;
    }
    int findLength(vector<int>& nums1, vector<int>& nums2) {

        int res = 0;
        vector<int> v(nums2.size(), 0);
        vector<vector<int>> memo(nums1.size(), v);
        /*
        for (int i=0; i< nums1.size();i++){
            for (int j=0; j< nums2.size();j++){
                int a = lrs(nums1,nums2,i,j,memo);
                res = max(res,a);
            }
        }*/
        for (int i = 0; i < nums1.size(); i++) {
            if (nums1[i] == nums2.back()) {
                memo[i][memo[0].size() - 1] = 1;
            }
        }
        for (int i = 0; i < nums2.size(); i++) {
            if (nums1.back() == nums2[i]) {
                memo[memo.size() - 1][i] = 1;
            }
        }
        for (int i = memo.size() - 2; i >= 0; i--) {
            for (int j = memo[0].size() - 2; j >= 0; j--) {
                if (nums1[i] == nums2[j]) {
                    memo[i][j] = 1 + memo[i + 1][j + 1];
                    res = max(res, memo[i][j]);
                }
            }
        }
        /*
        for (int i=0; i< nums1.size();i++){
            cout << i << endl;
            for (int j=0; j< nums2.size();j++){
                cout << memo[i][j] << ",";
            }
            cout << endl;
        }*/
        return res;
    }
};