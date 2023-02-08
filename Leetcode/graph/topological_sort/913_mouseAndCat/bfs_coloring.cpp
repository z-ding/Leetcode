class Solution {
public:
    vector<vector<vector<int>>> state; //mouse position, cat position, whose turn
    /*  0 means mouse's turn, 1 means cat turn.  result
    mouse 0 <cat 0 <res_m,res_c>>
            <cat 1 <res_m,res_c>>
    mouse 1
    mouse 2
    */
    //cat win position - mouse == cat
    //mouse win position - mouse == 0

    int catMouseGame(vector<vector<int>>& graph) {

        int n = graph.size();
        for (int i = 0; i < n; i++) {
            vector<vector<int>> cat_p;
            for (int j = 0; j < n; j++) {
                vector<int> v;
                v.push_back(-1);
                v.push_back(-1);
                cat_p.push_back(v);
            }
            state.push_back(cat_p);
        }
        //鼠必胜的初始状态
        queue<tuple<int, int, int>> q; //鼠的位置，猫的位置，谁的turn
        for (int i = 1; i < n; i++) {//只要鼠在0
            tuple<int, int, int> t1 = { 0,i,0 };
            state[0][i][0] = 1;
            tuple<int, int, int> t2 = { 0,i,1 };
            state[0][i][1] = 1;
            q.push(t2);
            q.push(t1);
        }
        //猫必胜的初始状态
        for (int i = 1; i < n; i++) {//只要猫鼠在同一格
            tuple<int, int, int> t1 = { i,i,0 };
            tuple<int, int, int> t2 = { i,i,1 };
            q.push(t1);
            q.push(t2);
            state[i][i][0] = 2;
            state[i][i][1] = 2;
        }
        //BFS扩展：从每一个已知结果的状态扩展
        while (!q.empty()) {
            int mouse = get<0>(q.front());
            int cat = get<1>(q.front());
            int turn = get<2>(q.front());
            int winner = state[mouse][cat][turn];
            /*
            第一种扩展情况，如果下一个状态是猫必胜的位置，而猫又站在猫下一个状态的旁边，这一轮是猫的turn，那下一轮猫必胜。鼠也同理
            */
            q.pop();
            //cout << "from " << mouse << cat << turn << winner << endl;
            if (winner == 2) {
                //猫在下一个必胜状态猫的位置的旁边，并且这个位置不为0，鼠在必输位置原地不动
                if (turn == 0) {//下一轮是鼠的回合，这轮猫行动
                    for (int i = 0; i < graph[cat].size(); i++) {
                        int pos = graph[cat][i];
                        if (pos != 0 && state[mouse][pos][1] == -1) {
                            tuple<int, int, int> t = { mouse,pos,1 };
                            state[mouse][pos][1] = 2;
                            q.push(t);
                            //cout << "1 cat win marked " << mouse << pos << endl;
                        }
                    }
                }
                else {//下一轮是猫的回合，这轮鼠行动。猫在现在的必胜位置，鼠只能往某个猫必胜的位置移动

                    for (int i = 0; i < graph[mouse].size(); i++) {
                        int pos = graph[mouse][i]; //鼠在猫的某个必胜位置旁边
                        if (pos == 0) {
                            continue;
                        }
                        bool noway = true;
                        for (int j = 0; j < graph[pos].size(); j++) {//检查这个位置是否只能通向猫必胜的位置
                            int next = graph[pos][j];
                            if (next == cat) {
                                continue;
                            }
                            if (state[next][cat][1] != 2) {
                                noway = false;
                                break;
                            }
                        }
                        if (noway && state[pos][cat][0] == -1) {
                            state[pos][cat][0] = 2;
                            tuple<int, int, int> t = { pos,cat,0 };
                            //cout << "2 cat win marked " << pos << cat << endl;
                            q.push(t);
                        }
                    }
                }
            }
            else {
                if (turn == 1) {
                    for (int i = 0; i < graph[mouse].size(); i++) {
                        int pos = graph[mouse][i];
                        if (pos != cat && state[pos][cat][0] == -1) {
                            tuple<int, int, int> t = { pos,cat,0 };
                            state[pos][cat][0] = 1;
                            q.push(t);
                            //cout << "1 mouse win marked " << pos << cat << endl;
                        }
                    }
                }
                else {

                    for (int i = 0; i < graph[cat].size(); i++) {
                        int pos = graph[cat][i];
                        bool noway = true;
                        for (int j = 0; j < graph[pos].size(); j++) {
                            int next = graph[pos][j];
                            if (next == 0) {
                                continue; //cat can't go to zero
                            }
                            if (state[mouse][next][0] != 1) {
                                noway = false;
                                break;
                            }
                        }
                        if (noway && state[mouse][pos][1] == -1) {
                            state[mouse][pos][1] = 1;
                            tuple<int, int, int> t = { mouse,pos,1 };
                            //cout << "2 mouse win marked " <<mouse << pos << endl;
                            q.push(t);
                        }
                    }
                }

            }
        }

        /*
        for (int i=0; i< n;i++){
            for (int j=0; j< n;j++){
                for (int k=0; k<2;k++){
                    cout << "mouse " << i << " cat " << j
                    << " turn res" <<state[i][j][k] <<endl;
                }
            }
        }*/

        if (state[1][2][0] == -1) {
            return 0;
        }
        else {
            return state[1][2][0];
        }

    }
};