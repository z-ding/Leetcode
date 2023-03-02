class Solution {
public:
    /*
    1 2  3   4... should be converted to binary to check combinations of number that's been chosen easly
    1 10 100 1000...
    i << i-1 (i == the number chosen by a player)
    */
    unordered_map<int, bool> u;
    vector<unordered_map<int, bool>> memo = { u,u };
    bool win(int limit, int target, int turn, int sum, int chosen) {
        //cout << "chosen " << chosen <<  "turn " << turn << "cur sum " << sum << endl;
        if (memo[turn].find(chosen) != memo[turn].end()) {
            return memo[turn][chosen];
        }
        if (sum >= target) {
            if (turn == 0) {//player2 win, player 1 will retry           
                memo[turn].emplace(chosen, false);
                return false;
            }
            memo[turn].emplace(chosen, true);
            return true;
        }
        if (turn == 0) {//first player's turn
            for (int i = 1; i <= limit; i++) {
                if (((1 << (i - 1)) & chosen) == 0) {//i is not chosen yet, try this i
                    //cout << "player 1 try " << i << " when " << chosen <<endl;
                    if (win(limit, target, 1, sum + i, (1 << (i - 1)) | chosen)) {
                        //cout << "player 1 chose " << i << ":" << combi << "," << sum+i << endl;
                        memo[turn].emplace(chosen, true);
                        return true;
                    }
                    //else: player 1 can't win by choose i, he will try next possible number
                }
            }
            //can't win by choosing any number
            memo[turn].emplace(chosen, false);
            return false;
        }
        else {
            for (int i = 1; i <= limit; i++) {
                if (((1 << (i - 1)) & chosen) == 0) {//i is not chosen yet, try this i
                    //cout << "player 2 try " << i << " when " << chosen <<endl;
                    if (!win(limit, target, 0, sum + i, (1 << (i - 1)) | chosen)) {
                        memo[turn].emplace(chosen, false);
                        return false;
                    }
                    //else: player 1 can't win by choose i, he will try next possible number
                }
            }
            memo[turn].emplace(chosen, true);
            return true;
        }
    }
    bool canIWin(int maxChoosableInteger, int desiredTotal) {
        if (maxChoosableInteger >= desiredTotal) {
            return true;
        }
        if (maxChoosableInteger * (maxChoosableInteger + 1) / 2 < desiredTotal) {
            return false;
        }
        return win(maxChoosableInteger, desiredTotal, 0, 0, 0);
    }
};