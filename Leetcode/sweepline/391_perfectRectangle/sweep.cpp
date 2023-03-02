class Solution {
public:
    bool isRectangleCover(vector<vector<int>>& rectangles) {
        map<pair<int, int>, int>m;
        for (auto it : rectangles) {
            m[{it[0], it[1]}]++;
            m[{it[2], it[3]}]++;
            m[{it[0], it[3]}]--;
            m[{it[2], it[1]}]--;
        }
        int cnt = 0;
        for (auto it = m.begin(); it != m.end(); it++) {
            //cout << it->first.first << "," << it->first.second << ":" << it-> second << endl;
            if (abs(it->second) == 1) {//corner
                cnt++;
            }
            else if (abs(it->second) != 1 && it->second != 0) {
                return false;
            }
        }
        return cnt == 4;
    }
};