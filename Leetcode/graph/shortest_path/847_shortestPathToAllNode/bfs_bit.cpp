class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {

        int target;
        int res = 1000000;

        target = (1 << graph.size()) - 1;
        for (int i = 0; i < graph.size(); i++) {
            int state = 1 << i;
            tuple<int, int, int> t = { i,0,state }; //node, step, state
            queue<tuple<int, int, int>> q;
            q.push(t);
            pair<int, int> p = { state,i };
            set<pair<int, int>> memo;//state,node
            memo.insert(p);
            //cout << "checking... " << i << endl;
            while (!q.empty()) {
                int cur = get<0>(q.front());
                int step = get<1>(q.front());
                int s = get<2>(q.front());
                //cout << cur << ":" << step << ":" << s << endl;
                if (s == target) {
                    res = min(res, step);
                    break;
                }
                q.pop();
                for (int i = 0; i < graph[cur].size(); i++) {
                    int next = graph[cur][i];
                    int news = s | (1 << next);
                    pair<int, int> p = { news, next };
                    if (memo.find(p) == memo.end()) {
                        memo.insert(p);
                        tuple<int, int, int> t1 = { next,step + 1,news };
                        q.push(t1);
                    }
                }
            }
        }
        return res;
    }
};