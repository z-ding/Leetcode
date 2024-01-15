class Solution {
public:
    vector<int> longestPrefixSuffix(string& text, string& needle) {
        int n = needle.size();
        vector<int> lps(n, 0);
        vector<int> indices;
        int idx = 1;
        int prevlps = 0;
        //lps
        while (idx < n) {
            if (needle[idx] == needle[prevlps]) {
                prevlps += 1;
                lps[idx] = prevlps;
                idx++;
            }
            else if (!prevlps) {
                lps[idx] = 0;
                idx += 1;
            }
            else {
                prevlps = lps[prevlps - 1];
            }
        }
        int i = 0;
        int j = 0;
        while (i < text.size()) {
            if (text[i] == needle[j]) {
                i++;
                j++;
            }
            if (j == n) {
                indices.push_back(i - n);
                j = lps[j - 1];
            }
            else if (i < text.size() && text[i] != needle[j]) {
                if (j == 0) i++;
                else j = lps[j - 1];
            }
        }
        return indices;
    }
    vector<int> beautifulIndices(string s, string a, string b, int k) {
        vector<int> res;
        auto v1 = longestPrefixSuffix(s, a);
        auto v2 = longestPrefixSuffix(s, b);
        if (!v2.size()) return res;
        //for (auto &x : v2) cout << x << ",";
        //cout << endl; 
        for (auto& x : v1) {
            //cout <<x << endl;
            auto it1 = upper_bound(v2.begin(), v2.end(), x);//first idx >  in v2
            if (it1 == v2.end()) it1--;
            if (abs(*it1 - x) <= k) {
                res.push_back(x);
                continue;
            }
            auto it2 = lower_bound(v2.begin(), v2.end(), x);//first idx >=  in v2
            if (it2 != v2.end() && *it2 == x) {
                res.push_back(x);
                continue;
            }
            if (it2 != v2.begin()) it2--;//first idx <  in v2
            if (abs(*it2 - x) <= k) {
                res.push_back(x);
            }
        }
        return res;
    }
};