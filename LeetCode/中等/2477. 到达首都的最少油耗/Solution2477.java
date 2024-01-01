/*
url: https://leetcode.cn/problems/minimum-fuel-cost-to-report-to-the-capital/
LeetCode参考: https://leetcode.cn/problems/minimum-fuel-cost-to-report-to-the-capital/solutions/2553190/dao-da-shou-du-de-zui-shao-you-hao-by-le-v013/
标签: dfs
*/

import java.util.ArrayList;
import java.util.List;

public class Solution2477 {
    private long ans = 0;

    public long minimumFuelCost(int[][] roads, int seats) {
        if (roads.length == 0) return 0;
        List<List<Integer>> graph = new ArrayList<>();
        int n = roads.length + 1;
        for (int i = 0; i < n; i++) graph.add(new ArrayList<>());
        for (int[] road : roads) {
            graph.get(road[0]).add(road[1]);
            graph.get(road[1]).add(road[0]);
        }
        boolean[] visited = new boolean[n];
        dfs(0, graph, seats, visited);
        return ans;
    }

    /* 按dfs的树边关系，节点存在父子关系，例如子节点有2 * seats个人，则要用2俩车，用2个单位的油到父节点，所有子节点的人集合到父节点后，
    再针对集合在父节点的人，考虑这些人要用多少辆车到父节点的父节点，题目不考虑车辆数，只需集合考虑油耗 */
    private int dfs(int node, List<List<Integer>> graph, int seats, boolean[] visited) {
        visited[node] = true;
        int num = 0;
        for (int neighbor : graph.get(node)) {
            if (!visited[neighbor]) {
                int subNum = dfs(neighbor, graph, seats, visited);
                ans += (subNum + seats - 1) / seats;
                num += subNum;
                visited[neighbor] = true;
            }
        }
        return 1 + num;
    }

    public static void main(String[] args) {
        Solution2477 solu = new Solution2477();
        System.out.println(solu.minimumFuelCost(new int[][]{{3,1},{3,2},{1,0},{0,4},{0,5},{4,6}}, 2));
    }
}
