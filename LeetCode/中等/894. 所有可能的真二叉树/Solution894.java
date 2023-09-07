// https://leetcode.cn/problems/all-possible-full-binary-trees/

import java.util.*;

public class Solution894 {
    public List<TreeNode> allPossibleFBT(int n) {
        List<List<TreeNode>> dp = new ArrayList<>();
        dp.add(new ArrayList<>());
        List<TreeNode> FBT1 = new ArrayList<>();
        FBT1.add(new TreeNode());
        dp.add(FBT1);
        for (int i = 2; i <= n; i++) {
            List<TreeNode> list = new ArrayList<>();
            for (int j = 1; j < i; j++) {
                List<TreeNode> list1 = dp.get(j);
                List<TreeNode> list2 = dp.get(i - j - 1);
                for (TreeNode left : list1) {
                    for (TreeNode right : list2) {
                        TreeNode root = new TreeNode();
                        root.left = left;
                        root.right = right;
                        list.add(root);
                    }
                }
            }
            dp.add(list);
        }
        return dp.get(n);
    }

    public static void main(String[] args) {
    }
}