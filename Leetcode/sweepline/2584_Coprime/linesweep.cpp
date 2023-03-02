class Solution {
public:
    //prime number from 1 to 1000
    vector<int> prime = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,
229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,503,509,521,523,541,547,557,563,569,571,577,587,593,599,601,607,613,617,619,631,641,643,647,653,659,661,673,677,683,691,701,709,719,727,733,739,743,751,757,761,769,773,787,797,809,811,821,823,827,829,839,853,857,859,863,877,881,883,887,907,911,919,929,937,941,947,953,967,971,977,983,991,997 };
    set<int> largeprime; //prime number over 1000
    int res = 100000;

    int findValidSplit(vector<int>& nums) {
        //cout << nums[334] << "," << nums[335] << endl;
        if (nums.size() == 1) {
            return -1;
        }
        //find the appearing range of each prime number in nums [first appearance, last apperance]
        //e.g. if 3 appeared in index 2 and 4, index 2-4 can't be split into two arrays
        unordered_map<int, pair<int, int>> range;
        for (int i = 0; i < nums.size(); i++) {
            int cur = nums[i];
            if (cur == 1) {
                continue;
            }
            bool isprime = true;
            //cout << nums[i] << ":" << endl;
            for (int j = 0; j < prime.size(); j++) {
                if (prime[j] > cur) {
                    break;
                }
                if (cur % prime[j] == 0) {
                    isprime = false;
                    if (range.find(prime[j]) == range.end()) {
                        pair<int, int> p = { i,i };//first time appearing
                        range.emplace(prime[j], p);
                    }
                    else {
                        int cur_start = range[prime[j]].first;
                        int cur_end = range[prime[j]].second;
                        //cout << cur_start << "," << cur_end<< endl;
                        range[prime[j]].first = min(cur_start, i);
                        range[prime[j]].second = max(cur_end, i);
                    }
                }
            }
            if (isprime) {
                largeprime.insert(cur);
            }
        }
        for (int i = 0; i < nums.size(); i++) {
            int cur = nums[i];
            if (cur < 1000) {
                continue;
            }
            //cout << nums[i] << ":" << endl;
            for (auto& e : largeprime) {
                if (cur < e) {
                    break;
                }
                if (cur % e == 0) {
                    if (range.find(e) == range.end()) {
                        pair<int, int> p = { i,i };//first time appearing
                        range.emplace(e, p);
                    }
                    else {
                        int cur_start = range[e].first;
                        int cur_end = range[e].second;
                        //cout << cur_start << "," << cur_end<< endl;
                        range[e].first = min(cur_start, i);
                        range[e].second = max(cur_end, i);
                    }
                }
            }

        }
        /*now we have a bunch of intervals that can not be placed togher. e.g.
                         ----
              ----
            --------
                -------
        if we +1 for each interval start and -1 for each interval end, we get a line like
            1 2 3 2  1 0 1   0
        we can seperate the array whereever there is a 0
        */
        unordered_map<int, int> count;
        for (auto& e : range) {
            count[e.second.first]++;
            count[e.second.second]--;
            //cout << e.first << ":" << e.second.first << "," << e.second.second << endl;

        }
        //for (auto &e: count){
            //cout <<  e.first << "," << e.second  << endl;
        //}
        vector<int> res(nums.size(), 0);
        int ttl = 0;
        for (int i = 0; i < nums.size(); i++) {
            ttl += count[i];
            res[i] = ttl;
        }
        for (int i = 0; i < res.size() - 1; i++) {
            //cout << i << "," << res[i] << endl;
            if (res[i] == 0) {
                return i;
            }
        }

        return -1;
    }
};