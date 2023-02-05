class Solution {
public:
    unordered_map<int, vector<int>> neighbour;
    unordered_set<int> visited;
    unordered_map<int, double> freq;
    inline void result(int node, double multiply) {
        if (freq.find(node) == freq.end()) {
            freq.emplace(node, multiply);
        }
        else {
            freq[node] += multiply;
        }
    }
    void dfs(int node, int time, int t, double multiply) {
        visited.emplace(node);
        //cout << node <<"," << time << endl;
        if (time == t) {
            result(node, multiply);
            return;
        }
        double child = 0;
        for (int i = 0; i < neighbour[node].size(); i++) {
            int next = neighbour[node][i];
            if (visited.find(next) == visited.end()) {//found an unvisited node
                child++;
            }
        }
        if (!child) {//can't jump to any child, jump forever in this node
            result(node, multiply);
            return;
        }
        multiply = multiply / child;
        //cout << multiply << endl;   
        for (int i = 0; i < neighbour[node].size(); i++) {
            int next = neighbour[node][i];
            if (visited.find(next) == visited.end()) {//found an unvisited node               
                dfs(neighbour[node][i], time + 1, t, multiply);
            }
        }
        visited.erase(node);


        return;
    }
    double frogPosition(int n, vector<vector<int>>& edges, int t, int target) {
        for (int i = 0; i < edges.size(); i++) {
            if (neighbour.find(edges[i][0]) == neighbour.end()) { //not in the map yet
                vector<int> v;
                v.push_back(edges[i][1]);
                neighbour.emplace(edges[i][0], v);
            }
            else {// in the map, add the new point to the vector
                neighbour[edges[i][0]].push_back(edges[i][1]);
            }

            if (neighbour.find(edges[i][1]) == neighbour.end()) { //not in the map yet
                vector<int> v;
                v.push_back(edges[i][0]);
                neighbour.emplace(edges[i][1], v);
            }
            else {// in the map, add the new point to the vector
                neighbour[edges[i][1]].push_back(edges[i][0]);
            }
        }
        dfs(1, 0, t, 1);
        if (freq.find(target) == freq.end()) {
            return 0;
        }
        double ttl = 0;
        for (auto& e : freq) {
            //cout << e.first << ":" << e.second << endl;
            ttl += e.second;
        }
        //cout << freq[target] << endl;
        return freq[target] / ttl;
    }
};