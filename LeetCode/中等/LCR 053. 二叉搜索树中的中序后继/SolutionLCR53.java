/*
url: https://leetcode.cn/problems/P5rCT8/
LeetCode参考: https://leetcode.cn/problems/P5rCT8/solutions/1490641/er-cha-sou-suo-shu-zhong-de-zhong-xu-hou-5nrz/
标签: 二叉搜索树, 中序遍历, 中序后继
*/

public class Solution {
    public TreeNode inorderSuccessor(TreeNode root, TreeNode p) {
        // 有右子树，中序后继在右子树中
        if (p.right != null) {
            p = p.right;
            while (p.left != null) {
                p = p.left;
            }
            return p;
        }
        // 无右子树，一直往左上走，然后往右上走一步，但是这里TreeNode没有parent指针，得变一下
        TreeNode ans = null;
        TreeNode node = root;
        while (node != null) {
            if (node.val > p.val) { // p的中序后继为node或在node的左子树
                ans = node;
                node = node.left;
            }
            else { // p的中序后继可能有，在node的右子树
                node = node.right;
            }
        }
        return ans;
    }

    public static void main(String[] args) {
    }
}
