/*
url: https://leetcode.cn/problems/house-robber-iii/?envType=daily-question&envId=2023-09-18
LeetCode参考: https://leetcode.cn/problems/house-robber-iii/solutions/361038/da-jia-jie-she-iii-by-leetcode-solution/
标签: 动态规划, 树动态规划, dfs, 后序遍历
*/

public class Solution337 {
    public int rob(TreeNode root) {
        int[] result = dfs(root); // result[0]表示选root的最大值，result[0]表示不选root的最大值
        return Math.max(result[0], result[1]);
    }

    private int[] dfs(TreeNode root) {
        if (root == null) return new int[]{0, 0};
        int[] l = dfs(root.left);
        int[] r = dfs(root.right);
        int selected = root.val + l[1] + r[1]; // 选root
        int notSelected = Math.max(l[0], l[1]) + Math.max(r[0], r[1]); // 不选root
        return new int[]{selected, notSelected};
    }

    public static void main(String[] args) {
    }
}