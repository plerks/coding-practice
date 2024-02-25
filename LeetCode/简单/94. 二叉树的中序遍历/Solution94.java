/*
url: https://leetcode.cn/problems/binary-tree-inorder-traversal/
相关: LeetCode144. 二叉树的前序遍历
      LeetCode145. 二叉树的后序遍历
      LeetCode105. 从前序与中序遍历序列构造二叉树
      LeetCode106. 从中序与后序遍历序列构造二叉树
      LeetCode889. 根据前序和后序遍历构造二叉树
      LeetCode589. N 叉树的前序遍历
      LeetCode590. N 叉树的后序遍历
      LeetCodeLCR 053. 二叉搜索树中的中序后继
标签: 中序遍历, 迭代版中序遍历
*/

import java.util.ArrayList;
import java.util.Deque;
import java.util.LinkedList;
import java.util.List;

public class Solution94 {
    public List<Integer> inorderTraversal(TreeNode root) {
        List<Integer> ans = new ArrayList<>();
        inorder(root, ans);
        return ans;
    }

    private void inorder(TreeNode root, List<Integer> ans) {
        if (root == null) return;
        inorder(root.left, ans);
        ans.add(root.val);
        inorder(root.right, ans);
    }

    // 迭代版
    public List<Integer> inorderTraversal_implementation2(TreeNode root) {
        List<Integer> ans = new ArrayList<>();
        Deque<TreeNode> stack = new LinkedList<>();
        TreeNode node = root;
        while (true) {
            // 沿左侧通路
            while (node != null) {
                stack.push(node);
                node = node.left;
            }
            if (stack.isEmpty()) break;
            // 转向右子树
            node = stack.pop();
            ans.add(node.val); // visit
            node = node.right;
        }
        return ans;
    }

    public static void main(String[] args) {
    }
}