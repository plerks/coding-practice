/*
url: https://leetcode.cn/problems/deepest-leaves-sum/
标签: 层序遍历
*/

import java.util.*;

public class Solution1302 {
    public int deepestLeavesSum(TreeNode root) {
        Deque<TreeNode> q = new LinkedList<>();
        q.offer(root);
        int ans = 0;
        while (!q.isEmpty()) {
            int size = q.size();
            boolean hasNextLevel = false;
            for (int i = 0; i < size; i++) {
                TreeNode node = q.poll();
                ans += node.val;
                if (node.left != null) {
                    q.offer(node.left);
                    hasNextLevel = true;
                }
                if (node.right != null) {
                    q.offer(node.right);
                    hasNextLevel = true;
                }
            }
            if (!hasNextLevel) break;
            else ans = 0;
        }
        return ans;
    }

    public static void main(String[] args) {
        
    }
}
