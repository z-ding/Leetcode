class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](vector<int>& a, vector<int>& b) {
            return a[0] < b[0]; //sort by starting value
            });
        //check whether each adjacent interval has overlap, if yes, remove the one with bigger ending value
        int removed = 0;
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] < intervals[i - 1][1]) {//start < previous end -- overlap
                removed++;
                if (intervals[i][1] > intervals[i - 1][1]) {//remove i
                    //replace i th value with i-1
                    intervals[i][0] = intervals[i - 1][0];
                    intervals[i][1] = intervals[i - 1][1];
                }
            }
        }
        return removed;
    }
};