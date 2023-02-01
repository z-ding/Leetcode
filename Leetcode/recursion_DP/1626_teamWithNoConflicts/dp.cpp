class Solution {
public:
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        vector<vector<int>> v;
        for (int i = 0; i < scores.size(); i++) {
            vector<int> tmp = { scores[i],ages[i] };
            v.push_back(tmp);
        }
        sort(v.begin(), v.end(), [](vector<int>& a, vector<int>& b) {
            return a[1] < b[1] || (a[1] == b[1] && a[0] < b[0]); //sort by age, then by score
            });
        /*
        dp[i] -- max score at i th element -- max sum subsequence of 0 to i-1 where no conflict exists


        */

        vector<int> dp(v.size(), 0);
        for (int i = 0; i < v.size(); i++) {
            dp[i] = v[i][0];
            for (int j = 0; j < i; j++) {
                if ((v[j][1] < v[i][1] && v[j][0] <= v[i][0]) || v[j][1] == v[i][1]) {
                    dp[i] = max(dp[i], dp[j] + v[i][0]);
                }
                if (i == 4) {
                    //cout << j << "," << dp[i] << ","  << v[j][1] << "." << v[i][1]<< endl;
                }

            }
            //cout << dp[i] << endl;

        }
        int ret = 0;
        for (int i = 0; i < dp.size(); i++)
            ret = max(ret, dp[i]);

        return ret;;
    }
};