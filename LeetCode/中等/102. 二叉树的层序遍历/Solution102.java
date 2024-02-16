/*
url: https://leetcode.cn/problems/binary-tree-level-order-traversal/description/?envType=daily-question&envId=2024-02-14
相关: LeetCode107. 二叉树的层序遍历 II, LeetCode103. 二叉树的锯齿形层序遍历
标签: 层序遍历
*/

import java.util.*;

public class Solution102 {
    public List<List<Integer>> levelOrder(TreeNode root) {
        Deque<TreeNode> q = new LinkedList<>();
        List<List<Integer>> ans = new ArrayList<>();
        if (root != null) q.offer(root);
        while (!q.isEmpty()) {
            int size = q.size();
            List<Integer> list = new ArrayList<>();
            for (int i = 0; i < size; i++) {
                TreeNode node = q.poll();
                list.add(node.val);
                if (node.left != null) q.offer(node.left);
                if (node.right != null) q.offer(node.right);
            }
            ans.add(list);
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution102 solu = new Solution102();
        System.out.println(solu.levelOrder(new TreeNode(3, new TreeNode(9), new TreeNode(20, new TreeNode(15), new TreeNode(7)))));
    }
}
