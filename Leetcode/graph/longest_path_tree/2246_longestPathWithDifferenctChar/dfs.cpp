class Solution {
public:
    unordered_set<int> visited;
    unordered_map<int, vector<int>> tree; //graph
    int res = 1;
    int maxPath(int node, string& s, char c) {
        int max_path = 1;
        int second_path = 1;
        int path = 1;
        for (int i = 0; i < tree[node].size(); i++) {
            //auto it = find(tree[tree[node][i]].begin(),tree[tree[node][i]].end(),node);
            //tree[tree[node][i]].erase(it);            
            if (s[tree[node][i]] != c) {
                path = 1 + maxPath(tree[node][i], s, s[tree[node][i]]);
            }
            else {
                maxPath(tree[node][i], s, s[tree[node][i]]);
                path = 1;
            }
            //cout << "node " << node << "path: " << path << ". " << c << endl;
            if (path > max_path) {
                second_path = max_path;
                max_path = path;
            }
            else if (path > second_path) {
                second_path = path;
            }

            //for this node, the max. path is the sum of two subtrees with max. node - 1
            int cur_max = max_path + second_path - 1;
            res = max(cur_max, res);
        }

        //return the subtree with maximum path to the parent
        //cout << node << "," <<  max_path << " . " << second_path << endl;
        return max_path;

    }
    int longestPath(vector<int>& parent, string s) {
        //build a graph
        //parent[0] = -1, so we start from first node
        for (int i = 1; i < parent.size(); i++) {
            //build the path from parent to child   
            if (tree.find(parent[i]) == tree.end()) {
                vector<int> v;
                v.push_back(i);
                tree.emplace(parent[i], v);
            }
            else {
                tree[parent[i]].push_back(i);
            }
            //build the path from child to parent
            /*
            if (tree.find(i) == tree.end()){
                vector<int> v;
                v.push_back(parent[i]);
                tree.emplace(i,v);
            } else{
                tree[i].push_back(parent[i]);
            }*/
        }
        //visualize and check whether the graph looks correct

        /*
        for (auto& t:tree){
            cout << t.first << ": ";
            for (int i=0; i< t.second.size();i++){
                cout << t.second[i] << "," ;
            }
            cout << endl;
        }*/
        /*
        the graph for first example looks like this
        5: 2,
        4: 1,
        3: 1,
        2: 0,5,
        1: 0,3,4,
        0: 1,2,
        */
        // now we can traverse through each tree to find the max path of that tree. we only need to visit each node once since now they are seperated trees, so we will record our visited node using a hash set
        maxPath(0, s, s[0]);
        return res;
    }
};