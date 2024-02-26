/*
url: https://leetcode.cn/problems/er-wei-shu-zu-zhong-de-cha-zhao-lcof/description/
LeetCode参考: https://leetcode.cn/problems/er-wei-shu-zu-zhong-de-cha-zhao-lcof/solutions/95306/mian-shi-ti-04-er-wei-shu-zu-zhong-de-cha-zhao-zuo/
相关: LeetCode240. 搜索二维矩阵 II
标签: 二分查找, Z字形查找
*/

// 此题与LeetCode240. 搜索二维矩阵 II完全相同
public class SolutionLCR121 {
    // 我的解法，虽然是递归的二分，但是实际LeetCode上运行用时0ms。但是问题是代码巨繁琐。
    public boolean findTargetIn2DPlants(int[][] plants, int target) {
        if (plants.length == 0 || plants[0].length == 0) return false;
        return myFindTargetIn2DPlants(plants, target, 0, plants.length - 1, 0, plants[0].length - 1);
    }

    private boolean myFindTargetIn2DPlants(int[][] plants, int target, int i1, int i2, int j1, int j2) {
        if (i1 > i2 || j1 > j2) return false;
        if (plants[i1][j1] == target) return true;
        if (plants[i1][j1] > target) return false;
        boolean ans = false;
        int mid1 = (i1 + i2) / 2;
        if (plants[mid1][j1] == target) return true;
        // 在搜索下半块前，target可能在mid1这一行存在，需要搜索
        if (plants[mid1][j1] < target) {
            for (int j = j1; j <= j2; j++) {
                if (plants[mid1][j] == target) return true;
            }
            ans |= myFindTargetIn2DPlants(plants, target, mid1 + 1, i2, j1, j2);
        }
        else ans |= myFindTargetIn2DPlants(plants, target, i1, mid1 - 1, j1, j2);
        int mid2 = (j1 + j2) / 2;
        if (plants[i1][mid2] == target) return true;
        // 在搜索右半块前，target可能在mid2这一列存在，需要搜索
        if (plants[i1][mid2] < target) {
            for (int i = i1; i <= i2; i++) {
                if (plants[i][mid2] == target) return true;
            }
            ans |= myFindTargetIn2DPlants(plants, target, i1, i2, mid2 + 1, j2);
        }
        else ans |= myFindTargetIn2DPlants(plants, target, i1, i2, j1, mid2 - 1);
        return ans;
    }

    // 参考题解的解法，非常巧妙，将矩阵旋转45度，从右上角开始看，则向左(j--)走变小，向右(i++)走变大，类似二叉搜索树，从而也实现了二分的查找
    public boolean findTargetIn2DPlants_implementation2(int[][] plants, int target) {
        // 这里选择右上角作为起点，也可以选择左下角
        if (plants.length == 0) return false;
        int i = 0, j = plants[0].length - 1;
        while (i < plants.length && j >= 0) {
            if (plants[i][j] == target) return true;
            else if (plants[i][j] > target) j--;
            else i++;
        }
        return false;
    }

    public static void main(String[] args) {
        SolutionLCR121 solu = new SolutionLCR121();
        // System.out.println(solu.findTargetIn2DPlants(new int[][]{{2,3,6,8},{4,5,8,9},{5,9,10,12}}, 8));
        // System.out.println(solu.findTargetIn2DPlants(new int[][]{}, 0));
        // System.out.println(solu.findTargetIn2DPlants(new int[][]{{-1,3}}, 3));
        // System.out.println(solu.findTargetIn2DPlants(new int[][]{{1,4},{2,5}}, 5));
        System.out.println(solu.findTargetIn2DPlants(new int[][]{{1,3,5,7,9},{2,4,6,8,10},{11,13,15,17,19},{12,14,16,18,20},{21,22,23,24,25}}, 13));
        System.out.println(solu.findTargetIn2DPlants_implementation2(new int[][]{{1,3,5,7,9},{2,4,6,8,10},{11,13,15,17,19},{12,14,16,18,20},{21,22,23,24,25}}, 13));
    }
}
