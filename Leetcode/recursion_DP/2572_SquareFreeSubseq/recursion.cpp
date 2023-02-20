class Solution {
public:
    unordered_set<int> sq;
    unordered_set<int> cur;
    vector<vector<long long>> c_memo;
    inline long long combination(int ttl, int target, int cur) {
        //cout << cur << "," << ttl << "," << target << endl;
        if (c_memo[cur][target] != -1) {
            return c_memo[cur][target];
        }
        if (target == 0) {
            c_memo[cur][target] = 1;
            return 1;
        }
        if (cur == ttl - target) {//has to choose all elements
            c_memo[cur][target] = 1;
            return 1;
        }
        long long c = 0;
        //choose this one
        c += combination(ttl, target - 1, cur + 1) % 1000000007;
        //not choose this one
        c += combination(ttl, target, cur + 1) % 1000000007;
        c_memo[cur][target] = c;
        return c;
    }
    int subset(vector<int>& nums, vector<long long>& count, vector<unordered_set<int>>& divider, int pos) {
        //cout << pos << endl;
        if (pos == nums.size()) {
            return 0;
        }
        long long op1 = 0;
        long long op2 = 0;
        bool inc = true;


        //nums[pos] is not a multiple of square number
        //take nums[pos]
        //add all divider of nums[pos] to the current divider set
        unordered_set<int> copy = cur;
        for (auto& e : divider[nums[pos]]) {
            if (cur.find(e) == cur.end()) {
                cur.emplace(e);
            }
            else {//adding nums[pos] to the current choice will make it a multiple of square number, don't add this position and check next position
                inc = false;
                break;
            }

        }
        if (inc) {
            //cout << "include" << nums[pos] << "," << cur.size() <<endl;
            op1 = (long long)(count[pos]) + (long long)(count[pos]) * (long long)(subset(nums, count, divider, pos + 1));// take any one from nums[pos]
        }
        cur = copy; //backtracking

        //cout << "exclude" << nums[pos] << endl;
        op2 = subset(nums, count, divider, pos + 1);//not take nums[pos]
        //cout << pos << op1 << op2 << endl;

        //memo[pos].emplace(index,op1+op2);
        return (op1 + op2) % 1000000007;
    }
    int squareFreeSubsets(vector<int>& nums) {
        vector<int> li = { 4,8,9,12,16,18,20,24,25,27,28 };
        for (int i = 0; i < li.size(); i++) {
            sq.emplace(li[i]);
        }

        vector<int> v = { 2,3,5,7,11,13,17,19,23,29 };
        unordered_set<int> u;
        vector<unordered_set<int>> divider(31, u);
        for (int i = 1; i <= 30; i++) {
            for (int j = 0; j < v.size(); j++) {
                if (i % v[j] == 0) {
                    divider[i].emplace(v[j]);
                }
            }
        }
        unordered_map<int, int> freq;
        for (int i = nums.size() - 1; i >= 0; i--) {
            if (sq.find(nums[i]) != sq.end()) {
                nums.erase(nums.begin() + i);
                continue;
            }

            if (freq.find(nums[i]) == freq.end()) {
                freq.emplace(nums[i], 1);
            }
            else {
                freq[nums[i]]++;
            }
        }

        vector<int> elem;
        vector<long long> count;
        long long multiplier = 0;
        for (auto& e : freq) {
            if (e.first == 1) {//we can choose any combination of 1 
                vector<long long> tmp(e.second + 1, -1);
                for (int i = 0; i <= e.second; i++) {
                    c_memo.push_back(tmp);
                }
                for (int n = 1; n <= e.second; n++) {//choose how many of 1
                    //cout << n << "target" << endl;
                    multiplier += combination(e.second, n, 0);
                    //cout << multiplier << "combination found" << endl;
                }
                //cout << multiplier << endl;
                elem.push_back(e.first);
                count.push_back(multiplier);
                continue;
            }
            elem.push_back(e.first);
            count.push_back(e.second);
        }

        return subset(elem, count, divider, 0);


    }
};