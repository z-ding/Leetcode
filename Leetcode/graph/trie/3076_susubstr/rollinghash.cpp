class Solution {
public:
    vector<string> shortestSubstrings(vector<string>& arr) {
        //brute force complexity 100*(20*20*100*20)
        //store all substring in rolling hash 20*20*100 ; search for each string 20*20*100
        long long p = 31;
        long long mod = 1000000009;
        vector<long long> power(21, 1);
        for (int i = 1; i < 21; i++) {
            power[i] = power[i - 1] * p % mod;
        }
        unordered_map<long long, int> mp;
        for (auto& x : arr) {
            for (int i = 0; i < x.size(); i++) {
                long long hash = 0;
                for (int j = i; j < x.size(); j++) {
                    //calculate rolling hash of each substr and store it in hash set
                    hash = hash + (long long)(x[j] - 'a' + 1) * power[j - i] % mod;
                    mp[hash]++;
                }
            }
        }
        vector<string> res(arr.size(), "");
        // vector<long long> a;    
        //vector<vector<long long>> v(arr.size(), a);
        for (int k = 0; k < arr.size(); k++) {
            string x = arr[k];
            int len = 10000;
            int left = -1;
            int right = -1;
            for (int i = 0; i < x.size(); i++) {
                long long hash = 0;
                for (int j = i; j < x.size(); j++) {
                    //calculate rolling hash of each substr and store it in hash set
                    hash = hash + (long long)(x[j] - 'a' + 1) * power[j - i] % mod;
                    //v[k].push_back(hash);
                    mp[hash]--;
                }
            }
            int idx = -1;
            for (int i = 0; i < x.size(); i++) {
                long long hash = 0;
                for (int j = i; j < x.size(); j++) {
                    if (len != 10000 && j - i + 1 > len) break;
                    hash = hash + (long long)(x[j] - 'a' + 1) * power[j - i] % mod;
                    if (mp[hash] == 0) {
                        //cout << k << ":" << i << j << endl;              
                        if (j - i + 1 < len) {
                            len = j - i + 1;
                            left = i;
                            right = j;
                        }
                        else if (j - i + 1 == len) {
                            bool rep = false;
                            int d = 0;
                            for (int cur = i; cur <= j; cur++) {
                                int comp = left + d;
                                if (x[cur] < x[comp]) {
                                    rep = true;
                                    break;
                                }
                                else if (x[cur] > x[comp]) break;
                                d++;
                            }
                            if (rep) {
                                left = i;
                                right = j;
                            }
                        }
                    }
                }
            }

            for (int i = 0; i < x.size(); i++) {
                long long hash = 0;
                for (int j = i; j < x.size(); j++) {
                    //calculate rolling hash of each substr and store it in hash set
                    hash = hash + (long long)(x[j] - 'a' + 1) * power[j - i] % mod;
                    //v[k].push_back(hash);
                    mp[hash]++;
                }
            }
            if (len < 10000) res[k] = x.substr(left, len);
        }
        return res;
    }
};