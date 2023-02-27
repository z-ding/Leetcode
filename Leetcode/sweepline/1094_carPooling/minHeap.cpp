class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        sort(trips.begin(), trips.end(), [](vector<int>& a, vector<int>& b) {
            return a[1] < b[1]; //sort according to starting point
            });
        /*
                   1    2   3   4   5   6   7   8   9      ppl
            [1,7]  -------------------------                8
            [2,9]       ------------------------------      4
            [3,6]           --------------                  9
            [4,9]               -----------------------     8
            [7,8]                            ------         6
            sort by starting point, check whether there are enough seats for each tri[]
        */
        int avai = capacity;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;//end point, people. lowest end point on the top
        for (int i = 0; i < trips.size(); i++) {
            //check whether some seats can be released from previous trips. e.g. for the last trip, seats from first trip can be released
            while (!pq.empty() && pq.top().first <= trips[i][1]) {
                avai += pq.top().second;
                pq.pop();
            }
            if (avai < trips[i][0]) {
                return false;
            }
            avai -= trips[i][0];
            pair<int, int> p = { trips[i][2],trips[i][0] };
            pq.push(p);
        }
        if (avai >= 0) {
            return true;
        }
        else {
            return false;
        }
    }
};