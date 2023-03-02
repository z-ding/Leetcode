class Solution {
public:
    /*
    sort by start value and compare adjacent intervals(i th and i-1 th)
    left pointer start from index 0
    case 1: no overlap. start(i) > end(i-1)
            ____ _____
            i-1    i
            since next start >= start(i), it will not overlap with i-1 th interval, shift left pointer
    case 2: overlap but not covered. start(i) < end(i-1) && end(i) > end(i-1)
            _____           i-1 th
               ________     i th
               xxx
                    YYY
            next interval can either overlap / covered by i th(XXX) or i-1 th (YYY), need to check every previous interval from left pointer (N square comlexity)
    case 3: covered start(i) < end(i-1) && end(i) <= end(i-1)
            ___________      i-1 th
                ____         i th
                XXXXXXXXXX
            if next interval overlaps / covered by i th interval, it means it must be overlapping / covered by i-1 th interval (XXX). check i-1 th interval is enough
            since erase in vector is O(n) complexity, we can simply mark the interval as [-1,-1]
    case 4: i-1 th interval is covered by i the interval (start(i) == start(i-1), end(i)>= end(i-1)
             ____           i-1 th
             ________       ith
             remove i th index and shift left pointer
    */
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        int removed = 0;
        sort(intervals.begin(), intervals.end(), [](vector<int>& a, vector<int>& b) {
            return a[0] < b[0];
            });
        int left = 0;
        int index = 1;//start index
        while (index < intervals.size()) {
            for (int i = left; i < index; i++) {//compare with each intervals from [left,index)
                if (intervals[i][1] == -1) {
                    continue;//removed interval
                }
                if (intervals[index][0] >= intervals[i][1]) {//no overlap
                    left++;
                }
                else {//overlapping or covered
                    if (intervals[index][1] <= intervals[i][1]) {//covered
                        removed++; //i th interval should be removed
                        intervals[index][1] = -1;
                        //intervals[index][0] = -1;
                        break;
                    }
                    else {//intervals[index][1]>intervals[i][1]
                        if (intervals[index][0] == intervals[i][0]) {
                            removed++; //i-1 th interval removed
                            left++;
                            break;
                        }

                    }
                }
            }
            //cout << index << "," << removed << endl;
            index++;
        }
        return intervals.size() - removed;

    }
};