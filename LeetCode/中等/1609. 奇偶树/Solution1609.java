/*
url: https://leetcode.cn/problems/even-odd-tree/
LeetCode参考: https://leetcode.cn/problems/even-odd-tree/solutions/2303204/ceng-ci-bian-li-tiao-jian-pan-ding-by-he-l7c8/
*/

import java.util.Deque;
import java.util.LinkedList;

public class Solution1609 {
    public boolean isEvenOddTree(TreeNode root) {
        if (root == null) return true;
        Deque<TreeNode> queue = new LinkedList<>();
        int level = 0;
        queue.offer(root);
        while (!queue.isEmpty()) {
            int size = queue.size();
            int pre;
            if (level % 2 == 0) {
                pre = Integer.MIN_VALUE;
            }
            else {
                pre = Integer.MAX_VALUE;
            }
            for (int i = 0; i < size; i++) {
                TreeNode p = queue.poll();
                if (p.left != null) queue.offer(p.left);
                if (p.right != null) queue.offer(p.right);
                if (level % 2 == 0) {
                    if (p.val % 2 == 0 || p.val <= pre) return false;
                }
                else {
                    if (p.val % 2 == 1 || p.val >= pre) return false;
                }
                pre = p.val;
            }
            level++;
        }
        return true;
        // 还有一种在层序遍历中知道层号的方法是把TreeNode包装成LeveledTreeNode，增加一个level属性，root为0，然后节点加入queue时level为父的level + 1
    }

    public static void main(String[] args) {
        TreeNode root = new TreeNode(5);
        TreeNode node4 = new TreeNode(4);
        TreeNode node2 = new TreeNode(2);
        TreeNode node3_1 = new TreeNode(3);
        TreeNode node3_2 = new TreeNode(3);
        TreeNode node7 = new TreeNode(7);
        root.left = node4;
        root.right = node2;
        node4.left = node3_1;
        node4.right = node3_2;
        node2.left = node7;
        Solution1609 solu = new Solution1609();
        System.out.println(solu.isEvenOddTree(root));
    }
}

class TreeNode {
    int val;
    TreeNode left;
    TreeNode right;
    TreeNode() {}
    TreeNode(int val) { this.val = val; }
    TreeNode(int val, TreeNode left, TreeNode right) {
        this.val = val;
        this.left = left;
        this.right = right;
    }
}