/*
url: https://leetcode.cn/problems/count-good-nodes-in-binary-tree/
标签: dfs
*/

public class Solution1448 {
    public int ans = 0;

    public int goodNodes(TreeNode root) {
        myGoodNodes(root, root.val);
        return ans;
    }

    public void myGoodNodes(TreeNode root, int currentMax) {
        if (root == null) return;
        if (root.val >= currentMax) {
            ans++;
            currentMax = root.val;
        }
        myGoodNodes(root.left, currentMax);
        myGoodNodes(root.right, currentMax);
    }

    public static void main(String[] args) {
    }
}