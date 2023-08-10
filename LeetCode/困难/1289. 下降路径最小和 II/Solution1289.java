/*
url: https://leetcode.cn/problems/minimum-falling-path-sum-ii/
LeetCode参考: https://leetcode.cn/problems/minimum-falling-path-sum-ii/solutions/101728/xia-jiang-lu-jing-zui-xiao-he-ii-by-leetcode-solut/
标签: 动态规划
*/

public class Solution1289 {
    public int minFallingPathSum(int[][] grid) {
        // 动态规划，无需回溯
        int[][] dp = new int[grid.length][grid[0].length];
        for (int i = 1; i < dp.length; i++) {
            for (int j = 0; j < dp[0].length; j++) {
                dp[i][j] = Integer.MAX_VALUE;
            }
        }
        for (int i = 0; i < dp[0].length; i++) {
            dp[0][i] = grid[0][i];
        }
        for (int i = 1; i < dp.length; i++) {
            for (int j = 0; j < dp[0].length; j++) {
                for (int k = 0; k < dp[i - 1].length; k++) {
                    if (j == k) continue;
                    dp[i][j] = Math.min(dp[i][j], dp[i - 1][k] + grid[i][j]);
                }
            }
        }
        int ans = Integer.MAX_VALUE;
        for (int i = 0; i <= dp[dp.length - 1].length - 1; i++) {
            ans = Math.min(ans, dp[dp.length - 1][i]);
        }
        return ans;
    }

    public int minFallingPathSum_implementation2(int[][] grid) {
        // 可以不用先用grid第一行初始化lastMin, lastSecondMin, lastMinIndex, 一并归入循环里
        int lastMin = 0, lastSecondMin = 0, lastMinIndex = -1;
        for (int i = 0; i < grid.length; i++) {
            int currentMin = Integer.MAX_VALUE, currentSecondMin = Integer.MAX_VALUE, currentMinIndex = -1;
            for (int j = 0; j < grid[0].length; j++) {
                int currentMinSum = (j == lastMinIndex ? lastSecondMin : lastMin) + grid[i][j];
                if (currentMinSum < currentMin) {
                    currentSecondMin = currentMin;
                    currentMin = currentMinSum;
                    currentMinIndex = j;
                }
                // 这里currentSecondMin可以取等于currentMin的值，以{{1,2,3},{4,5,6},{7,8,9}}为例，1，5和2，4都是6，lastIndex==0会导致第三行取不了7
                else if (currentMinSum >= currentMin && currentMinSum < currentSecondMin) {
                    currentSecondMin = currentMinSum;
                }
            }
            lastMin = currentMin;
            lastSecondMin = currentSecondMin;
            lastMinIndex = currentMinIndex;
        }
        return lastMin;
    }

    public static void main(String[] args) {
        Solution1289 solu = new Solution1289();
        System.out.println(solu.minFallingPathSum_implementation2(new int[][]{{1,2,3},{4,5,6},{7,8,9}}));
    }
}