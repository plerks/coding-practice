/*
url: https://leetcode.cn/problems/kth-largest-sum-in-a-binary-tree/description/?envType=daily-question&envId=2024-02-23
标签: 层序遍历, 层序遍历区分层节点, k选取
相关: 典型问题/k选取
*/

import java.util.*;

public class Solution2583 {
    public long kthLargestLevelSum(TreeNode root, int k) {
        PriorityQueue<Long> pq = new PriorityQueue<>(); // 小顶堆
        Deque<TreeNode> q = new LinkedList<>();
        q.offer(root);
        while (!q.isEmpty()) {
            int n = q.size();
            long sum = 0;
            for (int i = 0; i < n; i++) {
                TreeNode node = q.poll();
                sum += node.val;
                if (node.left != null) q.offer(node.left);
                if (node.right != null) q.offer(node.right);
            }
            if (pq.size() < k) pq.offer(sum);
            else if (pq.peek() < sum) {
                pq.poll();
                pq.offer(sum);
            }
        }
        return pq.size() >= k ? pq.peek() : -1;
    }

    public static void main(String[] args) {
        Solution2583 solu = new Solution2583();
        System.out.println(solu.kthLargestLevelSum(new TreeNode(5, new TreeNode(8), new TreeNode(9)), 1));
    }
}
