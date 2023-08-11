/*
url: https://leetcode.cn/problems/matrix-diagonal-sum/
标签: 矩阵主对角线, 矩阵副对角线
*/

public class Solution1572 {
    public int diagonalSum(int[][] mat) {
        int sum = 0;
        int n = mat.length;
        for (int i = 0; i < n; i++) {
            sum += mat[i][i];
        }
        for (int i = 0; i < n; i++) {
            if (n - 1 - i == i) continue;
            sum += mat[i][n - 1 - i];
        }
        return sum;
    }

    public static void main(String[] args) {
        Solution1572 solu = new Solution1572();
        System.out.println(solu.diagonalSum(new int[][]{{2,4}, {1,2}}));
    }
}