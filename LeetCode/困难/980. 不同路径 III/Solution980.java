// https://leetcode.cn/problems/unique-paths-iii/

public class Solution980 {
    private int ans = 0;

    public int uniquePathsIII(int[][] grid) {
        int[][] visited = new int[grid.length][grid[0].length];
        int startI = 0, startJ = 0, endI = 0, endJ = 0, noObstacleCount = 0;
        for (int i = 0; i < grid.length; i++)
            for (int j = 0; j < grid[0].length; j++) {
                if (grid[i][j] == 1) {
                    startI = i;
                    startJ = j;
                }
                if (grid[i][j] != -1) {
                    noObstacleCount++;
                }
            }
        dfs(startI, startJ, grid, visited, 0, noObstacleCount);
        return ans;
    }

    private void dfs(int i, int j, int[][] grid, int[][] visited, int visitedCount, int noObstacleCount) {
        if (i < 0 || i >= grid.length || j < 0 || j >= grid[0].length) {
            return;
        }
        if (grid[i][j] == -1) {
            return;
        }
        if (visited[i][j] == 1) {
            return;
        }
        visited[i][j] = 1;
        visitedCount++;
        if (grid[i][j] == 2 && visitedCount == noObstacleCount) {
            ans++;
            visited[i][j] = 0;
            return;
        }
        else {
            dfs(i - 1, j, grid, visited, visitedCount, noObstacleCount);
            dfs(i + 1, j, grid, visited, visitedCount, noObstacleCount);
            dfs(i, j - 1, grid, visited, visitedCount, noObstacleCount);
            dfs(i, j + 1, grid, visited, visitedCount, noObstacleCount);
            visited[i][j] = 0;
            visitedCount--;
        }
    }

    public static void main(String[] args) {
        Solution980 solu = new Solution980();
        System.out.println(solu.uniquePathsIII(new int[][]{{1,0,0,0},{0,0,0,0},{0,0,0,2}}));
    }
}