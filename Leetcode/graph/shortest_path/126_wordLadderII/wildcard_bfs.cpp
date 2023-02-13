class Solution {
public:
    vector<string> v2;
    void dfs(vector<vector<tuple<string, int, vector<int>>>>& level, vector<vector<string>>& res, int cur_l, int cur_c) {

        if (cur_l == -1) {
            res.emplace_back(v2);
            return;
        }
        tuple<string, int, vector<int>> t = level[cur_l][cur_c];
        string w = get<0>(t);
        v2.push_back(w);
        vector<int> lastlevel = get<2>(t);
        for (int i = 0; i < lastlevel.size(); i++) {
            dfs(level, res, cur_l - 1, lastlevel[i]);

        }
        v2.pop_back();
    }
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        /*generating the list using wildcard patterns
        e.g. hot has three patterns: h*t, *ot, ho*
             dot has three patterns: *ot, d*t,do*
             so they have the common pattern *ot
             we can generate a hash map with the wildcard pattern and the corresponding words like below
                hi* : hit,
                d*g : dog,
                ho* : hot,
                *og : dog,log,cog,
                lo* : lot,log,
                *ot : hot,dot,lot,
                do* : dot,dog,
                h*t : hot,hit,
                l*t : lot,
                l*g : log,
                c*g : cog,
                d*t : dot,
                *it : hit,
                co* : cog,
        the complexity of generating the map and run the bfs based on this pattern map is m*n*m. as m << n, the performance will be better
        */
        vector<vector<string>> res;
        unordered_map<string, vector<string>> map;
        if (find(wordList.begin(), wordList.end(), endWord) == wordList.end()) {//add the beginWord to the wordList if it's not in the wordList
            return res;
        }
        if (find(wordList.begin(), wordList.end(), beginWord) == wordList.end()) {//add the beginWord to the wordList if it's not in the wordList
            wordList.push_back(beginWord);
        }
        unordered_map<string, vector<string>> wildcard;
        int len = wordList[0].size();
        for (int i = 0; i < wordList.size(); i++) { //n operations
            vector<string> wc;
            for (int j = 0; j < len; j++) {//m operations
                string p = wordList[i];
                p.replace(j, 1, "*");
                if (map.find(p) == map.end()) { // new pattern found
                    vector v = { wordList[i] };
                    map.emplace(p, v);
                }
                else { // matched with one of the existing pattern
                    map[p].push_back(wordList[i]); //add the word into current pattern's vector
                }
                wc.push_back(p);
            }
            wildcard.emplace(wordList[i], wc);
        }
        /*view the map
        for (auto& e:map){
            cout << e.first << " : "  ;
            for (int i=0; i< e.second.size();i++){
                cout << e.second[i] << "," ;
            }
            cout <<endl;
       }*/
        queue<tuple<string, int, int>> q;//word, index in this level, from index in last level, step to reach
        tuple t = { beginWord,0,-1 };
        q.push(t);
        unordered_map<string, int> visited;
        visited.emplace(beginWord, 0); //word + step to reach that word
        int step = 0;
        int min_step = 100000;
        vector<vector<tuple<string, int, vector<int>>>> level;
        vector<tuple<string, int, vector<int>>> v_begin;
        tuple<string, int, vector<int>> t_b = { beginWord,0,{-1} };
        v_begin.emplace_back(t_b);
        level.emplace_back(v_begin);
        while (!q.empty() && step <= min_step) {
            int size = q.size();
            vector<tuple<string, int, vector<int>>> l;
            //cout <<"new level " << endl;
            int count = -1;
            while (size--) {
                string w = get<0>(q.front());
                int lastlevel = get<1>(q.front());
                //cout<<"visiting: " << w << ":" << step << endl;
                if (w == endWord) {
                    //cout << "reached " << endl;
                    min_step = min(min_step, step);
                    //cout << "reached " << next << endl;
                }
                for (int i = 0; i < wildcard[w].size(); i++) {
                    for (int j = 0; j < map[wildcard[w][i]].size(); j++) {
                        string next = map[wildcard[w][i]][j];
                        if (visited.find(next) == visited.end()) {
                            count++;
                            visited.emplace(next, step + 1);
                            tuple<string, int, int> t = { next,count,lastlevel };
                            q.push(t);
                            vector<int> v = { lastlevel };
                            tuple<string, int, vector<int>> tv = { next,count,v };
                            l.emplace_back(tv);
                        }
                        else if (step < visited[next]) {
                            auto it = find_if(l.begin(), l.end(), [&](tuple<string, int, vector<int>>& t1) {
                                return get<0>(t1) == next;
                                });
                            get<2>(*it).push_back(lastlevel);
                        }
                    }
                }
                q.pop();
            }
            level.emplace_back(l);
            step++;
        }

        level.pop_back();
        /*
        for (int i=0; i< level.size();i++){
            cout<< "level " << i << ": " ;
            for (int j=0; j< level[i].size();j++){
                string w = get<0>(level[i][j]);
                int lastl = get<1>(level[i][j]);
                vector<int> thisl = get<2>(level[i][j]);
                cout << w << "," << lastl << "," ;
                for (int i=0; i< thisl.size();i++){
                    cout << thisl[i] << ";";
                }
                cout << " | " ;
            }
            cout << endl;
        }*/
        int m = level.size() - 1;

        for (int i = 0; i < level[m].size(); i++) {
            if (get<0>(level[m][i]) == endWord) {
                dfs(level, res, m, i);
            }
        }

        for (int i = 0; i < res.size(); i++) {
            reverse(res[i].begin(), res[i].end());
        }

        return res;
    }
};