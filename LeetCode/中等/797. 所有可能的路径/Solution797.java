/*
url: https://leetcode.cn/problems/all-paths-from-source-to-target/description/
LeetCode参考: https://leetcode.cn/problems/all-paths-from-source-to-target/solutions/956408/suo-you-ke-neng-de-lu-jing-by-leetcode-s-iyoh/
相关: LeetCode1976. 到达目的地的方案数
*/


import java.util.*;

public class Solution797 {
    int n;
    List<List<Integer>> ans;

    public List<List<Integer>> allPathsSourceTarget(int[][] graph) {
        n = graph.length;
        ans = new ArrayList<>();
        boolean[] visited = new boolean[n];
        dfs(0, graph, visited, new ArrayList<>());
        return ans;
    }

    private void dfs(int root, int[][] graph, boolean[] visited, List<Integer> path) {
        if (!visited[root]) {
            visited[root] = true;
            path.add(root);
            if (root == n - 1) {
                ans.add(new ArrayList<>(path));
                visited[root] = false;
                path.remove(path.size() - 1);
                return;
            }
            for (int neighbor : graph[root]) {
                dfs(neighbor, graph, visited, path);
            }
            // 为了后续还可以通过其它路径到这个点
            visited[root] = false;
            path.remove(path.size() - 1);
        }
    }

    // 参考官方题解，因为本题中的图为有向无环图（DAG），搜索过程中不会反复遍历同一个点，因此我们无需判断当前点是否遍历过。
    public List<List<Integer>> allPathsSourceTarget_implementation2(int[][] graph) {
        n = graph.length;
        ans = new ArrayList<>();
        dfs2(0, graph, new ArrayList<>());
        return ans;
    }

    private void dfs2(int root, int[][] graph, List<Integer> path) {
        path.add(root);
        if (root == n - 1) {
            ans.add(new ArrayList<>(path));
            path.remove(path.size() - 1);
            return;
        }
        for (int neighbor : graph[root]) {
            dfs2(neighbor, graph, path);
        }
        path.remove(path.size() - 1);
    }

    public static void main(String[] args) {
        Solution797 solu = new Solution797();
        System.out.println(solu.allPathsSourceTarget(new int[][]{{1,2},{3},{3},{}}));
        Solution797 solu2 = new Solution797();
        System.out.println(solu2.allPathsSourceTarget_implementation2(new int[][]{{1,2},{3},{3},{}}));
    }
}
