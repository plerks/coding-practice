/*
url: https://leetcode.cn/problems/coin-change/?envType=daily-question&envId=2024-03-24
标签: 完全背包问题
相关: 典型问题/背包问题/完全背包问题, LeetCode518. 零钱兑换 II
*/

import java.util.*;

public class Solution322 {
    // 直接用典型问题/背包问题/完全背包问题的代码改一下
    public int coinChange(int[] coins, int amount) {
        // dp[i][j]为使用前i种硬币得出值j的最小硬币数
        int[][] dp = new int[coins.length + 1][amount + 1];
        for (int[] arr : dp) Arrays.fill(arr, Integer.MAX_VALUE);
        for (int i = 0; i <= coins.length; i++) {
            dp[i][0] = 0;
        }
        for (int i = 1; i <= coins.length; i++) {
            for (int j = 1; j <= amount; j++) {
                int w = coins[i - 1];
                if (j - w >= 0 && dp[i][j - w] != Integer.MAX_VALUE) {
                    dp[i][j] = Math.min(dp[i - 1][j], dp[i][j - w] + 1);
                }
                else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        return dp[coins.length][amount] == Integer.MAX_VALUE ? -1 : dp[coins.length][amount];
    }

    // 优化空间
    public int coinChange_implementation2(int[] coins, int amount) {
        int[] dp = new int[amount + 1];
        Arrays.fill(dp, Integer.MAX_VALUE);
        dp[0] = 0;
        for (int i = 1; i <= coins.length; i++) {
            for (int j = 1; j <= amount; j++) {
                int w = coins[i - 1];
                if (j - w >= 0 && dp[j - w] != Integer.MAX_VALUE) {
                    dp[j] = Math.min(dp[j], dp[j - w] + 1);
                }
            }
        }
        return dp[amount] == Integer.MAX_VALUE ? -1 : dp[amount];
    }

    public static void main(String[] args) {
        Solution322 solu = new Solution322();
        System.out.println(solu.coinChange(new int[]{1,2,5}, 11));
        System.out.println(solu.coinChange_implementation2(new int[]{1,2,5}, 11));
    }
}
