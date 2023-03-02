class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList, vector<vector<int>>& secondList) {
        map<int, pair<int, int>> sweep;//<int,bool>:value / whether there is a close interval
        for (int i = 0; i < firstList.size(); i++) {
            sweep[firstList[i][0]].first++;
            sweep[firstList[i][1]].first--;
            sweep[firstList[i][0]].second++;
            sweep[firstList[i][1]].second++;
        }
        for (int i = 0; i < secondList.size(); i++) {
            sweep[secondList[i][0]].first++;
            sweep[secondList[i][1]].first--;
            sweep[secondList[i][0]].second++;
            sweep[secondList[i][1]].second++;
        }
        vector<vector<int>> res;
        int start = -1;
        bool sweeping = false;//overlapping interval found
        int total = 0;
        for (auto& e : sweep) {
            total += e.second.first;
            //cout << e.first << "," <<total << "." << e.second.second<< endl;
            if (total > 1) {//overlapping
                if (!sweeping) {
                    //start sweep
                    sweeping = true;
                    start = e.first;
                }//if already sweeping, do nothing since we want to return the whole overlapping area
            }
            else {//non onverlap
                if (sweeping) {
                    //stop sweeping, push to result
                    sweeping = false;
                    vector<int> v = { start,e.first };
                    res.push_back(v);
                }
            }
            if (total == 1 && e.second.second == 2) {
                vector<int> v = { e.first,e.first };
                res.push_back(v);
            }
        }
        return res;
    }
};