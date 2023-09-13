// https://leetcode.cn/problems/check-knight-tour-configuration/?envType=daily-question&envId=2023-09-13

import java.util.HashMap;

public class Solution2596 {
    public boolean checkValidGrid(int[][] grid) {
        HashMap<Integer, int[]> map = new HashMap<>();
        if (grid[0][0] != 0) return false;
        for (int i = 0; i < grid.length; i++) {
            for (int j = 0; j < grid[0].length; j++) {
                map.put(grid[i][j], new int[]{i, j});
            }
        }
        int x = 0, y = 0;
        int n = grid.length;
        for (int step = 1; step <= n * n - 1; step++) {
            int nextX = map.get(step)[0];
            int nextY = map.get(step)[1];
            if (!checkValid(x, y, nextX, nextY)) {
                return false;
            }
            x = nextX;
            y = nextY;
        }
        return true;
    }

    public boolean checkValidGrid_implementation2(int[][] grid) {
        if (grid[0][0] != 0) return false;
        int n = grid.length;
        int[][] path = new int[n * n][2]; // path[i]表示第i步的坐标
        for (int i = 0; i < grid.length; i++) {
            for (int j = 0; j < grid[0].length; j++) {
                path[grid[i][j]][0] = i;
                path[grid[i][j]][1] = j;
            }
        }
        int x = 0, y = 0;
        for (int step = 1; step <= n * n - 1; step++) {
            int nextX = path[step][0];
            int nextY = path[step][1];
            if (!checkValid(x, y, nextX, nextY)) {
                return false;
            }
            x = nextX;
            y = nextY;
        }
        return true;
    }

    private boolean checkValid(int x, int y, int nextX, int nextY) {
        if (Math.abs(x - nextX) == 1 && Math.abs(y - nextY) == 2
        || Math.abs(x - nextX) == 2 && Math.abs(y - nextY) == 1) {
            return true;
        }
        return false;
    }

    public static void main(String[] args) {
        Solution2596 solu = new Solution2596();
        System.out.println(solu.checkValidGrid(new int[][]{{0,3,6},{5,8,1},{2,7,4}}));
        System.out.println(solu.checkValidGrid_implementation2(new int[][]{{0,3,6},{5,8,1},{2,7,4}}));
    }
}