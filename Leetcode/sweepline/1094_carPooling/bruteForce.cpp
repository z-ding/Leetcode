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
        for (int i = 0; i < trips.size(); i++) {
            //check whether some seats can be released from previous trips. e.g. for the last trip, seats from first trip can be released
            for (int j = 0; j <= i - 1; j++) {
                if (trips[j][2] <= trips[i][1]) {
                    avai += trips[j][0];
                    trips[j][0] = 0;//can't release again
                }
            }
            if (avai < trips[i][0]) {
                return false;
            }
            avai -= trips[i][0];
        }
        if (avai >= 0) {
            return true;
        }
        else {
            return false;
        }
    }
};