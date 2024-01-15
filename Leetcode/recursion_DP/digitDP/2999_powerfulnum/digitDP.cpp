class Solution {
public:
    long long dfs(string n, int digit, int limit, string s, int x, bool equal) {
        if (digit == 0) return 0ll;
        //cout << n << "," << digit << "," << equal<<endl;
        if (digit == s.size()) {
            int idx = n.size() - digit;
            if (equal) {
                //cout << idx<< endl;
                if (n.substr(idx) < s) return 0ll;
            }
            return 1ll;
        }
        long long count = 0;
        if (equal) {
            int idx = n.size() - digit;
            int d = stoi(n.substr(idx, 1));
            if (d <= limit) {
                count += (long long)(d)*dfs(n, digit - 1, limit, s, x, 0);//0-d-1
                count += dfs(n, digit - 1, limit, s, x, 1);//==d
            }
            else count += (long long)(1 + limit) * dfs(s, digit - 1, limit, s, x, 0);

        }
        else {
            count += (long long)(1 + limit) * dfs(n, digit - 1, limit, s, x, 0);
        }
        return count;
    }
    long long helper(long long n, int limit, string suf) {
        string s = to_string(n);
        int m = s.size();
        if (m < suf.size()) return 0ll;
        if (m == suf.size()) {
            if (suf <= s) return 1ll;
            return 0ll;
        }
        int f = stoi(s.substr(0, 1));
        long long res = 0;
        //first digit
        if (f <= limit) {//0-f-1, f f>=1
            res += (long long)f * dfs(s, m - 1, limit, suf, suf.size(), 0);//0-f-1
            //cout <<res << endl;
            res += dfs(s, m - 1, limit, suf, suf.size(), 1);//f
        }
        else {//f > limit, 0-limit is okay
            res += (long long)(1 + limit) * dfs(s, m - 1, limit, suf, suf.size(), 0);
        }
        return res;
    }
    long long numberOfPowerfulInt(long long start, long long finish, int limit, string s) {
        long long x = helper(finish, limit, s);
        long long y = helper(start - 1, limit, s);
        //cout << x <<","<< y << endl;
        return x - y;
    }
};