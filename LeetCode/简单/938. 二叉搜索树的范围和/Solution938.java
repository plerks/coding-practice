/*
url: https://leetcode.cn/problems/range-sum-of-bst/description/?envType=daily-question&envId=2024-02-26
LeetCode参考: https://leetcode.cn/problems/range-sum-of-bst/solutions/746069/er-cha-sou-suo-shu-de-fan-wei-he-by-leet-rpq7/
相关: LeetCode94. 二叉树的中序遍历
相关: dfs, bfs, 层序遍历
*/

import java.util.*;

public class Solution938 {
    // 中序遍历的迭代版，LeetCode运行用时6ms
    public int rangeSumBST(TreeNode root, int low, int high) {
        // 只需能求<=x的节点的sum，并考虑到二叉搜索树的中序遍历是按升序遍历的
        Deque<TreeNode> stack = new LinkedList<>();
        stack.push(root);
        TreeNode node = root;
        int sum1 = 0; // <= low - 1的节点的和
        while (true) {
            while (node != null) {
                stack.push(node);
                node = node.left;
            }
            if (stack.isEmpty()) break;
            node = stack.pop();
            if (node.val >= low) break;
            sum1 += node.val;
            node = node.right;
        }
        stack.clear();
        node = root;
        int sum2 = 0; // <= high的节点的和
        while (true) {
            while (node != null) {
                stack.push(node);
                node = node.left;
            }
            if (stack.isEmpty()) break;
            node = stack.pop();
            if (node.val > high) break;
            sum2 += node.val;
            node = node.right;
        }
        return sum2 - sum1;
    }

    // 中序遍历的递归版，LeetCode运行用时1ms
    public int rangeSumBST_implementation2(TreeNode root, int low, int high) {
        return inorder(root, high) - inorder(root, low - 1); // inorder()返回<=x的总和
    }

    private int inorder(TreeNode root, int x) {
        if (root == null) return 0;
        int sum = 0;
        sum += inorder(root.left, x);
        if (root.val <= x) sum += root.val;
        if (root.val < x) {
            sum += inorder(root.right, x);
        }
        return sum;
    }

    // 官方题解的解法，结合了一定的剪枝，不用两轮计算，LeetCode运行用时0ms
    public int rangeSumBST_implementation3(TreeNode root, int low, int high) {
        if (root == null) return 0;
        if (root.val < low) return rangeSumBST_implementation3(root.right, low, high);
        if (root.val > high) return rangeSumBST_implementation3(root.left, low, high);
        return root.val + rangeSumBST_implementation3(root.left, low, high) + rangeSumBST_implementation3(root.right, low, high);
    }

    // 官方题解用层序遍历的解法，也结合了一定的剪枝，LeetCode运行用时3ms
    public int rangeSumBST_implementation4(TreeNode root, int low, int high) {
        Deque<TreeNode> q = new LinkedList<>();
        q.offer(root);
        int sum = 0;
        while (!q.isEmpty()) {
            TreeNode node = q.poll();
            if (node == null) continue;
            if (node.val < low) {
                q.offer(node.right);
            }
            else if (node.val > high) {
                q.offer(node.left);
            }
            else {
                sum += node.val;
                q.offer(node.left);
                q.offer(node.right);
            }
        }
        return sum;
    }

    public static void main(String[] args) {
        Solution938 solu = new Solution938();
        System.out.println(solu.rangeSumBST(new TreeNode(2, new TreeNode(1), new TreeNode(5)), 1, 3));
        System.out.println(solu.rangeSumBST_implementation2(new TreeNode(2, new TreeNode(1), new TreeNode(5)), 1, 3));
        System.out.println(solu.rangeSumBST_implementation3(new TreeNode(2, new TreeNode(1), new TreeNode(5)), 1, 3));
        System.out.println(solu.rangeSumBST_implementation4(new TreeNode(2, new TreeNode(1), new TreeNode(5)), 1, 3));
    }
}
