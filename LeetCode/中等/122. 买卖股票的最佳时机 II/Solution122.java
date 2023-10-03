/*
url: https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/?envType=daily-question&envId=2023-10-02
LeetCode参考: https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/solutions/476791/mai-mai-gu-piao-de-zui-jia-shi-ji-ii-by-leetcode-s/
相关: https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/
      https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-iii/
标签: 动态规划, 二维动态规划
*/

public class Solution122 {
    public int maxProfit(int[] prices) {
        int n = prices.length;
        int[][] dp = new int[n][2];
        dp[0][0] = 0;
        dp[0][1] = -prices[0];
        for (int i = 1; i < n; i++) {
            dp[i][0] = Math.max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
            dp[i][1] = Math.max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
        }
        return dp[n - 1][0]; // dp[n - 1][1]一定比dp[n - 1][0]小
    }

    public static void main(String[] args) {
        Solution122 solu = new Solution122();
        System.out.println(solu.maxProfit(new int[]{7,1,5,3,6,4}));
    }
}