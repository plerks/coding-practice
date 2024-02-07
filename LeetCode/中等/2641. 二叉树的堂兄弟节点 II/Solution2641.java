/*
url: https://leetcode.cn/problems/cousins-in-binary-tree-ii/description/?envType=daily-question&envId=2024-02-07
LeetCode参考: https://leetcode.cn/problems/cousins-in-binary-tree-ii/solutions/2626702/er-cha-shu-de-tang-xiong-di-jie-dian-ii-1b9oj/
相关: LeetCode993. 二叉树的堂兄弟节点
标签: 层序遍历
*/

import java.util.*;

public class Solution2641 {
    // 我的做法，需要两次层序遍历，一次统计各层和，一次改值
    public TreeNode replaceValueInTree(TreeNode root) {
        /* 将所有节点值变成堂兄弟节点值的和，由于堂兄弟都在同一层，考虑层序遍历。
        只需统计每一层的节点值之和，每个节点的最终值为层和减去这个节点及其兄弟的值。
        */
        HashMap<Integer, Integer> depthSum = new HashMap<>();
        Deque<TreeNode> q = new LinkedList<>();
        q.offer(root);
        int depth = -1;
        while (!q.isEmpty()) {
            depth++;
            int size = q.size();
            int sum = 0;
            for (int i = 0; i < size; i++) {
                TreeNode node = q.poll();
                sum += node.val;
                TreeNode left = node.left;
                TreeNode right = node.right;
                if (left != null) {
                    q.offer(left);
                }
                if (right != null) {
                    q.offer(right);
                }
            }
            depthSum.put(depth, sum);
        }
        q.offer(root);
        root.val = -root.val; // root没父节点，单独做一次
        depth = -1;
        while (!q.isEmpty()) {
            depth++;
            int size = q.size();
            for (int i = 0; i < size; i++) {
                TreeNode node = q.poll();
                node.val += depthSum.get(depth);
                TreeNode left = node.left;
                TreeNode right = node.right;
                int t = (left == null ? 0 : left.val) + (right == null ? 0 : right.val);
                // 提前让left和right变为他们之和的负值
                if (left != null) {
                    left.val = -t;
                    q.offer(left);
                }
                if (right != null) {
                    right.val = -t;
                    q.offer(right);
                }
            }
        }
        return root;
    }

    // 参考题解的做法，在遍历过程中不是统计本层的sum，而是直接统计下一层的sum，这样就不用两次层序遍历
    public TreeNode replaceValueInTree_implementation2(TreeNode root) {
        Deque<TreeNode> q = new LinkedList<>();
        q.offer(root);
        int depthSum = root.val;
        root.val = -root.val;
        while (!q.isEmpty()) {
            int size = q.size();
            int sum = 0;
            // 一层
            for (int i = 0; i < size; i++) {
                // 归纳假设，现在depthSum已经存好了当前层的和，且当前层的节点已经是-(自己+兄弟)
                TreeNode node = q.poll();
                node.val = node.val + depthSum;
                TreeNode left = node.left;
                TreeNode right = node.right;
                int t = (left == null ? 0 : left.val) + (right == null ? 0 : right.val);
                sum += t;
                if (left != null) {
                    left.val = -t;
                    q.offer(left);
                }
                if (right != null) {
                    right.val = -t;
                    q.offer(right);
                }
            }
            depthSum = sum;
        }
        return root;
    }

    public static void main(String[] args) {
        Solution2641 solu = new Solution2641();
        TreeNode root = new TreeNode(5, new TreeNode(4, new TreeNode(1), new TreeNode(10)), new TreeNode(9, null, new TreeNode(7)));
        solu.replaceValueInTree(root);
        TreeNode root2 = new TreeNode(5, new TreeNode(4, new TreeNode(1), new TreeNode(10)), new TreeNode(9, null, new TreeNode(7)));
        solu.replaceValueInTree_implementation2(root2);
    }
}
