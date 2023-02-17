class Solution {
public:
    int profit(vector<int>& prices, int fee, int day, int stock, vector<vector<int>>& memo) {//stock:0-no stock, 1-stock-on-hand        
        if (memo[day][stock] != -1) {
            return memo[day][stock];
        }
        if (day == prices.size()) {
            memo[day][stock] = 0;
            return 0;
        }
        int pb = 0;
        int pnb = 0;
        int ps = 0;
        int pns = 0;
        if (!stock) {
            //buy or not buy
            pb = -prices[day] + profit(prices, fee, day + 1, 1, memo);
            pnb = profit(prices, fee, day + 1, 0, memo);
        }
        else {
            //sell or not sell
            ps = prices[day] - fee + profit(prices, fee, day + 1, 0, memo);
            pns = profit(prices, fee, day + 1, 1, memo);
        }
        memo[day][stock] = max(max(pb, pnb), max(ps, pns));
        cout << day << "," << stock << ":" << max(pb, pnb) << "," << max(ps, pns) << endl;
        return memo[day][stock];
    }
    int maxProfit(vector<int>& prices, int fee) {
        vector<int> v(2, -1);//stock on hand or not
        int n = prices.size() + 1;
        vector<vector<int>> memo(n, v);

        memo[n - 1][0] = 0;
        memo[n - 1][1] = 0;
        for (int i = n - 2; i >= 0; i--) {
            //if we don't have stock today, we can buy or do nothing
            //if we buy, profit = -prices + profit(day+1, has stock)
            //if we don't buy, profit = profit(day+1, no stock)
            int buy = -prices[i] + memo[i + 1][1];
            int notbuy = memo[i + 1][0];
            memo[i][0] = max(buy, notbuy);
            //if we  have stock today, we can sell or do nothing
            //if we sell, profit = prices - fee + profit(day+1, no stock)
            //if we don't sell, profit = profit(day+1, has stock)
            int sell = prices[i] - fee + memo[i + 1][0];
            int notsell = memo[i + 1][1];
            memo[i][1] = max(sell, notsell);
            //cout << memo[i][0] << "," << memo[i][1] << endl;

        }
        return memo[0][0];//we wouldn't have stock on day 0


        //return profit(prices,fee,0,0,memo);
    }
};