/*
url: https://leetcode.cn/problems/binary-tree-level-order-traversal-ii/description/?envType=daily-question&envId=2024-02-15
相关: LeetCode102. 二叉树的层序遍历
标签: 层序遍历
*/

import java.util.*;

public class Solution107 {
    public List<List<Integer>> levelOrderBottom(TreeNode root) {
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
        Collections.reverse(ans);
        return ans;
    }

    public static void main(String[] args) {
        Solution107 solu = new Solution107();
        System.out.println(solu.levelOrderBottom(new TreeNode(3, new TreeNode(9), new TreeNode(20, new TreeNode(15), new TreeNode(7)))));
    }
}
