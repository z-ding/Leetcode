class Solution {
public:
    vector<long long> power;
    const long long p = 31;
    long long mod = 1e9 + 9;
    long long findhash(string& x) {
        long long res = 0LL;
        for (int i = 0; i < x.size(); i++) {
            res = (res + (x[i] - 'a') * power[i] % mod) % mod;
        }
        return res;
    }
    vector<int> findindeces(vector<long long>& hash_s, long long hash_t, int m) {
        vector<int> idx;
        //cout << "h" << hash_t << "," << m << endl;
        for (int i = 1; i < hash_s.size(); i++) {
            if (i + m - 1 >= hash_s.size()) break;
            //cout << hash_s[i+m-1] << "," << hash_s[i-1] << endl;
            long long hash = (hash_s[i + m - 1] + mod - hash_s[i - 1]) % mod;
            if (hash == hash_t * power[i - 1] % mod) {
                idx.push_back(i - 1);
            }
        }
        return idx;
    }
    vector<int> beautifulIndices(string s, string a, string b, int k) {
        //precompute power
        if (s.size() < a.size() || s.size() < b.size()) return {};
        power.push_back(1ll);//26 ^ 0
        for (int i = 1; i < s.size(); i++) {
            long long x = power.back() * p % mod;
            power.push_back(x);
        }
        //calculate hash value of string a & b
        auto hash_a = findhash(a);
        auto hash_b = findhash(b);
        //cout << hash_a << "," << hash_b << endl;
        // calculate the prefix hash values for the string `s`
        vector<long long> hash_s(s.size() + 1, 0);
        for (int i = 0; i < s.size(); i++) {
            hash_s[i + 1] = hash_s[i] + (s[i] - 'a') * power[i] % mod;
        }
        auto v1 = findindeces(hash_s, hash_a, a.size());
        auto v2 = findindeces(hash_s, hash_b, b.size());
        vector<int> res;
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