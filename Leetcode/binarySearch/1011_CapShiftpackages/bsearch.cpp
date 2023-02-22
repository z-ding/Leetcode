class Solution {
public:
    int guesscap(int left, int right, vector<int>& weights, int days) {

        if (left > right) {
            return right + 1;
        }

        int mid = (left + right) / 2;//try this capacity
        int group = 0;
        int index = 0;
        while (index < weights.size() - 1) {
            int ttlweight = 0;
            while (index < weights.size() && ttlweight + weights[index] <= mid) {  //can take more packages              
                ttlweight += weights[index];
                index++;
            }
            group++;
            //cout << index << "," << group << endl;
        }
        if (index != weights.size()) {
            group++;
        }
        //cout << left << "," << right <<"," << mid << ":" << group << endl;
        //we try in a greedy way so that we will reduce capacity when we can deliver within the days limit

        if (group > days) {//mid is too low. 
            return guesscap(mid + 1, right, weights, days);
        }
        else {//we can reduce mid. if left > mid-1 means that previous mid is the lowest capacity
            return guesscap(left, mid - 1, weights, days);
        }
    }
    int shipWithinDays(vector<int>& weights, int days) {
        int startCap = 0;
        int lowest = 0;
        if (weights.size() <= days) { //shift one package per day, capacity should be the max weight
            int m = 0;
            for (int i = 0; i < weights.size(); i++) {
                m = max(m, weights[i]);
            }
            return m;
        }
        if (days == 1) {
            int t = 0;
            for (int i = 0; i < weights.size(); i++) {
                t += weights[i];
            }
            return t;
        }
        //e.g. 7 packages, 3 day, int package per day = 7/3+1 = 3
        for (int i = 0; i < weights.size(); i++) {
            lowest = max(lowest, weights[i]);
        }
        for (int i = 0; i < weights.size(); i += (weights.size() / days + 1)) {
            int w = 0; //capacity needed for each combination
            for (int j = i; j < i + weights.size() / days + 1; j++) {
                w += weights[i];
            }
            startCap = max(startCap, w);
        }
        return guesscap(lowest, startCap, weights, days);
    }
};