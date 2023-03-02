class Solution {
public:
    //prime number from 1 to 1000
    vector<int> prime = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,
229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,503,509,521,523,541,547,557,563,569,571,577,587,593,599,601,607,613,617,619,631,641,643,647,653,659,661,673,677,683,691,701,709,719,727,733,739,743,751,757,761,769,773,787,797,809,811,821,823,827,829,839,853,857,859,863,877,881,883,887,907,911,919,929,937,941,947,953,967,971,977,983,991,997 };
    int res = 100000;
    void dfs(int pos, vector<unordered_set<int>>& factors, int checkpos, bool can, vector<unordered_set<int>>& f, vector<int>& nums) {//until clearpos there is no conflict
        //cout << pos << ";" << checkpos << ": " << can << endl;
        if (pos == factors.size()) {
            if (can) {
                res = min(res, checkpos);
            }
            return;
        }
        bool together = false;
        if (nums[pos] != 1) {
            for (int i = 0; i <= checkpos; i++) {
                if (nums[i] == 1) {
                    continue;
                }
                if (nums[pos] % nums[i] == 0 || nums[i] % nums[pos] == 0) {
                    together = true;
                    break;
                }
            }
            if (!together) {
                for (auto& e : f[pos]) {
                    if (factors[checkpos].find(e) != factors[checkpos].end()) {
                        //must place this position together with the previous array
                        //cout <<"failed " << checkpos << ":" << e << endl;
                        together = true;
                        break;
                    }
                }
            }
        }


        if (together) {
            dfs(pos + 1, factors, pos, false, f, nums);
        }
        else {//we can seperate this pos with previous array, check next position
            //cout << "passed " << endl;
            dfs(pos + 1, factors, checkpos, true, f, nums);
        }
        return;
    }
    int findValidSplit(vector<int>& nums) {
        if (nums.size() == 1) {
            return -1;
        }
        unordered_set<int> u;
        vector<unordered_set<int>> f(nums.size(), u);//current pos
        vector<unordered_set<int>> factors(nums.size(), u);//cumu
        for (int i = 0; i < nums.size(); i++) {
            if (i > 0) {
                factors[i] = factors[i - 1];
            }
            int cur = nums[i];
            for (int j = 0; j < prime.size(); j++) {
                if (prime[j] > cur) {
                    break;
                }
                if (cur % prime[j] == 0) {
                    f[i].emplace(prime[j]);
                    if (factors[i].find(prime[j]) == factors[i].end()) {
                        factors[i].emplace(prime[j]);
                        //cout << i << ":" << prime[j] << "emplaced " << endl;
                    }
                }
            }
        }
        dfs(1, factors, 0, false, f, nums);
        if (res == 100000) {
            return -1;
        }
        return res;
    }
};