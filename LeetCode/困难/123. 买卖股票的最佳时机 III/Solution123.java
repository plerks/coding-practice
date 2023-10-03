/*
url: https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-iii/?envType=daily-question&envId=2023-10-03
相关: https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/
      https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/
标签: 动态规划, 三维动态规划
*/

public class Solution123 {
    public int maxProfit(int[] prices) {
        int n = prices.length;
        int[][][] dp = new int[n][2][3]; // dp[i][j][k]表示第i天交易完成后的最大收益，j为是否持有股票，k为已经完成的交易数量
        dp[0][0][0] = 0;
        dp[0][0][1] = 0;
        dp[0][0][2] = 0;
        dp[0][1][0] = -prices[0];
        dp[0][1][1] = -prices[0];
        dp[0][1][2] = -prices[0];
        for (int i = 1; i < n; i++) {
            dp[i][0][0] = 0;
            /* 以dp[i][0][1]为例，第i天不持有股票，则:一. 第i天未卖出，则第i天的收益为dp[i - 1][0][1] 二. 第i天卖出，则第i-1天持有股票，且交易完成数为0，
            即dp[i - 1][1][0] + prices[i]
            */
            dp[i][0][1] = Math.max(dp[i - 1][0][1], dp[i - 1][1][0] + prices[i]);
            dp[i][0][2] = Math.max(dp[i - 1][0][2], dp[i - 1][1][1] + prices[i]);
            dp[i][1][0] = Math.max(dp[i - 1][1][0], -prices[i]);
            dp[i][1][1] = Math.max(dp[i - 1][1][1], dp[i - 1][0][1] - prices[i]);
            dp[i][1][1] = Math.max(dp[i - 1][1][1], dp[i - 1][0][1] - prices[i]);
            dp[i][1][2] = Math.max(dp[i - 1][1][2], dp[i - 1][0][2] - prices[i]);
        }
        // 每次dp只涉及dp[i]和dp[i - 1]，应该可以像674. 最长连续递增序列一样用predp和dp变量滚动着走
        return Math.max(dp[n - 1][0][0], Math.max(dp[n - 1][0][1], dp[n - 1][0][2]));
    }

    public static void main(String[] args) {
        Solution123 solu = new Solution123();
        System.out.println(solu.maxProfit(new int[]{1}));
    }
}