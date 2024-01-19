/*
url: https://leetcode.cn/problems/coin-change-ii/description/
相关: 典型问题/背包问题/完全背包问题
*/
public class Solution518 {
    public int change(int amount, int[] coins) {
        int[] dp = new int[amount + 1];
        dp[0] = 1;
        for (int i = 1; i <= coins.length; i++) {
            // dp[i][j]与头上和左侧的数有关，这里j不像0-1背包那样要从大到小
            for (int j = 1; j <= amount; j++) {
                int w = coins[i - 1];
                dp[j] = dp[j] + (j - w >= 0 ? dp[j - w] : 0);
            }
        }
        return dp[amount];
    }

    public static void main(String[] args) {
        Solution518 solu = new Solution518();
        System.out.println(solu.change(5, new int[]{1,2,5}));
    }
}
