/*
url: https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/?envType=daily-question&envId=2023-10-06
相关: LeetCode121. 买卖股票的最佳时机
      LeetCode122. 买卖股票的最佳时机 II
      LeetCode123. 买卖股票的最佳时机 III
      LeetCode188. 买卖股票的最佳时机 IV
      LeetCode309. 买卖股票的最佳时机含冷冻期
标签: 动态规划, 二维动态规划
*/

public class Solution714 {
    public int maxProfit(int[] prices, int fee) {
        int n = prices.length;
        int[][] dp = new int[n][2]; // dp[i][j]表示第i天的最大收益，j为0/1表示当天结束后是否持有股票
        dp[0][0] = 0;
        dp[0][1] = -prices[0];
        for (int i = 1; i < n; i++) {
            dp[i][0] = Math.max(dp[i - 1][0], dp[i - 1][1] + prices[i] - fee);
            dp[i][1] = Math.max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
        }
        return dp[n - 1][0];
    }

    public static void main(String[] args) {
        Solution714 solu = new Solution714();
        System.out.println(solu.maxProfit(new int[]{1, 3, 2, 8, 4, 9}, 2));
    }
}