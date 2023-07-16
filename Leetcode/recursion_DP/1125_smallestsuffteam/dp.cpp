class Solution {
public:
    unordered_map<string, int> mp;//skill, index
    int n = 0;
    vector<int>  res;
    int memo[61][65537];
    int choice[61][65537];
    int dfs(vector<int>& people, int pos, int skills) {
        if (skills + 1 == (1 << n)) {//all required skill fullfilled
            return 0;
        }
        if (pos == people.size()) {
            return 100;
        }
        if (memo[pos][skills] != -1) return memo[pos][skills];
        //choose this person 
        int a = 100; int b = 100;
        a = 1 + dfs(people, pos + 1, skills | people[pos]);
        b = dfs(people, pos + 1, skills); //not choose this person
        if (a <= b) {//include this position
            choice[pos][skills] = 1;
        }
        memo[pos][skills] = min(a, b);
        return memo[pos][skills];
    }
    vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people) {
        n = req_skills.size();
        for (int i = 0; i < req_skills.size(); i++) {
            mp.emplace(req_skills[i], i);
        }
        memset(memo, -1, sizeof(memo));
        memset(choice, 0, sizeof(choice));
        vector<int> p;
        for (auto v : people) {
            int total_skills = 0;
            for (auto str : v) {
                total_skills |= (1 << mp[str]);
            }
            p.push_back(total_skills);
        }
        int x = dfs(p, 0, 0);
        int mask = 0;
        for (int i = 0; i <= people.size(); i++) {
            if (choice[i][mask]) {
                mask |= p[i];
                res.push_back(i);
            }
        }
        for (int i = 0; i < people.size(); i++) {
            cout << i << ":";
            for (int j = 0; j < (1 << n); j++) {
                cout << choice[i][j] << "," << memo[i][j] << "|";
            }
            cout << endl;
        }
        return res;
    }
};