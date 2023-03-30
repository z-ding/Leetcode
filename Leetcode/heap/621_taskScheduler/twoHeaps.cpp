class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        unordered_map<char, int> freq;
        for (int i = 0; i < tasks.size(); i++) {
            freq[tasks[i]]++;
        }
        priority_queue<pair<int, char>> pq;//maxheap of <freq,char>
        for (auto& e : freq) {
            pair<int, char> p = { e.second,e.first };
            pq.push(p);
        }
        priority_queue<pair<int, char>> remaining;
        int idle = 0;
        int time = 0;
        bool updateidle = true;
        int diff = 0;
        while (!pq.empty() && diff <= n) {
            pair<int, char> toDo = { pq.top().first - 1,pq.top().second };//do one task with max freq
            time++;
            diff++;
            //cout << pq.top().second << time << "," << toDo.first << endl;
            if (updateidle) {
                if (pq.size() <= n) {
                    updateidle = false;
                    idle = n - pq.size() + 1;
                }
                else {
                    idle = 0;
                    updateidle = false;
                }
            }

            pq.pop();
            if (toDo.first > 0) {
                remaining.push(toDo);
            }
            if (pq.empty() || diff > n) {
                if (!pq.empty() || !remaining.empty()) {
                    time += idle;
                }
                idle = 0;
                diff = 0;
                while (!remaining.empty()) {
                    pq.push(remaining.top());
                    remaining.pop();
                }
                updateidle = true;
                //cout <<"reupdate" << endl;
            }

        }
        return time;
    }
};