class Solution {
public:
    //dfs and backtrack
    vector<string> res;
    vector<string> tmp;
    int n;
    bool found = false;
    unordered_map<string, vector<pair<string, int>>> mp;
    void dfs(string node) {
        //cout << node << endl;
        if (found) return;
        tmp.push_back(node);
        if (tmp.size() == n + 1) {//all edges used
            found = true;
            res = tmp;
            return;
        }
        for (int i = 0; i < mp[node].size(); i++) {
            if (mp[node][i].second == 0) {
                mp[node][i].second = 1;
                dfs(mp[node][i].first);
                mp[node][i].second = 0;
            }
        }
        tmp.pop_back();
    }

    vector<string> findItinerary(vector<vector<string>>& tickets) {
        //sort the input list so that we will visit the cities in lexical order
        sort(tickets.begin(), tickets.end(), [](vector<string>& a, vector<string>& b) {
            return a[0] < b[0] || (a[0] == b[0] && a[1] < b[1]);
            });
        //build the adjacency list
        for (int i = 0; i < tickets.size(); i++) {
            mp[tickets[i][0]].push_back({ tickets[i][1],0 });//0 indicates unused edges
        }
        n = tickets.size();
        dfs("JFK");
        return res;
    }
};