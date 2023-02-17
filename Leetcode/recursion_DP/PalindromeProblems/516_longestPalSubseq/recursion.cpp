TLE solution(intuive recursion + memorization)
class Solution {
public:
    /*
        take the example abcbca
        we start from first and last index a == a, so the max length is 2 + max length of new substr bcbc
        now the first and last index b != c, so the max length is either the length of new substr bcb or cbc
    */
    unordered_map<string, int> memo;
    //if we use the string as key here and try to memorize it, we will have a TLE since comparing string in hash map is O(length) complexity. scroll down for optimized solution
    int pal(string& s) {
        if (s.size() == 0) {
            return 0;
        }
        if (memo.find(s) != memo.end()) {
            return memo[s];
        }
        if (s.size() == 1) {
            memo.emplace(s, 1);
            return 1;
        }
        int len = 0;
        //s's size is at least 2
        if (s[0] == s.back()) {
            string n;
            if (s.size() > 2) {
                n = s.substr(1, s.size() - 2);
            }
            len = 2 + pal(n);
        }
        else {
            string s1 = s.substr(0, s.size() - 1);
            string s2 = s.substr(1);
            len = max(pal(s1), pal(s2));
        }
        memo.emplace(s, len);
        return len;
    }
    int longestPalindromeSubseq(string s) {
        return pal(s);
    }
};
Optimized solution
class Solution {
public:
    // as we want to memorize the index instead of the string, we should pass in the start index and end index instead of a new substr
    //using the same idea of the TLE solution, we can use i and j to represent the start and ending index of each substring
    int pal(string& s, int i, int j, vector<vector<int>>& memo) {
        if (i > j) {
            return 0;
        }
        if (memo[i][j] != -1) {
            return memo[i][j];
        }
        if (i == j) {
            memo[i][j] = 1;
            return 1;
        }
        int len = 0;
        //s's size is at least 2
        if (s[i] == s[j]) {
            len = 2 + pal(s, i + 1, j - 1, memo);
        }
        else {
            len = max(pal(s, i, j - 1, memo), pal(s, i + 1, j, memo));
        }
        memo[i][j] = len;
        return len;
    }
    int longestPalindromeSubseq(string s) {
        vector<int> v(s.size(), -1);
        vector<vector<int>> memo(s.size(), v);
        return pal(s, 0, s.size() - 1, memo);
    }
};