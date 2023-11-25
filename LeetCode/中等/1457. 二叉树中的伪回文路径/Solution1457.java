/*
url: https://leetcode.cn/problems/pseudo-palindromic-paths-in-a-binary-tree/?envType=daily-question&envId=2023-11-25
LeetCode参考: https://leetcode.cn/problems/pseudo-palindromic-paths-in-a-binary-tree/solutions/259339/java-dfs-shuang-bai-by-rational-irrationality/
标签: dfs, x & (x - 1)的性质, 位运算, 序列能否排列成回文
*/

public class Solution1457 {
    int ans = 0;

    public int pseudoPalindromicPaths (TreeNode root) {
        dfs(root, 0);
        return ans;
    }

    // 主要问题在于序列是否能排列成回文，需要序列每个字符出现偶数次，或者一个出现奇数次，其它全出现偶数次
    private void dfs(TreeNode root, int temp) {
        if (root == null) return;
        temp = temp ^ (1 << root.val); // root.val只会出现1-9，用位来记录出现每个数出现偶数还是奇数次
        if (root.left == null && root.right == null) {
            // 若temp == 0，说明路径中每个数出现偶数次，可以排成回文
            // 若(temp & (temp - 1)) == 0，说明temp为一个只有一位为1的数，说明路径有一个数出现奇数次，其它都出现偶数次，可以排成回文
            // temp - 1相比temp是把temp的最后一位1变为0，然后右边全为1，高位相同
            if (temp == 0 || (temp & (temp - 1)) == 0) {
                ans++;
                return;
            }
        }
        dfs(root.left, temp);
        dfs(root.right, temp);
    }

    public static void main(String[] args) {
    }
}
