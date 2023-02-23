class Solution {
public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > cap; //minheap of capital required
        for (int i = 0; i < capital.size(); i++) {
            pair<int, int> p = { capital[i],profits[i] };
            cap.push(p);
        }
        int step = 0;
        int res = 0;
        int ini = w;
        priority_queue<int> profit; //maxheap
        while (step < k) {
            while (!cap.empty() && cap.top().first <= w) {
                //cout << cap.top().first << ", " << cap.top().second << endl;
                profit.push(cap.top().second);
                cap.pop();
            }
            //take max profit we can afford
            //cout << profit.top()<< endl;
            if (!profit.empty()) {
                res += profit.top();
                w += profit.top();
                profit.pop();
            }
            step++;
        }
        return res + ini;
    }
};