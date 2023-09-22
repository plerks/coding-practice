/*
url: https://leetcode.cn/problems/binary-tree-inorder-traversal/
相关: https://leetcode.cn/problems/binary-tree-preorder-traversal/
      https://leetcode.cn/problems/binary-tree-postorder-traversal/
      https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
      https://leetcode.cn/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
      https://leetcode.cn/problems/P5rCT8/
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