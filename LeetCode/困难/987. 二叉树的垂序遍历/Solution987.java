/*
url: https://leetcode.cn/problems/vertical-order-traversal-of-a-binary-tree/description/?envType=daily-question&envId=2024-02-13
标签: TreeMap, 二叉树特殊遍历, 垂序遍历, dfs, 多级条件排序
*/

import java.util.*;

public class Solution987 {
    public List<List<Integer>> verticalTraversal(TreeNode root) {
        TreeMap<Integer, List<int[]>> map = new TreeMap<>();
        dfs(root, 0, 0, map);
        List<List<Integer>> ans = new ArrayList<>();
        while (!map.isEmpty()) {
            List<int[]> nodes = map.pollFirstEntry().getValue();
            Collections.sort(nodes, (x, y) -> {
                if (x[1] == y[1]) return x[0] - y[0];
                return x[1] - y[1];
            });
            List<Integer> list = new ArrayList<>();
            for (int i = 0; i < nodes.size(); i++) {
                list.add(nodes.get(i)[0]);
            }
            ans.add(list);
        }
        return ans;
    }

    private void dfs(TreeNode root, int i, int j, TreeMap<Integer, List<int[]>> map) {
        if (root == null) return;
        List<int[]> list;
        if (!map.containsKey(j)) {
            list = new ArrayList<>();
            map.put(j, list);
        }
        else list = map.get(j);
        list.add(new int[]{root.val, i, j});
        dfs(root.left, i + 1, j - 1, map);
        dfs(root.right, i + 1, j + 1, map);
    }

    public static void main(String[] args) {
        Solution987 solu = new Solution987();
        System.out.println(solu.verticalTraversal(new TreeNode(3, new TreeNode(9), new TreeNode(20, new TreeNode(15), new TreeNode(7)))));
    }
}
