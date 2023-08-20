// https://leetcode.cn/problems/root-equals-sum-of-children/

public class Solution2236 {
    public boolean checkTree(TreeNode root) {
        return root.val == root.left.val + root.right.val;
    }

    public static void main(String[] args) {
    }
}