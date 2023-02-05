//mark state as 0 for the first visit, mark as draw if a cycle is detected
//Problem: a winning route can be discovered after the draw, causing previous return value / detected cycle to be incorrect.
//e.g. the code below passed a simple test case [[2],[2,4],[0,1,3],[2,4],[1,3]]
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
    int dfs(vector<vector<int>>& graph, int mouse, int cat, int turn, int step, int drawlimit) {
        cout << " pos " << mouse << "," << cat << " next turn: " << turn << endl;
        if (state[mouse][cat][turn] != -1) {
            return state[mouse][cat][turn];
        }
        if (mouse == 0) {
            state[mouse][cat][turn] = 1;
            return 1;
        }
        if (mouse == cat) {
            state[mouse][cat][turn] = 2;
            return 2;
        }
        state[mouse][cat][turn] = 0;
        /*
        if (step == drawlimit){
            state[mouse][cat][turn] =0;
            return 0;
        }*/

        if (!turn) {//mouse's turn
            bool isDraw = false;
            for (int i = 0; i < graph[mouse].size(); i++) {
                int nextturn = dfs(graph, graph[mouse][i], cat, turn + 1, step + 1, drawlimit);
                if (nextturn == 1) {
                    isDraw = false;
                    return state[mouse][cat][turn] = 1;
                }
                if (nextturn == 0) {
                    isDraw = true;
                }
            }
            //because draw is better than loss
            if (isDraw) {
                return state[mouse][cat][turn] = 0;
            }
            return state[mouse][cat][turn] = 2;
        }
        else {
            bool isDraw = false;
            for (int i = 0; i < graph[cat].size(); i++) {
                if (graph[cat][i] != 0) {
                    int nextturn = dfs(graph, mouse, graph[cat][i], turn - 1, step + 1, drawlimit);
                    if (nextturn == 2) {
                        isDraw = false;
                        return state[mouse][cat][turn] = 2;
                    }
                    if (nextturn == 0) {
                        isDraw = true;
                    }
                }
            }
            if (isDraw) {
                return state[mouse][cat][turn] = 0;
            }
            return state[mouse][cat][turn] = 1;
        }

        cout << "best option of " << turn << " at pos " << mouse << "," << cat << " : " << state[mouse][cat][turn] << endl;
        return state[mouse][cat][turn];
    }
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

        dfs(graph, 1, 2, 0, 0, 5 * n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < 2; k++) {
                    cout << "mouse " << i << " cat " << j
                        << " turn res" << state[i][j][k] << endl;
                }


            }
        }
        if (state[1][2][0] == -1) {
            return 0;
        }
        else {
            return state[1][2][0];
        }

    }
};
/*
cout for this testcase
 pos 1,2 next turn: 0
 pos 2,2 next turn: 1
 pos 4,2 next turn: 1
 pos 4,1 next turn: 0
 pos 1,1 next turn: 1
 pos 3,1 next turn: 1
 pos 3,2 next turn: 0
 pos 2,2 next turn: 1
 pos 4,2 next turn: 1
 pos 3,4 next turn: 0
 pos 2,4 next turn: 1
 pos 2,1 next turn: 0
 pos 0,1 next turn: 1
 pos 2,3 next turn: 0
 pos 0,3 next turn: 1
 pos 4,3 next turn: 0
 pos 1,3 next turn: 1
 pos 1,2 next turn: 0
 pos 1,4 next turn: 0
 pos 2,4 next turn: 1
 pos 3,3 next turn: 1
mouse 0 cat 0 turn res-1
mouse 0 cat 0 turn res-1
mouse 0 cat 1 turn res-1
mouse 0 cat 1 turn res1
mouse 0 cat 2 turn res-1
mouse 0 cat 2 turn res-1
mouse 0 cat 3 turn res-1
mouse 0 cat 3 turn res1
mouse 0 cat 4 turn res-1
mouse 0 cat 4 turn res-1
mouse 1 cat 0 turn res-1
mouse 1 cat 0 turn res-1
mouse 1 cat 1 turn res-1
mouse 1 cat 1 turn res2
mouse 1 cat 2 turn res0
mouse 1 cat 2 turn res-1
mouse 1 cat 3 turn res-1
mouse 1 cat 3 turn res0
mouse 1 cat 4 turn res1
mouse 1 cat 4 turn res-1
mouse 2 cat 0 turn res-1
mouse 2 cat 0 turn res-1
mouse 2 cat 1 turn res1
mouse 2 cat 1 turn res-1
mouse 2 cat 2 turn res-1
mouse 2 cat 2 turn res2
mouse 2 cat 3 turn res1
mouse 2 cat 3 turn res-1
mouse 2 cat 4 turn res-1
mouse 2 cat 4 turn res1
mouse 3 cat 0 turn res-1
mouse 3 cat 0 turn res-1
mouse 3 cat 1 turn res-1
mouse 3 cat 1 turn res0
mouse 3 cat 2 turn res0
mouse 3 cat 2 turn res-1
mouse 3 cat 3 turn res-1
mouse 3 cat 3 turn res2
mouse 3 cat 4 turn res1
mouse 3 cat 4 turn res-1
mouse 4 cat 0 turn res-1
mouse 4 cat 0 turn res-1
mouse 4 cat 1 turn res0
mouse 4 cat 1 turn res-1
mouse 4 cat 2 turn res-1
mouse 4 cat 2 turn res0
mouse 4 cat 3 turn res0
mouse 4 cat 3 turn res-1
mouse 4 cat 4 turn res-1
mouse 4 cat 4 turn res-1


*/

/*
However, if we simply add an edge between 0 and 1, the test case would be [[1,2],[2,4,0],[0,1,3],[2,4],[1,3]]
now the result for the root node is still correct although we discovered a later mouse winning route, we can found that the result of node
<1,3,1> is still draw, which didn't consider the new route found. AT position <1,3,1> no matter cat moves to 2 or 4, mouse can move to 0 and win
so the result on this node is wrong, same for node <4,3,0>
cout after new edges
 pos 1,2 next turn: 0
 pos 2,2 next turn: 1
 pos 4,2 next turn: 1
 pos 4,1 next turn: 0
 pos 1,1 next turn: 1
 pos 3,1 next turn: 1
 pos 3,2 next turn: 0
 pos 2,2 next turn: 1
 pos 4,2 next turn: 1
 pos 3,4 next turn: 0
 pos 2,4 next turn: 1
 pos 2,1 next turn: 0
 pos 0,1 next turn: 1
 pos 2,3 next turn: 0
 pos 0,3 next turn: 1
 pos 4,3 next turn: 0
 pos 1,3 next turn: 1
 pos 1,2 next turn: 0
 pos 1,4 next turn: 0
 pos 2,4 next turn: 1
 pos 3,3 next turn: 1
 pos 0,2 next turn: 1
mouse 0 cat 0 turn res-1
mouse 0 cat 0 turn res-1
mouse 0 cat 1 turn res-1
mouse 0 cat 1 turn res1
mouse 0 cat 2 turn res-1
mouse 0 cat 2 turn res1
mouse 0 cat 3 turn res-1
mouse 0 cat 3 turn res1
mouse 0 cat 4 turn res-1
mouse 0 cat 4 turn res-1
mouse 1 cat 0 turn res-1
mouse 1 cat 0 turn res-1
mouse 1 cat 1 turn res-1
mouse 1 cat 1 turn res2
mouse 1 cat 2 turn res1
mouse 1 cat 2 turn res-1
mouse 1 cat 3 turn res-1
mouse 1 cat 3 turn res0
mouse 1 cat 4 turn res1
mouse 1 cat 4 turn res-1
mouse 2 cat 0 turn res-1
mouse 2 cat 0 turn res-1
mouse 2 cat 1 turn res1
mouse 2 cat 1 turn res-1
mouse 2 cat 2 turn res-1
mouse 2 cat 2 turn res2
mouse 2 cat 3 turn res1
mouse 2 cat 3 turn res-1
mouse 2 cat 4 turn res-1
mouse 2 cat 4 turn res1
mouse 3 cat 0 turn res-1
mouse 3 cat 0 turn res-1
mouse 3 cat 1 turn res-1
mouse 3 cat 1 turn res0
mouse 3 cat 2 turn res0
mouse 3 cat 2 turn res-1
mouse 3 cat 3 turn res-1
mouse 3 cat 3 turn res2
mouse 3 cat 4 turn res1
mouse 3 cat 4 turn res-1
mouse 4 cat 0 turn res-1
mouse 4 cat 0 turn res-1
mouse 4 cat 1 turn res0
mouse 4 cat 1 turn res-1
mouse 4 cat 2 turn res-1
mouse 4 cat 2 turn res0
mouse 4 cat 3 turn res0
mouse 4 cat 3 turn res-1
mouse 4 cat 4 turn res-1
mouse 4 cat 4 turn res-1
*/

/*
the walkaround would be: we will revisit each draw position after each dfs until the draw position doesn't reduce again. with the new route found
we should be able to udpate some of the draw route each time, until no route can be updated further. 
as we are revisiting the nodes again and again, this solution is defenitely not efficient, however it passed leetcode testcases.
*/
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
    int dfs(vector<vector<int>>& graph, int mouse, int cat, int turn) {
        //cout << " pos " << mouse << "," << cat << " next turn: " << turn << endl; 
        if (state[mouse][cat][turn] != -1) {
            return state[mouse][cat][turn];
        }
        if (mouse == 0) {
            state[mouse][cat][turn] = 1;
            return 1;
        }
        if (mouse == cat) {
            state[mouse][cat][turn] = 2;
            return 2;
        }
        state[mouse][cat][turn] = 0;
        /*
        if (step == drawlimit){
            state[mouse][cat][turn] =0;
            return 0;
        }*/

        if (!turn) {//mouse's turn
            bool isDraw = false;
            for (int i = 0; i < graph[mouse].size(); i++) {
                int nextturn = dfs(graph, graph[mouse][i], cat, turn + 1);
                if (nextturn == 1) {
                    isDraw = false;
                    return state[mouse][cat][turn] = 1;
                }
                if (nextturn == 0) {
                    isDraw = true;
                }
            }
            //because draw is better than loss
            if (isDraw) {
                return state[mouse][cat][turn] = 0;
            }
            return state[mouse][cat][turn] = 2;
        }
        else {
            bool isDraw = false;
            for (int i = 0; i < graph[cat].size(); i++) {
                if (graph[cat][i] != 0) {
                    int nextturn = dfs(graph, mouse, graph[cat][i], turn - 1);
                    if (nextturn == 2) {
                        isDraw = false;
                        return state[mouse][cat][turn] = 2;
                    }
                    if (nextturn == 0) {
                        isDraw = true;
                    }
                }
            }
            if (isDraw) {
                return state[mouse][cat][turn] = 0;
            }
            return state[mouse][cat][turn] = 1;
        }


        return state[mouse][cat][turn];
    }
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

        dfs(graph, 1, 2, 0);
        //revisit 0
        vector<vector<int>> revisit;
        int lastround = -1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < 2; k++) {
                    if (state[i][j][k] == 0) {
                        vector<int> v = { i,j,k };
                        revisit.push_back(v);
                    }
                    //cout << "mouse " << i << " cat " << j 
                    //<< " turn res" <<state[i][j][k] <<endl;
                }
            }
        }
        while (lastround != revisit.size() && revisit.size() != 0) {
            //cout << lastround << ','<< revisit.size() << endl;
            lastround = revisit.size();
            for (int i = 0; i < revisit.size(); i++) {
                state[revisit[i][0]][revisit[i][1]][revisit[i][2]] = -1;
                dfs(graph, revisit[i][0], revisit[i][1], revisit[i][2]);
            }
            revisit.clear();
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    for (int k = 0; k < 2; k++) {
                        if (state[i][j][k] == 0) {
                            vector<int> v = { i,j,k };
                            revisit.push_back(v);
                        }
                    }
                }
            }

        }

        if (state[1][2][0] == -1) {
            return 0;
        }
        else {
            return state[1][2][0];
        }

    }
};