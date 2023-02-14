class Solution {
public:
    //visit the 2d vector from lower age to higher age
    // if new age is higher than previous age benchmark, new score must be higher than hurdle, otherwise not choose new age player
    //if a new player is chosen, update age benchmark and score hurdle
    vector<vector<int>> memo;
    int maxscore(vector<vector<int>>& v, int player, int hurdle) {
        int score_c = 0;
        int score_nc = 0;
        //cout << "hurdle " <<  player <<": " << age_benchmark << "," << score_hurdle << endl;
        if (memo[player][hurdle] != -1) {
            return memo[player][hurdle];
        }
        if (player == v.size()) { //out of bound
            memo[player][hurdle] = 0;
            return 0;
        }

        if (v[player][1] > v[hurdle][1]) {
            if (v[player][0] >= v[hurdle][0]) {//choose or not choose new player
                //choose
                score_c = v[player][0] + maxscore(v, player + 1, player);
            }
            //not choose this player
            score_nc = maxscore(v, player + 1, hurdle);
        }
        else { // current player's age is equal to age benchmark, no conflict possible
            score_c = v[player][0] + maxscore(v, player + 1, player);
            score_nc = maxscore(v, player + 1, hurdle);
        }


        int score = max(score_c, score_nc);
        memo[player][hurdle] = score;
        //cout << player << ":" << score_c << "," <<score_nc<< endl;
        return score;
    }
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        vector<vector<int>> v;
        v.push_back({ 0,0 }); //dummy
        for (int i = 0; i < scores.size(); i++) {
            vector<int> tmp = { scores[i],ages[i] };
            v.push_back(tmp);
        }
        sort(v.begin(), v.end(), [](vector<int>& a, vector<int>& b) {
            return a[1] < b[1] || (a[1] == b[1] && a[0] < b[0]); //sort by age, then by score
            });

        for (int i = 0; i <= v.size(); i++) {
            vector<int> t;
            for (int j = 0; j <= v.size(); j++) {
                t.push_back(-1);
            }
            memo.push_back(t);
        }
        //check sorting
        //for (int i=0; i< v.size();i++){
            //cout << v[i][0] << "," << v[i][1] << endl;
        //}


        return maxscore(v, 0, 0);;
    }
};