/*
url: https://leetcode.cn/problems/search-a-2d-matrix-ii/
LeetCode参考: https://leetcode.cn/problems/search-a-2d-matrix-ii/solutions/1062538/sou-suo-er-wei-ju-zhen-ii-by-leetcode-so-9hcx/
相关: LeetCodeLCR 121. 寻找目标值 - 二维数组
标签: 二分查找, Z字形查找
*/

// 此题与LeetCodeLCR 121. 寻找目标值 - 二维数组完全相同，先做的那道题，然后LeetCode有提示LCR 121与240题相同，直接搬过来
public class Solution240 {
    public boolean searchMatrix(int[][] matrix, int target) {
        if (matrix.length == 0) return false;
        int i = 0, j = matrix[0].length - 1;
        while (i < matrix.length && j >= 0) {
            if (matrix[i][j] == target) return true;
            else if (matrix[i][j] > target) j--;
            else i++;
        }
        return false;
    }

    public static void main(String[] args) {
        Solution240 solu = new Solution240();
        System.out.println(solu.searchMatrix(new int[][]{{1,3,5,7,9},{2,4,6,8,10},{11,13,15,17,19},{12,14,16,18,20},{21,22,23,24,25}}, 13));
    }
}
