class Solution {
public:
    string reorganizeString(string s) {
        unordered_map<char, int> u;
        for (int i = 0; i < s.size(); i++) {
            u[s[i]]++;
        }
        string res;
        priority_queue<pair<int, char>> pq;
        for (auto& e : u) {
            pq.push({ e.second,e.first });
        }
        pair<int, char> prev = { -1,'a' };
        while (!pq.empty()) {
            pair<int, char> cur = pq.top();
            pq.pop();
            string s(1, cur.second);
            res += s;
            if (prev.first != -1) {
                pq.push(prev);
                prev.first = -1;
            }

            if (cur.first > 1) {//store decremented value to a prev pair since we can't choose the same letter again
                prev = { cur.first - 1, cur.second };
            }

        }
        if (res.size() < s.size()) {
            return "";
        }

        return res;
    }
};