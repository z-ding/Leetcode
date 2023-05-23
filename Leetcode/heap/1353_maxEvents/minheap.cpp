class Solution {
public:
    int maxEvents(vector<vector<int>>& events) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;
        sort(events.begin(), events.end(), [](vector<int>& a, vector<int>& b) {
            return a[0] < b[0];
            });
        int cur = 1;
        int pos = 0;
        int cnt = 0;
        int lastday = 1;
        for (int i = 0; i < events.size(); i++) {
            lastday = max(lastday, events[i][1]);
        }
        int day = 1;
        while (cur <= lastday) {
            if (pos < events.size()) {
                day = events[pos][0];
            }
            while (day == cur && pos < events.size() && events[pos][0] == day) {//push event starts on same date to the minheap
                pair<int, int> p = { events[pos][1],events[pos][0] };//put events ending sonnest on the top of minheap
                pq.push(p);
                pos++;
            }
            if (!pq.empty() && cur <= pq.top().first) {//complete the event on top and increment cur
                //cout << pq.top().first <<"," << pq.top().second << endl;
                pq.pop();
                cnt++;
            }
            cur++;
            cout << cur << endl;
            while (!pq.empty() && cur > pq.top().first) {
                pq.pop();
            }

        }
        return cnt;
    }
};