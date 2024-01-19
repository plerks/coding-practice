/*
描述: 商店里有n个商品，第i个商品价值为values[i]，重量为weights[i]，现在有一个可容纳最大重量为W的背包，
    目标使得背包中的商品总价值最大，每个商品只能选择一次，且要不选择整个某商品要不不选择某商品，应该选择哪些商品。
参考: https://labuladong.github.io/algo/di-er-zhan-a01c6/bei-bao-le-34bd4/jing-dian--28f3c/
      https://oi-wiki.org/dp/knapsack/
相关: LeetCode2809. 使数组和小于等于 x 的最少时间, LeetCode416. 分割等和子集
*/

public class ZeroOneKnapsack {
    public int zeroOneKnapsack(int n, int[] values, int[] weights, int W) {
        int[][] dp = new int[n + 1][W + 1]; // dp[i][j]表示从前i件商品里选，总重量为j以内时的最大价值
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= W; j++) { // dp[i][j]只取决于上一行而不取决于左侧，因此这里for (int j = W; j >= 1; j--)也行
                int v = values[i - 1], w = weights[i - 1]; // 第i件商品的价值和重量
                // 分选或不选第i件商品两种情况
                if (j - w < 0) { // 装不进
                    dp[i][j] = dp[i - 1][j];
                }
                else dp[i][j] = Math.max(dp[i - 1][j], dp[i - 1][j - w] + v);
            }
        }
        return dp[n][W];
    }

    // dp[i]只与dp[i - 1]相关，优化空间使用，把第一个维度i去掉，实在不行可以用两行滚动着算
    public int zeroOneKnapsack_implemention2(int n, int[] values, int[] weights, int W) {
        int[] dp = new int[W + 1];
        for (int i = 1; i <= n; i++) {
            for (int j = W; j >= weights[i - 1]; j--) { // 这个优化空间的技巧必须从大到小，这样计算dp[j]时dp[j - weights[i - 1]]为上一行的结果
                // 由于复用空间，j < weights[i - 1]的部分不用更新，自动会是dp[i - 1][j]
                if (dp[j - weights[i - 1]] + values[i - 1] > dp[j]) dp[j] = dp[j - weights[i - 1]] + values[i - 1];
            }
        }
        return dp[W];
    }

    public static void main(String[] args) {
        ZeroOneKnapsack zok = new ZeroOneKnapsack();
        System.out.println(zok.zeroOneKnapsack(3, new int[]{4,2,3}, new int[]{2,1,3}, 2));
        System.out.println(zok.zeroOneKnapsack(3, new int[]{4,2,3}, new int[]{2,1,3}, 4));
        System.out.println(zok.zeroOneKnapsack_implemention2(3, new int[]{4,2,3}, new int[]{2,1,3}, 2));
        System.out.println(zok.zeroOneKnapsack_implemention2(3, new int[]{4,2,3}, new int[]{2,1,3}, 4));
    }
}
