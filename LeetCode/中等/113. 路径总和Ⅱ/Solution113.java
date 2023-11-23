/*
url: https://leetcode.cn/problems/path-sum-ii/
相关: LeetCode112. 路径总和
标签: dfs
*/

import java.util.ArrayList;
import java.util.Deque;
import java.util.LinkedList;
import java.util.List;

public class Solution113 {
	Deque<Integer> stack = new LinkedList<>();
    
    List<List<Integer>> res = new ArrayList<>();
	
	public static void main(String[] args) {

	}

    public List<List<Integer>> pathSum(TreeNode root, int targetSum) {
        dfs(root, targetSum, 0);
        return res;
    }

    public void dfs(TreeNode root, int targetSum, int currentSum) {
        if (root == null) {
            return;
        }
        else {
            stack.addLast(root.val); // 用push()和pop()最后结果的方向会是反的
            if (root.left == null && root.right == null && currentSum + root.val == targetSum) {
                res.add(new ArrayList<>(stack));
            }
            else {
                dfs(root.left, targetSum, currentSum + root.val);
                dfs(root.right, targetSum, currentSum + root.val);
            }
        }
        stack.removeLast();
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
