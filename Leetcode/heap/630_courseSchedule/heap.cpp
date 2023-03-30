class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        sort(courses.begin(), courses.end(), [](vector<int>& a, vector<int>& b) {
            return a[1] < b[1];
            });
        priority_queue<int> pq;
        int time = 0;
        int c = 0;
        for (int i = 0; i < courses.size(); i++) {
            if (time + courses[i][0] <= courses[i][1]) {
                //can take this course and finish it before courses[i][1] at this moment
                c++;
                time += courses[i][0];
                pq.push(courses[i][0]);
            }
            else {
                //couldn't finish this course before the deadline, maybe this course or previous courses takes long time to complete.
                if (pq.empty()) {
                    continue;
                }
                if (courses[i][0] >= pq.top()) {
                    continue;
                }
                pq.push(courses[i][0]);
                //pop from pq to optimize the courses baskets that we can take until courses[i][1]
                int tmax = pq.top();
                time = time - tmax + courses[i][0];
                pq.pop();
            }
        }
        return c;
    }
};