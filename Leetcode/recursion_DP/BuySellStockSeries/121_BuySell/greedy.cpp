class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() == 1) {
            return 0;
        }
        int buy = 0; //left pointer day 0
        int sell = 1;//right pointer day 1
        int max = 0;
        while (sell < prices.size()) {
            if (prices[buy] >= prices[sell]) {
                //shift buy pointer to sell pointer where the price is low, sell set to buy+1
                buy = sell;
                //sell= buy+1;
            }
            else {
                //compare profit with max
                if (prices[sell] - prices[buy] > max) {
                    max = prices[sell] - prices[buy];
                }
                //shift sell pointer by 1
                //sell ++;
            }
            sell++;

        }
        return max;
    }
};