/*
url: https://leetcode.cn/problems/binary-tree-postorder-traversal/
相关: https://leetcode.cn/problems/binary-tree-preorder-traversal/
      https://leetcode.cn/problems/binary-tree-inorder-traversal/
      https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
      https://leetcode.cn/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
LeetCode参考: https://leetcode.cn/problems/binary-tree-postorder-traversal/solutions/431066/er-cha-shu-de-hou-xu-bian-li-by-leetcode-solution/
              https://leetcode.cn/problems/binary-tree-postorder-traversal/solutions/431066/er-cha-shu-de-hou-xu-bian-li-by-leetcode-solution/comments/1194730
标签: 后序遍历, 迭代版后序遍历
*/

import java.util.ArrayList;
import java.util.Deque;
import java.util.LinkedList;
import java.util.List;
import java.util.Stack;

public class Solution145 {
    public List<Integer> postorderTraversal(TreeNode root) {
        List<Integer> ans = new ArrayList<>();
        postorder(root, ans);
        return ans;
    }

    private void postorder(TreeNode root, List<Integer> ans) {
        if (root == null) return;
        postorder(root.left, ans);
        postorder(root.right, ans);
        ans.add(root.val);
    }

    // 迭代版
    public List<Integer> postorderTraversal_implementation2(TreeNode root) {
        List<Integer> ans = new ArrayList<>();
        Deque<TreeNode> stack = new LinkedList<>();
        TreeNode node = root;
        TreeNode prev = null; // 记录刚访问完的子树
        while (true) {
            while (node != null) {
                stack.push(node);
                node = node.left;
            }
            if (stack.isEmpty()) break;
            node = stack.pop(); // 此时左子树访问完了，但是不知道右子树是否访问了，从而不知道root是否可以访问，需借助prev
            if (node.right == null || node.right == prev) {
                ans.add(node.val);
                prev = node;
                node = null;
            }
            else {
                stack.push(node);
                node = node.right;
            }
        }
        return ans;
    }

    public static void main(String[] args) {
    }
}
