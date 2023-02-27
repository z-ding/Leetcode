class Solution {
public:
    /*
    check how many people are going to get on the bus and how many people want to get off at each stop
    if at certain stop passenger > capacity, return false
    */
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        vector<pair<int, int>> people; //pair<stop number, people on/off (off: negative)
        for (auto& t : trips) {
            pair<int, int> p1 = { t[1], t[0] }; //start stop: people get on the bus
            pair<int, int> p2 = { t[2], -t[0] };//end stop: people get off the bus
            people.emplace_back(p1);
            people.emplace_back(p2);
        }
        sort(people.begin(), people.end());//sort by stop & people (negative first)
        for (auto& p : people) {
            capacity -= p.second;
            if (capacity < 0) {
                return false;
            }
        }
        return true;
    }
};