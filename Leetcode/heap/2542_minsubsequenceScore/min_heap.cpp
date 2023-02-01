class Solution {
public:
    long long maxScore(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<vector<int>> pair;
        /* pair each element in nums1 and nums2 and sort it by decreasing order by num2
            example1
            2,4
            3,3
            1,2
            3,1
        */
        for (int i = 0; i < nums1.size(); i++) {
            vector<int> v;
            v.push_back(nums1[i]);
            v.push_back(nums2[i]);
            pair.push_back(v);
        }
        sort(pair.begin(), pair.end(), [](vector<int>& a, vector<int>& b) {
            return a[1] > b[1];
            });
        long long res = 0;
        long long cursum = 0;
        priority_queue<long long, vector<long long>, greater<long long> > q;
        for (int i = 0; i < pair.size(); i++) {
            q.push(pair[i][0]);
            cursum += pair[i][0];
            if (q.size() > k) {//pop the smallest item
                cursum -= q.top();
                q.pop();
            }
            if (q.size() == k) {
                res = max(res, cursum * pair[i][1]);
            }

        }
        return res;

    }
};