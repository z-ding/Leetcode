/*
Intuition
if we consider the brute force approach (DFS), we have to check every possible route from start city to destination. This will give us a TLE. However we can stop visiting a route if there exists a better route at the city we are visiting. Better route means a route with same or less amount of stops but cheaper or same price to reach a certain city. Since we are exploring a route completely before exploring another route in DFS, we have to memorize the cost to reach each city with each possible stop and compare the new route with all routes with fewer or less amount of stops. This prunning approach can pass all the testcases, but it's not so efficient. (I will put the link of DFS + prunning answer in the comment for your reference)
However, we are visiting the graph layer by layer by using BFS. So we just need to record the min cost appeared so far for the city we reached. If we reached the city again, it means that we are already using more stops, so if the price is higher than the min price we have for the city, we don't need to continue with this route.

Approach
we will have a vector to store the min price we discovered so far to reach a certain city. Meanwhile we will do a normal BFS with a queue (queue<tuple<int,int,int>>) Everytime we want to explore a new route, we will push a tuple of <city, stops, cost> to the queue. If we figured out that there is already a more optimal route existing for the next city we want to visit, we won't push anything to the queue, meaning that we will stop exploring this route.

*/

class Solution {
public:
    unordered_map<int, vector<pair<int, int>>> network;
    int res = 10000000;
    vector<int> min_price;//min price for each city

    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        //converting the flights to a hash map
        for (int i = 0; i < flights.size(); i++) {
            if (network.find(flights[i][0]) == network.end()) {
                vector<pair<int, int>> v;
                pair<int, int> p = { flights[i][1],flights[i][2] }; //destination & price
                v.emplace_back(p);
                network.emplace(flights[i][0], v);
            }
            else {
                pair<int, int> p = { flights[i][1],flights[i][2] }; //destination & price
                network[flights[i][0]].emplace_back(p);
            }

        }
        for (int i = 0; i < n; i++) {
            min_price.push_back(10000000);
        }
        min_price[src] = 0;//the cost to reach src city is 0
        queue<tuple<int, int, int>> q; //city, stop, price
        tuple<int, int, int> t0 = make_tuple(src, 0, 0);
        q.push(t0);
        int stop = 0;
        while (!q.empty() && stop <= k) {
            int size = q.size();
            while (size) {//explore the graph layer by layer
                int cur_city = get<0>(q.front());
                int cur_stop = get<1>(q.front());
                int cur_price = get<2>(q.front());
                if (cur_price >= res) {// not consider this route
                    q.pop();
                    size--;
                    continue;
                }
                for (int i = 0; i < network[cur_city].size(); i++) {
                    int next_city = network[cur_city][i].first;
                    int next_cost = network[cur_city][i].second;
                    int newcost = cur_price + next_cost;
                    if (newcost < min_price[next_city]) {
                        //only consider visiting next city when the cost is lower than current min cost with fewer or same amount of stops
                        min_price[next_city] = newcost;
                        tuple t = make_tuple(next_city, stop + 1, newcost);
                        q.push(t);
                        if (next_city == dst) {
                            res = min(res, newcost);
                        }
                    }
                }
                q.pop();
                size--;
            }
            stop++;
        }
        if (res == 10000000) {
            return -1;
        }
        return res;
    }
};