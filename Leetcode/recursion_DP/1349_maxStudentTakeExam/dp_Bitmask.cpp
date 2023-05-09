class Solution {
public:
    bool canPlace(vector<vector<char>>& seats, int r, int c) {
        //check left, right, upper left and upper right if in boundary
        if (c - 1 >= 0) {
            if (r - 1 >= 0) {
                if (seats[r][c - 1] == 's' || seats[r - 1][c - 1] == 's') {
                    return false;
                }
            }
            else {
                if (seats[r][c - 1] == 's') {
                    return false;
                }
            }
        }
        if (c + 1 < seats[0].size()) {
            if (r - 1 >= 0) {
                if (seats[r][c + 1] == 's' || seats[r - 1][c + 1] == 's') {
                    return false;
                }
            }
            else {
                if (seats[r][c + 1] == 's') {
                    return false;
                }
            }
        }
        return true;
    }
    int memo[8][8][255][255];
    int dfs(vector<vector<char>>& seats, int r, int c, int premask, int curmask) {
        //we only need two rows' bitmask
        if (r == seats.size()) {//no more student can be placed
            return 0;
        }

        if (c == seats[0].size()) {//this row fully checked
            return dfs(seats, r + 1, 0, curmask, 0);
        }
        if (memo[r][c][premask][curmask] != -1) {
            return memo[r][c][premask][curmask];
        }
        int s1 = 0; int s2 = 0;
        if (seats[r][c] != '#' && canPlace(seats, r, c)) {
            seats[r][c] = 's';//indicate there is a student here
            s1 = 1 + dfs(seats, r, c + 1, premask, curmask | (1 << c));
            seats[r][c] = '.';//backtracking
        }
        s2 = dfs(seats, r, c + 1, premask, curmask);//not place student here
        memo[r][c][premask][curmask] = max(s1, s2);
        return  memo[r][c][premask][curmask];
    }
    int maxStudents(vector<vector<char>>& seats) {
        memset(memo, -1, sizeof(memo));
        return dfs(seats, 0, 0, 0, 0);
    }
};