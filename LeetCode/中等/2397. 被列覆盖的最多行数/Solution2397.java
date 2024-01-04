/*
url: https://leetcode.cn/problems/maximum-rows-covered-by-columns/description/?envType=daily-question&envId=2024-01-04
LeetCode参考: https://leetcode.cn/problems/maximum-rows-covered-by-columns/solutions/1798794/by-endlesscheng-dvxe/
              https://leetcode.cn/problems/maximum-rows-covered-by-columns/solutions/2587986/bei-lie-fu-gai-de-zui-duo-xing-shu-by-le-5kb9/
标签: Gosper's Hack算法
*/

public class Solution2397 {
    public int maximumRows(int[][] matrix, int numSelect) {
        // 需要枚举列的选取情况
        int m = matrix.length, n = matrix[0].length;
        int[] mask = new int[m];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                mask[i] = (mask[i] << 1) | matrix[i][j];
            }
        }
        int ans = 0;
        int select = (1 << numSelect) - 1; // 例如numSelect = 3，则初始的列选取为111
        while (select <= ((1 << numSelect) - 1) << (n - numSelect)) { // ((1 << numSelect) - 1) << (n - numSelect)为最大的选取情况
            int count = 0;
            for (int i = 0; i < m; i++) {
                if ((mask[i] & select) == mask[i]) {
                    count++;
                }
            }
            ans = Math.max(ans, count);
            int lowbit = select & -select;
            int x = select + lowbit;
            select = ((select ^ x) / lowbit >> 2) | x; // Gosper's Hack算法，能直接计算出下一个有numSelect个1的列选取情况
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution2397 solu = new Solution2397();
        System.out.println(solu.maximumRows(new int[][]{{0,0,0},{1,0,1},{0,1,1},{0,0,1}}, 2));
        System.out.println(solu.maximumRows(new int[][]{{1},{0}}, 1));
    }
}
