class Solution {
public:
    vector<int> findRightInterval(vector<vector<int>>& intervals) {
        map<int, int> sv;
        vector<int> res(intervals.size(), -1);
        for (int i = 0; i < intervals.size(); i++) {
            sv.emplace(intervals[i][0], i);//start value: index
        }
        for (int i = 0; i < intervals.size(); i++) {
            auto lb = sv.lower_bound(intervals[i][1]);//first sv >= ending index
            if (intervals[i][0] == intervals[i][1]) {// a point

                res[i] = lb->second;
            }
            if (lb != sv.end() && lb->second != i) {
                res[i] = lb->second;
            }

        }
        return res;
    }
};