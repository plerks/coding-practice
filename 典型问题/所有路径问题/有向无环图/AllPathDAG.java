/*
描述: 求出有向无环图(DAG)中从节点0到节点n-1的所有路径，即题目LeetCode797. 所有可能的路径
相关: LeetCode797. 所有可能的路径, LeetCode1976. 到达目的地的方案数
*/

import java.util.*;

public class AllPathDAG {
    int n;
    List<List<Integer>> ans;

    /* 以下代码要求图是有向无环图，若图不是有向无环图，则见LeetCode1976. 到达目的地的方案数 countPaths_wrong()，这样写会有问题
    */
    // 参考LeetCode797. 所有可能的路径的官方题解，因为本题中的图为有向无环图（DAG），搜索过程中不会反复遍历同一个点，因此我们无需判断当前点是否遍历过。
    public List<List<Integer>> allPathsSourceTarget(int[][] graph) {
        n = graph.length;
        ans = new ArrayList<>();
        dfs(0, graph, new ArrayList<>());
        return ans;
    }

    private void dfs(int root, int[][] graph, List<Integer> path) {
        path.add(root);
        if (root == n - 1) {
            ans.add(new ArrayList<>(path));
            path.remove(path.size() - 1);
            return;
        }
        for (int neighbor : graph[root]) {
            dfs(neighbor, graph, path);
        }
        path.remove(path.size() - 1);
    }
    public static void main(String[] args) {
        AllPathDAG allPathDAG = new AllPathDAG();
        System.out.println(allPathDAG.allPathsSourceTarget(new int[][]{{1,2},{3},{3},{}}));
    }
}
