class Solution {
public:

    int profit(vector<int>& prices, int today, int boughtday, vector<vector<int>>& memo) {
        int pb = 0; int pnb = 0; int ps = 0; int pns = 0;
        //cout << today << "," << boughtday << "," << canbuy << endl;
        if (memo[today][boughtday + 1] != -1) {
            return memo[today][boughtday + 1];
        }
        if (today >= prices.size()) {
            memo[today][boughtday + 1] = 0;
            return 0;
        }
        if (boughtday == -1) { //no stock on hand, buy or not buy today
            pb = profit(prices, today + 1, today, memo);//buy, can't buy next day before sell          
            pnb = profit(prices, today + 1, -1, memo);//not buy
        }
        else {//stock on hand, decide whether to sell
            //cout << "cansell " <<  today << "," << boughtday << "," << canbuy << endl;
            ps = prices[today] - prices[boughtday] + profit(prices, today + 2, -1, memo);//sell & cool down
            pns = profit(prices, today + 1, boughtday, memo); //not sell
        }
        //cout << today << "," << boughtday << ":" << ps << endl;
        memo[today][boughtday + 1] = max(max(pb, pnb), max(ps, pns));
        return memo[today][boughtday + 1];
    }
    int maxProfit(vector<int>& prices) {
        int n = prices.size() + 3;
        vector<int> v(n, -1);
        vector<vector<int>> memo(n, v);
        return profit(prices, 0, -1, memo);

    }
};