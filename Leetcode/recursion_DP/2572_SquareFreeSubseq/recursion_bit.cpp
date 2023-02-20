class Solution {
public:
    unordered_set<int> sq{ 4,8,9,12,16,18,20,24,25,27,28 };//multiple of square numbers
    int cur = 0;
    long long subset(vector<int>& nums, vector<long long>& count, vector<int>& divider, int pos) {
        if (pos == nums.size()) {
            return 0;
        }
        long long op1 = 0;
        long long op2 = 0;
        //nums[pos] is not a multiple of square number
        //take nums[pos]
        //add all divider of nums[pos] to the current divider set
        int prev = cur;
        if ((cur & divider[nums[pos]]) == 0) {//there are no duplicated prime factors in current combination and the new divider
            cur = cur | divider[nums[pos]];
            op1 = count[pos] % 1000000007 + count[pos] % 1000000007 * subset(nums, count, divider, pos + 1);// take any one from nums[pos]
            cur = prev;//backtracking
        }
        op2 = subset(nums, count, divider, pos + 1);//not take nums[pos]  % 1000000007
        //cout << pos << op1 << op2 << endl;
        return (op1 + op2) % 1000000007;
    }
    int squareFreeSubsets(vector<int>& nums) {
        vector<int> v = { 2,3,5,7,11,13,17,19,23,29 };
        unordered_map<int, int> index;
        for (int i = 0; i < v.size(); i++) {
            index.emplace(v[i], pow(2, i));//gove each prime number < 30 a index of power of 2
        }
        vector<int> divider(31, 0);// the prime factor of each number from 1 to 30
        for (int i = 1; i <= 30; i++) {
            for (int j = 0; j < v.size(); j++) {
                if (i < j) {
                    continue;
                }
                if (i % v[j] == 0) {//combine all prime factors into a binary number like 1010101
                    divider[i] = index[v[j]] | divider[i];
                }
            }
            //cout << i << ":" << divider[i] << endl;
        }
        unordered_map<int, int> freq;//count the appearing time of each number in nums
        for (int i = nums.size() - 1; i >= 0; i--) {
            if (sq.find(nums[i]) != sq.end()) {//we can remove square numbers directly
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
        long long multiplier = 1;
        for (auto& e : freq) {
            if (e.first == 1) {//we can choose any combination of 1 
                //multiplier = pow(2,e.second)-1;exceed the limit of long long
                while (e.second) {
                    multiplier = multiplier * 2 % 1000000007;
                    e.second--;
                }
                multiplier--;
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