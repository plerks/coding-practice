/*
url: https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-search-tree/description/?envType=daily-question&envId=2024-02-25
相关: LeetCode236. 二叉树的最近公共祖先
标签: 最近公共祖先
*/

public class Solution235 {
    public TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {
        // 最近公共祖先的值一定在[p, q]之间，从上往下遇到的第一个就是最近公共祖先
        if (p.val > q.val) {
            TreeNode temp = p;
            p = q;
            q = temp;
        }
        while (root.val < p.val || root.val > q.val) {
            if (root.val < p.val) root = root.right;
            else root = root.left;
        }
        return root;
    }

    public static void main(String[] args) {
        Solution235 solu = new Solution235();
        TreeNode n2 = new TreeNode(2);
        TreeNode n8 = new TreeNode(8);
        TreeNode root = new TreeNode(6, n2, n8);
        System.out.println(solu.lowestCommonAncestor(root, n2, n8).val);
    }
}
