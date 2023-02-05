class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        //find out number of child for each node, if number ==0, it is a safe node
        unordered_map<int, vector<int>> child;//child:<parent>
        unordered_map<int, int> childnumber;//node:childnumber
        queue<int> q;
        vector<int> res;
        for (int i = 0; i < graph.size(); i++) {
            if (graph[i].size() == 0) {
                q.push(i); //terminal nodes
            }
            childnumber.emplace(i, graph[i].size());
            for (int j = 0; j < graph[i].size(); j++) {
                if (child.find(graph[i][j]) == child.end()) {
                    vector<int> v;
                    v.push_back(i);
                    child.emplace(graph[i][j], v);
                }
                else {
                    child[graph[i][j]].push_back(i);
                }
            }
        }

        while (!q.empty()) {
            int cur = q.front();
            res.push_back(cur);
            for (int i = 0; i < child[cur].size(); i++) {
                int par = child[cur][i];
                childnumber[par]--;
                if (!childnumber[par]) {
                    q.push(par);//safe node,add to queue
                }
            }
            q.pop();
        }
        sort(res.begin(), res.end());
        return res;
    }
};