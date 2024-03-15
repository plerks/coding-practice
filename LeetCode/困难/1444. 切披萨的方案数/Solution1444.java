/*
url: https://leetcode.cn/problems/number-of-ways-of-cutting-a-pizza/
LeetCode参考: https://leetcode.cn/problems/number-of-ways-of-cutting-a-pizza/solutions/2387392/qie-pi-sa-de-fang-an-shu-by-leetcode-sol-7ik7/
相关: LeetCode2312. 卖木头块
标签: 动态规划, 切矩形
*/
public class Solution1444 {
    public int ways(String[] pizza, int k) {
        int m = pizza.length, n = pizza[0].length(), mod = (int)(1e9 + 7);
        int[][] apples = new int[m + 1][n + 1];
        int[][][] dp = new int[k + 1][m][n];

        // 预处理计算apples数组，apples[i][j]表示右下侧的苹果数量。这里apples多一行列是方便计算，下面要用到i + 1, j + 1
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                apples[i][j] = (pizza[i].charAt(j) == 'A' ? 1 : 0) + apples[i + 1][j] + apples[i][j + 1] - apples[i + 1][j + 1];
                dp[1][i][j] = apples[i][j] > 0 ? 1 : 0;
            }
        }

        for (int z = 2; z <= k; z++)
            for (int i = 0; i < m; i++)
                for (int j = 0; j < n; j++) {
                    // 尝试在不同行水平切
                    for (int i2 = i + 1; i2 < m; i2++) {
                        // 如果这行有苹果就是个方案
                        if (apples[i][j] > apples[i2][j]) {
                            dp[z][i][j] = (dp[z][i][j] + dp[z - 1][i2][j]) % mod;
                        }
                    }
                    // 竖直方向
                    for (int j2 = j + 1; j2 < n; j2++) {
                        if (apples[i][j] > apples[i][j2]) {
                            dp[z][i][j] = (dp[z][i][j] + dp[z - 1][i][j2]) % mod;
                        }
                    }
                }
        return dp[k][0][0];
    }

    public static void main(String[] args) {
        Solution1444 solu = new Solution1444();
        System.out.println(solu.ways(new String[]{"AAAA.","A..A.","AA.AA"}, 5));
    }
}