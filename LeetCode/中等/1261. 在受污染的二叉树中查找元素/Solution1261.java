// https://leetcode.cn/problems/find-elements-in-a-contaminated-binary-tree/description/?envType=daily-question&envId=2024-03-12

import java.util.*;

public class Solution1261 {
    Set<Integer> set = new HashSet<>();

    // 粘贴到LeetCode上把这个方法改名为FindElements
    public Solution1261(TreeNode root) {
        root.val = 0;
        set.add(0);
        dfs(root);
    }

    public boolean find(int target) {
        return set.contains(target);
    }

    private void dfs(TreeNode root) {
        if (root == null) return;
        if (root.left != null) {
            root.left.val = 2 * root.val + 1;
            set.add(root.left.val);
        }
        if (root.right != null) {
            root.right.val = 2 * root.val + 2;
            set.add(root.right.val);
        }
        dfs(root.left);
        dfs(root.right);
    }

    public static void main(String[] args) {
    }
}
