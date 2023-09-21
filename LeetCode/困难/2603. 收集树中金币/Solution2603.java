/*
url: https://leetcode.cn/problems/collect-coins-in-a-tree/?envType=daily-question&envId=2023-09-21
LeetCode参考: https://leetcode.cn/problems/collect-coins-in-a-tree/solutions/2191371/tuo-bu-pai-xu-ji-lu-ru-dui-shi-jian-pyth-6uli/
标签: 类拓扑排序
*/

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

public class Solution2603 {
    public int collectTheCoins(int[] coins, int[][] edges) {
        int n = coins.length;
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        // 建图
        int[] degrees = new int[n];
        for (int[] arr : edges) {
            degrees[arr[0]]++;
            degrees[arr[1]]++;
            graph.get(arr[0]).add(arr[1]);
            graph.get(arr[1]).add(arr[0]);
        }
        // 去除所有没有金币的叶子
        int edgeCount = n - 1; // 初始边数
        Queue<Integer> q = new LinkedList<>();
        for (int i = 0; i < degrees.length; i++) {
            if (degrees[i] == 1 && coins[i] == 0) {
                q.offer(i);
            }
        }
        while (!q.isEmpty()) {
            int node = q.poll();
            edgeCount--;
            for (int y : graph.get(node)) {
                degrees[y]--;
                if (degrees[y] == 1 && coins[y] == 0) { // 和有向无环图的拓扑排序不同，这里不一定总能续上一个无金币的叶节点
                    q.offer(y);
                }
            }
        }

        // 现在所有叶节点都有金币，要把这些叶节点及其父节点删除，剩下的节点为必须走过的节点
        for (int i = 0; i < degrees.length; i++) {
            if (degrees[i] == 1 && coins[i] == 1) { // 所有有金币的叶节点
                q.offer(i);
            }
        }
        // 删除这些叶子
        edgeCount -= q.size();
        // 删除这些叶子的父节点
        for (int x : q) {
            for (int y : graph.get(x)) {
                degrees[y]--;
                if (degrees[y] == 1) { // 如果这个父节点成为了叶子，则其不需要访问
                    edgeCount--;
                }
            }
        }
        return Math.max(edgeCount * 2, 0);
    }

    public static void main(String[] args) {
        Solution2603 solu = new Solution2603();
        System.out.println(solu.solve());
    }
}