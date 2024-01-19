/*
描述: 有一个背包，最大容量为amount，有一系列物品coins，每个物品的重量为coins[i]，
    每个物品的数量无限。请问有多少种方法，能够把背包恰好装满？
参考: https://labuladong.github.io/algo/di-er-zhan-a01c6/bei-bao-le-34bd4/jing-dian--70de0/
相关: LeetCode518. 零钱兑换 II
*/

public class UnboundedKnapsack {
    public int unboundedKnapsack(int[] coins, int amount) {
        // dp[i][j]为使用前i种硬币得出值j的种数
        int[][] dp = new int[coins.length + 1][amount + 1];
        for (int i = 0; i <= coins.length; i++) {
            dp[i][0] = 1;
        }
        for (int i = 1; i <= coins.length; i++) {
            for (int j = 1; j <= amount; j++) { // 这里dp[i][j]与左侧有关，不能改成for (int j = amount; j >= 1; j--)
                int w = coins[i - 1]; // 第i种硬币的重量
                dp[i][j] = dp[i - 1][j] + (j - w >= 0 ? dp[i][j - w] : 0); // dp[i][j - w]仍然为使用前i种硬币，保留了重复使用第i种硬币的可能
            }
        }
        return dp[coins.length][amount];
    }

    // 优化空间使用
    public int unboundedKnapsack_implementation2(int[] coins, int amount) {
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
        UnboundedKnapsack uk = new UnboundedKnapsack();
        System.out.println(uk.unboundedKnapsack(new int[]{1,2,5}, 5));
        System.out.println(uk.unboundedKnapsack_implementation2(new int[]{1,2,5}, 5));
    }
}
