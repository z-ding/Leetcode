class Solution {
public:
    unordered_map<char, int> window;
    inline bool check(int k, int size) {
        //find out highest freq
        int maxfreq = 0;
        for (auto& w : window) {
            maxfreq = max(maxfreq, w.second);
        }
        if (size - maxfreq <= k) {
            return true;
        }
        else {
            return false;
        }
    }
    int characterReplacement(string s, int k) {
        int res = 0;
        int left = 0;
        int right = 0;
        while (right < s.size()) {
            window[s[right]]++;
            while (!check(k, right - left + 1)) {
                //invalid window, shift left ptr until it's valid
                window[s[left]]--;
                if (!window[s[left]]) {
                    window.erase(s[left]);
                }
                left++;
            }
            res = max(res, right - left + 1);
            right++;
        }
        return res;
    }
};