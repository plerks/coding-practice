/*
url: https://leetcode.cn/problems/binary-tree-zigzag-level-order-traversal/description/?envType=daily-question&envId=2024-02-16
相关: LeetCode102. 二叉树的层序遍历, LeetCode107. 二叉树的层序遍历 II
标签: 层序遍历
*/

import java.util.*;

public class Solution103 {
    public List<List<Integer>> zigzagLevelOrder(TreeNode root) {
        Deque<TreeNode> q = new LinkedList<>();
        List<List<Integer>> ans = new ArrayList<>();
        if (root != null) q.offer(root);
        int level = -1;
        while (!q.isEmpty()) {
            int size = q.size();
            List<Integer> list = new ArrayList<>();
            level++;
            for (int i = 0; i < size; i++) {
                TreeNode node = q.poll();
                list.add(node.val);
                if (node.left != null) q.offer(node.left);
                if (node.right != null) q.offer(node.right);
            }
            if (level % 2 == 1) Collections.reverse(list);
            ans.add(list);
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution103 solu = new Solution103();
        System.out.println(solu.zigzagLevelOrder(new TreeNode(3, new TreeNode(9), new TreeNode(20, new TreeNode(15), new TreeNode(7)))));
    }
}
