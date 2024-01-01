/*
url: https://leetcode.cn/problems/binary-search-tree-to-greater-sum-tree/
标签: 逆中序遍历
*/

public class Solution1038 {
    int sum = 0;

    public TreeNode bstToGst(TreeNode root) {
        inversePreorder(root);
        return root;
    }

    private void inversePreorder(TreeNode root) {
        // 中序遍历得到的是从小到大的序列，则逆中序则是从大到小的序列
        if (root == null) return;
        inversePreorder(root.right); // sum现在是累加了所有比root.val大的
        sum += root.val;
        root.val = sum;
        inversePreorder(root.left);
    }

    public static void main(String[] args) {
    }
}
