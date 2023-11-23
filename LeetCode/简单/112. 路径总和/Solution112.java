/*
url: https://leetcode.cn/problems/path-sum/
相关: LeetCode113. 路径总和 II
标签: dfs
*/

public class Solution112 {
    public boolean hasPathSum(TreeNode root, int targetSum) {
        return dfs(root, targetSum);
    }

    private boolean dfs(TreeNode root, int targetSum) {
        if (root == null) return false;
        if (root.left == null && root.right == null && targetSum == root.val) return true;
        return dfs(root.left, targetSum - root.val) || dfs(root.right, targetSum - root.val);
    }

    public static void main(String[] args) {
    }
}
