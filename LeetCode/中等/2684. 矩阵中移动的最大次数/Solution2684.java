/*
url: https://leetcode.cn/problems/maximum-number-of-moves-in-a-grid/description/?envType=daily-question&envId=2024-03-16
LeetCode参考: https://leetcode.cn/problems/maximum-number-of-moves-in-a-grid/solutions/2269244/cong-ji-yi-hua-sou-suo-dao-di-tui-by-end-pgq3/
              https://leetcode.cn/problems/maximum-number-of-moves-in-a-grid/solutions/2684036/ju-zhen-zhong-yi-dong-de-zui-da-ci-shu-b-b7jx/
标签: 动态规划, 列优先动态规划
*/

// 这题灵茶山艾府的题解和官方题解思路是用的dfs和bfs，dfs偏暴力模拟，bfs和我这样dp类似，dp要简单些。
public class Solution2684 {
    public int maxMoves(int[][] grid) {
        int m = grid.length;
        int n = grid[0].length;
        int[][] dp = new int[m][n];
        int ans = 0;
        /* 按列来遍历，因为dp[i][j]依赖的是左，左上，左下3个位置，能走到的话步数就是列号。
        dp[i][j] == -1表示走不到这里，需要这样区分，因为有可能从(i,j)能到(i,j+1)，不区分的话dp[i][j+1] = j+1，但是本身到不了(i,j) */
        for (int j = 1; j < n; j++) {
            for (int i = 0; i < m; i++) {
                dp[i][j] = -1;
                if (i - 1 >= 0 && j - 1 >= 0 && dp[i - 1][j - 1] != -1 && grid[i - 1][j - 1] < grid[i][j]) {
                    dp[i][j] = j;
                }
                else if (j - 1 >= 0 && dp[i][j - 1] != -1 && grid[i][j - 1] < grid[i][j]) {
                    dp[i][j] = j;
                }
                else if (i + 1 < m && j - 1 >= 0 && dp[i + 1][j - 1] != -1 && grid[i + 1][j - 1] < grid[i][j]) {
                    dp[i][j] = j;
                }
                ans = Math.max(ans, dp[i][j]);
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution2684 solu = new Solution2684();
        // System.out.println(solu.maxMoves(new int[][]{{2,4,3,5},{5,4,9,3},{3,4,2,11},{10,9,13,15}}));
        System.out.println(solu.maxMoves(new int[][]{{3,2,4},{2,1,9},{1,1,7}}));
    }
}
