/*
url: https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-iv/?envType=daily-question&envId=2023-10-04
相关: https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/
      https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/
      https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-iii/
      https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-with-cooldown/
标签: 动态规划, 三维动态规划
*/

import java.util.Arrays;

public class Solution188 {
    public int maxProfit(int k, int[] prices) {
        int n = prices.length;
        int[][][] dp = new int[n][2][k + 1]; // dp[i][j][k]表示第i天交易完成后的最大收益，j为是否持有股票，k为已经完成的交易数量
        Arrays.fill(dp[0][0], 0);
        Arrays.fill(dp[0][1], -prices[0]);
        for (int i = 1; i < n; i++) {
            dp[i][0][0] = 0;
            dp[i][1][0] = Math.max(dp[i - 1][1][0], -prices[i]);
            for (int j = 1; j < k + 1; j++) {
                /* 以dp[i][0][j]为例说明递推逻辑，现在不持有股票，则一.今天未发生卖出，则dp[i][0][j]收益为dp[i - 1][0][j]，二.今天发生卖出，则
                dp[i][0][j]收益为前一天持有股票且交易次数为j-1的情况下，今天把持有的股票卖出，即dp[i - 1][1][j - 1] + prices[i]
                */
                dp[i][0][j] = Math.max(dp[i - 1][0][j], dp[i - 1][1][j - 1] + prices[i]);
                dp[i][1][j] = Math.max(dp[i - 1][1][j], dp[i - 1][0][j] - prices[i]);
            }
        }
        int maxProfit = Integer.MIN_VALUE;
        for (int j = 0; j < k + 1; j++) {
            maxProfit = Math.max(maxProfit, dp[n - 1][0][j]);
        }
        return maxProfit;
    }

    public static void main(String[] args) {
        Solution188 solu = new Solution188();
        System.out.println(solu.maxProfit(2, new int[]{3,2,6,5,0,3}));
    }
}