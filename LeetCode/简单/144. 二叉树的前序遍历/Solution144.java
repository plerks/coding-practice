/*
url: https://leetcode.cn/problems/binary-tree-preorder-traversal/
相关: LeetCode94. 二叉树的中序遍历
      LeetCode145. 二叉树的后序遍历
      LeetCode105. 从前序与中序遍历序列构造二叉树
      LeetCode106. 从中序与后序遍历序列构造二叉树
      LeetCode889. 根据前序和后序遍历构造二叉树
      LeetCode589. N 叉树的前序遍历
      LeetCode590. N 叉树的后序遍历
LeetCode参考: https://leetcode.cn/problems/binary-tree-preorder-traversal/solutions/461821/er-cha-shu-de-qian-xu-bian-li-by-leetcode-solution/
标签: 前序遍历, 迭代版前序遍历, 先序遍历, 迭代版先序遍历
*/

import java.util.*;

public class Solution144 {
    public List<Integer> preorderTraversal(TreeNode root) {
        List<Integer> ans = new ArrayList<>();
        preorder(root, ans);
        return ans;
    }

    private void preorder(TreeNode root, List<Integer> ans) {
        if (root == null) return;
        ans.add(root.val);
        preorder(root.left, ans);
        preorder(root.right, ans);
    }

    // 迭代版
    public List<Integer> preorderTraversal_implementation2(TreeNode root) {
        List<Integer> ans = new ArrayList<>();
        Deque<TreeNode> stack = new LinkedList<>();
        TreeNode node = root;
        while (true) {
            // 沿左侧通路访问
            while (node != null) {
                ans.add(node.val); // visit
                stack.push(node);
                node = node.left;
            }
            if (stack.isEmpty()) break;
            // 转向右子树
            node = stack.pop();
            node = node.right;
        }
        return ans;
    }

    // 迭代版2，参考LeetCode589. N 叉树的前序遍历preorder_implementation3()
    public List<Integer> preorderTraversal_implementation3(TreeNode root) {
        List<Integer> ans = new ArrayList<>();
        Deque<TreeNode> stack = new LinkedList<>();
        if (root != null) stack.push(root);
        while (!stack.isEmpty()) {
            TreeNode node = stack.pop();
            ans.add(node.val);
            if (node.right != null) stack.push(node.right);
            if (node.left != null) stack.push(node.left);
        }
        return ans;
    }

    public static void main(String[] args) {
    }
}
