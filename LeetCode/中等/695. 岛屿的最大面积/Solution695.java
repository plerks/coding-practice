// https://leetcode.cn/problems/max-area-of-island/

class Solution695 {
    int count = 0;
	public int maxAreaOfIsland (int[][] grid) {
        // write code here
		int res = Integer.MIN_VALUE;
		boolean[][] discovered = new boolean[grid.length][grid[0].length];
		for(int i = 0;i < grid.length;i++)
			for(int j = 0;j < grid[0].length;j++) {
				//if(discovered[i][j]==true || grid[i][j]==0) continue;
				count = 0;
				dfsAround(grid,i,j,discovered);
				if(count > res) res = count;
			}
		return res;
    }

	private void dfsAround(int[][] grid, int i, int j, boolean[][] discovered) {
		if(i<0 || i>=grid.length || j<0 || j>=grid[0].length || discovered[i][j]==true || grid[i][j]==0) return;
		discovered[i][j] = true;
		count++;
		dfsAround(grid,i-1,j,discovered);
		dfsAround(grid,i+1,j,discovered);
		dfsAround(grid,i,j-1,discovered);
		dfsAround(grid,i,j+1,discovered);
	}

    public static void main(String[] args) {
        
    }
}