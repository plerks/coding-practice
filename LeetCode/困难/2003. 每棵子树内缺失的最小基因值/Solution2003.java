/*
url: https://leetcode.cn/problems/smallest-missing-genetic-value-in-each-subtree/?envType=daily-question&envId=2023-10-31
LeetCode参考: https://leetcode.cn/problems/smallest-missing-genetic-value-in-each-subtree/solutions/2490449/mei-ke-zi-shu-nei-que-shi-de-zui-xiao-ji-mljk/
相关: LeetCode41. 缺失的第一个正数
标签: dfs, 从下往上, 自下而上
*/

import java.util.*;

public class Solution2003 {
    public int[] smallestMissingValueSubtree(int[] parents, int[] nums) {
        /* 各个节点的基因值各不相同，因此基因值为1的节点最多一个。
        若子树T(x)包含基因值为1的节点，则其为基因值1节点的祖先，需要知道T(x)的元素构成，若T(x)不包含，则其缺失的最小基因值一定为1。
        因此，只需从可能存在的最多一个基因值为1的节点从下往上进行判断，其它的节点缺失的最小基因值一定为1。
        即：只有从基因值为1的节点往根的线路是特别的，自顶向下的话不适合找出这条线路，也不适合在遍历这条线路时维护子树的所有值的集合，这是从下往上进行的原因 */
        int n = parents.length;
        int[] ans = new int[n];
        Arrays.fill(ans, 1);
        int gene1Node = -1; // 基因值为1的节点编号(可能不存在)
        for (int i = 0; i < n; i++) {
            if (nums[i] == 1) {
                gene1Node = i;
                break;
            }
        }
        HashSet<Integer> set = new HashSet<>(); // 只需要一个set，不需要多个，因为是在从基因值为1的节点往根走，子树T(x)是一层层包含的
        boolean[] visited = new boolean[n];
        List<List<Integer>> children = new ArrayList<>(); // 用于dfs
        for (int i = 0; i < n; i++) {
            children.add(new ArrayList<>());
        }
        for (int i = 0; i < n; i++) {
            if (parents[i] == -1) continue;
            children.get(parents[i]).add(i);
        }
        if (gene1Node != -1) { // 基因值为1的节点存在
            int node = gene1Node;
            int geneValue = 1; // 一棵树的缺失最小基因值一定>=其子树的，因此不必每次重新开始
            while (node != -1) {
                dfs(node, visited, children, set, nums); // 求子树T的所有值，放入set
                while (set.contains(geneValue)) {
                    geneValue++;
                }
                ans[node] = geneValue;
                node = parents[node];
            }
        }
        return ans;
    }

    private void dfs(int node, boolean[] visited, List<List<Integer>> children, HashSet<Integer> set, int[] nums) {
        if (visited[node]) return;
        visited[node] = true;
        set.add(nums[node]);
        for (int child : children.get(node)) {
            dfs(child, visited, children, set, nums);
        }
    }

    public static void main(String[] args) {
        Solution2003 solu = new Solution2003();
        System.out.println(Arrays.toString(solu.smallestMissingValueSubtree(new int[]{-1,0,0,2}, new int[]{1,2,3,4})));
    }
}
