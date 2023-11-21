/*
url: https://leetcode.cn/problems/minimum-path-cost-in-a-grid/?envType=daily-question&envId=2023-11-22
标签: 动态规划
*/

import java.util.Arrays;

public class Solution2304 {
    public int minPathCost(int[][] grid, int[][] moveCost) {
        int m = grid.length, n = grid[0].length;
        int[][] dp = new int[m][n];
        for (int[] arr : dp) Arrays.fill(arr, Integer.MAX_VALUE);
        for (int j = 0; j < n; j++) {
            dp[0][j] = grid[0][j];
        }
        for (int i = 0; i < m - 1; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < moveCost[grid[i][j]].length; k++) { // moveCost[grid[i][j]].length等于n
                    dp[i + 1][k] = Math.min(dp[i + 1][k], dp[i][j] + moveCost[grid[i][j]][k] + grid[i + 1][k]);
                }
            }
        }
        int ans = Integer.MAX_VALUE;
        for (int j = 0; j < n; j++) ans = Math.min(ans, dp[m - 1][j]);
        return ans;
    }

    // 一次递推仅涉及两行，用两行的dp数组滚动递推，减小空间使用
    public int minPathCost_implementation2(int[][] grid, int[][] moveCost) {
        int m = grid.length, n = grid[0].length;
        int[] prev = new int[n];
        int[] current = new int[n];
        for (int j = 0; j < n; j++) {
            prev[j] = grid[0][j];
        }
        Arrays.fill(current, Integer.MAX_VALUE);
        for (int i = 0; i < m - 1; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < moveCost[grid[i][j]].length; k++) { // moveCost[grid[i][j]].length等于n
                    current[k] = Math.min(current[k], prev[j] + moveCost[grid[i][j]][k] + grid[i + 1][k]);
                }
            }
            int[] temp = prev;
            prev = current;
            current = temp;
            Arrays.fill(current, Integer.MAX_VALUE);
        }
        int ans = Integer.MAX_VALUE;
        // prev现在对准最后一行
        for (int j = 0; j < n; j++) ans = Math.min(ans, prev[j]);
        return ans;
    }

    public static void main(String[] args) {
        Solution2304 solu = new Solution2304();
        System.out.println(solu.minPathCost(new int[][]{{5,3},{4,0},{2,1}}, new int[][]{{9,8},{1,5},{10,12},{18,6},{2,4},{14,3}}));
        System.out.println(solu.minPathCost_implementation2(new int[][]{{5,3},{4,0},{2,1}}, new int[][]{{9,8},{1,5},{10,12},{18,6},{2,4},{14,3}}));
    }
}
