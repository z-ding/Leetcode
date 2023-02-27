class Solution {
public:
    int rl = 1;
    int max_len = 0;
    string best_str;
    string longestPalindrome(string s) {
        //result with odd number length  
        for (int i = 0; i < s.size(); i++) {
            while (i - rl >= 0 && i + rl < s.size() && s[i - rl] == s[i + rl]) {
                if (2 * rl + 1 > max_len) {
                    max_len = 2 * rl + 1;
                    best_str = s.substr(i - rl, 2 * rl + 1);
                }
                rl++;
            }
            rl = 1;
        }
        rl = 0;
        //result with even number length
        for (int i = 0; i < s.size(); i++) {
            while (i - rl >= 0 && i + rl + 1 < s.size() && i + 1 < s.size() && s[i - rl] == s[i + 1 + rl]) {
                if (2 * rl + 2 > max_len) {
                    max_len = 2 * rl + 2;
                    best_str = s.substr(i - rl, 2 * rl + 2);
                }
                rl++;
            }
            rl = 0;
        }
        if (best_str.size() == 0) {
            best_str = s.substr(0, 1);
        }
        return best_str;
    }
};