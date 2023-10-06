/*
url: https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-with-cooldown/?envType=daily-question&envId=2023-10-05
相关: LeetCode121. 买卖股票的最佳时机
      LeetCode122. 买卖股票的最佳时机 II
      LeetCode123. 买卖股票的最佳时机 III
      LeetCode188. 买卖股票的最佳时机 IV
      LeetCode714. 买卖股票的最佳时机含手续费
标签: 动态规划, 二维动态规划
*/

public class Solution309 {
    public int maxProfit(int[] prices) {
        int n = prices.length;
        if (n == 1) return 0;
        int[][] dp = new int[n][2]; // dp[i]表示第i天的最大收益，第二位0/1表示这天交易结束是否持有股票
        dp[0][0] = 0;
        dp[0][1] = -prices[0];
        dp[1][0] = Math.max(dp[0][0], dp[0][1] + prices[1]);
        dp[1][1] = Math.max(dp[0][1], dp[0][0] - prices[1]);
        for (int i = 2; i < n; i++) {
            dp[i][0] = Math.max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
            dp[i][1] = Math.max(dp[i - 1][1], dp[i - 2][0] - prices[i]);
        }
        return dp[n - 1][0];
    }

    public static void main(String[] args) {
        Solution309 solu = new Solution309();
        System.out.println(solu.maxProfit(new int[]{1,2,3,0,2}));
    }
}