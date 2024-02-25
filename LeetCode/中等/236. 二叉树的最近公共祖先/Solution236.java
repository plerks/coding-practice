/*
url: https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/
LeetCode参考: https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/solutions/238552/er-cha-shu-de-zui-jin-gong-gong-zu-xian-by-leetc-2/
相关: LeetCode2846. 边权重均等查询, LeetCode235. 二叉搜索树的最近公共祖先
标签: 最近公共祖先
*/

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;

public class Solution236 {
    public TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {
        HashMap<TreeNode, TreeNode> map = new HashMap<>(); // LeetCode的TreeNode无parent指针，dfs一遍记录每个节点的parent
        dfs(root, map);
        HashSet<TreeNode> set = new HashSet<>();
        TreeNode node = p;
        while (node != null) {
            set.add(node);
            node = map.get(node);
        }
        node = q;
        while (node != null) {
            if (set.contains(node)) return node;
            node = map.get(node);
        }
        return null;
    }

    public void dfs(TreeNode root, Map<TreeNode, TreeNode> map) {
        if (root.left != null) {
            map.put(root.left, root);
            dfs(root.left, map);
        }
        if (root.right != null) {
            map.put(root.right, root);
            dfs(root.right, map);
        }
    }

    TreeNode ans;

    // 递归做
    public TreeNode lowestCommonAncestor_implementation2(TreeNode root, TreeNode p, TreeNode q) {
        dfs(root, p, q);
        return ans;
    }

    public boolean dfs(TreeNode root, TreeNode p, TreeNode q) { // root子树是否包含p或q
        if (root == null) return false;
        boolean b1 = dfs(root.left, p, q);
        boolean b2 = dfs(root.right, p, q);
        // 注意只有p, q的最近公共祖先才能满足这两种条件，最近公共祖先的祖先不会
        if (root == p || root == q) {
            if (b1 || b2) {
                ans = root;
                return true;
            }
        }
        else {
            if (b1 && b2) {
                ans = root;
                return true;
            }
        }
        return b1 || b2 || root == p || root == q;
    }

    public static void main(String[] args) {
        Solution236 solu = new Solution236();
        TreeNode node0 = new TreeNode(0);
        TreeNode node1 = new TreeNode(1);
        TreeNode node2 = new TreeNode(2);
        TreeNode node3 = new TreeNode(3);
        node0.left = node1;
        node1.left = node2;
        node1.right = node3;
        System.out.println(solu.lowestCommonAncestor_implementation2(node0, node2, node3).val);
    }
}
