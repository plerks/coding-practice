// https://leetcode.cn/problems/count-servers-that-communicate/

public class Solution1267 {
    public int countServers(int[][] grid) {
        // 每一行的server数量
        int[] rows = new int[grid.length];
        int[] cols = new int[grid[0].length];
        for (int i = 0; i < grid.length; i++) {
            for (int j = 0; j < grid[0].length; j++) {
                if (grid[i][j] == 1) {
                    rows[i]++;
                    cols[j]++;
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < grid.length; i++) {
            for (int j = 0; j < grid[0].length; j++) {
                if (grid[i][j] == 1) {
                    if (rows[i] >= 2 || cols[j] >= 2) {
                        ans++;
                    }
                }
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution1267 solu = new Solution1267();
        System.out.println(solu.countServers(new int[][]{{0,1}, {1,0}}));
    }
}