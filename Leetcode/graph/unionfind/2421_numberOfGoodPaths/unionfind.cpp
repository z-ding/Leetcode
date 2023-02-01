class Solution {
public:
    unordered_map<int, vector<int>> neighbour;
    unordered_map<int, vector<int>> value;
    int count = 0;
    void findparent(int v, vector<int>& vals, vector<int>& parent, int node, int p, vector<int>& rank) {

        parent[node] = p;
        //cout<< node << endl;
        for (int i = 0; i < neighbour[node].size(); i++) {
            if (v >= vals[neighbour[node][i]]) { //connect cur node and its neighbour
                if (parent[node] != parent[neighbour[node][i]]) {
                    if (rank[parent[node]] >= rank[parent[neighbour[node][i]]]) {
                        rank[parent[node]]++;
                        rank[parent[neighbour[node][i]]]--;
                        findparent(v, vals, parent, neighbour[node][i], parent[node], rank);
                    }
                    else {
                        parent[node] = parent[neighbour[node][i]];
                        rank[parent[node]]--;
                        rank[parent[neighbour[node][i]]]++;
                        findparent(v, vals, parent, node, parent[neighbour[node][i]], rank);
                    }


                }
            }

        }
        return;
    }

    int numberOfGoodPaths(vector<int>& vals, vector<vector<int>>& edges) {
        //build a hashmap which indicates each val's appearing index from the smallest value to biggest value
        for (int i = 0; i < edges.size(); i++) {
            if (neighbour.find(edges[i][0]) == neighbour.end()) { //not in the map yet
                vector<int> v;
                v.push_back(edges[i][1]);
                neighbour.emplace(edges[i][0], v);
            }
            else {// in the map, add the new point to the vector
                neighbour[edges[i][0]].push_back(edges[i][1]);
            }

            if (neighbour.find(edges[i][1]) == neighbour.end()) { //not in the map yet
                vector<int> v;
                v.push_back(edges[i][0]);
                neighbour.emplace(edges[i][1], v);
            }
            else {// in the map, add the new point to the vector
                neighbour[edges[i][1]].push_back(edges[i][0]);
            }
        }

        vector<int> nondup;
        vector<int> parent(vals.size(), 0);
        for (int i = 0; i < vals.size(); i++) {
            parent[i] = i;
            if (value.find(vals[i]) == value.end()) {
                vector<int> v(1, i);
                nondup.push_back(vals[i]);
                value.emplace(vals[i], v);
            }
            else {
                value[vals[i]].push_back(i);
            }
        }
        sort(nondup.begin(), nondup.end());
        //build the graph from the smallest value

        vector<int> rank(vals.size(), 1);
        for (int i = 0; i < nondup.size(); i++) {
            for (int j = 0; j < value[nondup[i]].size(); j++) {
                findparent(nondup[i], vals, parent, value[nondup[i]][j], parent[value[nondup[i]][j]], rank);
            }
            //check parent 
            //cout<< "val " << nondup[i] << endl;
            //for (int j=0;j< parent.size();j++){
                //cout<< parent[j];
            //}
            //cout << endl;

            //count num of connected  nondup[i]
            unordered_map<int, int> freq;
            for (int j = 0; j < value[nondup[i]].size(); j++) {
                int p = parent[value[nondup[i]][j]];
                if (freq.find(p) == freq.end()) {
                    freq.emplace(p, 1);
                }
                else {
                    freq[p] ++;
                }
            }

            for (auto& f : freq) {
                count += f.second * (f.second - 1) / 2;
            }
        }



        return count + vals.size();

    }
};