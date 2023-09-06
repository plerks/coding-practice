/*
url: https://leetcode.cn/problems/lowest-common-ancestor-of-deepest-leaves/?envType=daily-question&envId=2023-09-06
LeetCode参考: https://leetcode.cn/problems/lowest-common-ancestor-of-deepest-leaves/solutions/488055/liang-chong-si-lu-yi-chong-qian-xu-bian-li-yi-chon/
              https://leetcode.cn/problems/lowest-common-ancestor-of-deepest-leaves/solutions/267484/dfsjian-dan-jie-ti-si-lu-yi-kan-jiu-dong-by-xiaora/
*/

public class Solution1123 {
    // 找左右子树高度相等的节点
    public TreeNode lcaDeepestLeaves(TreeNode root) {
        if (root == null) return null;
        // 这里求高度反复在读树，可以通过给TreeNode定义depth字段或用HashMap存已经求完的节点高度进行优化
        int leftDepth = getDepth(root.left);
        int rightDepth = getDepth(root.right);
        if (leftDepth == rightDepth) return root;
        // leftDepth > rightDepth，解一定在左子树中
        if (leftDepth > rightDepth) return lcaDeepestLeaves(root.left);
        return lcaDeepestLeaves(root.right);
    }

    private int getDepth(TreeNode root) {
        if (root == null) return 0;
        return Math.max(getDepth(root.left) + 1, getDepth(root.right) + 1);
    }

    TreeNode ans = null;
    int currentMaxDepth = 0;

    public TreeNode lcaDeepestLeaves_implementation2(TreeNode root) {
        dfs(root, 0);
        return ans;
    }

    private int dfs(TreeNode root, int currentDepth) {
        if (root == null) return currentDepth;
        // left表示左子树的节点的最大深度
        int left = dfs(root.left, currentDepth + 1);
        int right = dfs(root.right, currentDepth + 1);
        // 这里必须是left >= currentMaxDepth而非>，因为上面的dfs()可能访问完了叶节点刚更新完currentMaxDepth，这时候父节点要进行更新，否则最终ans是叶节点
        if (left == right && left >= currentMaxDepth) {
            ans = root;
            currentMaxDepth = left;
        }
        return Math.max(left, right);
    }

    public static void main(String[] args) {
    }
}