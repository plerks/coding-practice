// https://leetcode.cn/problems/first-completely-painted-row-or-column/

public class Solution2661 {
    public int firstCompleteIndex(int[] arr, int[][] mat) {
        int m = mat.length, n = mat[0].length;
        int max = Math.max(m, n); // max用于进制表示法
        // 输入数组元素[1，m * n]，记录每个数字在哪行哪列
        long[] map = new long[m * n];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                map[mat[i][j] - 1] = (long)i * max + j;
            }
        }
        int[] rows = new int[m]; // 每行涂色个数为0
        int[] cols = new int[n]; // 每列涂色个数为0
        for (int i = 0; i < arr.length; i++) {
            long pos = map[arr[i] - 1];
            int rowNum = (int)(pos / max);
            int colNum = (int)(pos % max);
            rows[rowNum]++;
            cols[colNum]++;
            if (rows[rowNum] == n || cols[colNum] == m) {
                return i;
            }
        }
        return -1;
    }

    public static void main(String[] args) {
        Solution2661 solu = new Solution2661();
        System.out.println(solu.firstCompleteIndex(new int[]{1,3,4,2}, new int[][]{{1,4},{2,3}}));
    }
}
