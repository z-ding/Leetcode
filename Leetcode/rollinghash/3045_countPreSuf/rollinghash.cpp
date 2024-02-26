class Solution {
public:
    long long countPrefixSuffixPairs(vector<string>& words) {
        vector<vector<int>> wl;
        vector<long long> power;
        const long long p = 31;
        long long mod = 1e9 + 9;
        power.push_back(1ll);//26 ^ 0
        for (int i = 1; i < 100000; i++) {
            long long x = power.back() * p % mod;
            power.push_back(x);
        }
        unordered_map<long long, long long> freq;
        long long res = 0;
        for (int idx = 0; idx < words.size(); idx++) {
            //cout << "idx" << idx << endl;
            long long pcur = 0;
            long long scur = 0;
            int y = words[idx].size();
            //0 --- y-1 power: 0...0
            for (int i = 0; i < y; i++) {
                pcur = (pcur + (long long)(words[idx][i] - 'a' + 1) * power[i]) % mod;
                scur = ((long long)(words[idx][y - 1 - i] - 'a' + 1) + scur * p) % mod;
                //cout << pcur << "," << scur << endl;
                if (pcur == scur && freq.find(pcur) != freq.end()) res += freq[pcur];
            }
            freq[pcur]++;
        }
        return res;
    }
};