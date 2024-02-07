/*
url: https://leetcode.cn/problems/cousins-in-binary-tree/description/?envType=daily-question&envId=2024-02-08
相关: LeetCode2641. 二叉树的堂兄弟节点 II
标签: 层序遍历, bfs, dfs
*/

import java.util.*;

public class Solution993 {
    // 用dfs应该也行
    public boolean isCousins(TreeNode root, int x, int y) {
        Deque<TreeNode> q = new LinkedList<>();
        q.offer(root);
        int foundCount = 0;
        int depth = -1;
        int depthX = -1;
        int depthY = -2;
        TreeNode parentX = null, parentY = null;
        while ((!q.isEmpty()) && (foundCount < 2)) {
            depth++;
            int size = q.size();
            for (int i = 0; i < size; i++) {
                TreeNode node = q.poll();
                if (node.left != null) {
                    if (node.left.val == x) {
                        depthX = depth + 1;
                        parentX = node;
                        foundCount++;
                    }
                    if (node.left.val == y) {
                        depthY = depth + 1;
                        parentY = node;
                        foundCount++;
                    }
                    q.offer(node.left);
                }
                if (node.right != null) {
                    if (node.right.val == x) {
                        depthX = depth + 1;
                        parentX = node;
                        foundCount++;
                    }
                    if (node.right.val == y) {
                        depthY = depth + 1;
                        parentY = node;
                        foundCount++;
                    }
                    q.offer(node.right);
                }
            }
        }
        return depthX == depthY && parentX != parentY;
    }

    public static void main(String[] args) {
        Solution993 solu = new Solution993();
        TreeNode root = new TreeNode(1, new TreeNode(2, null, new TreeNode(4)), new TreeNode(3, null, new TreeNode(5)));
        System.out.println(solu.isCousins(root, 5, 4));
    }
}
