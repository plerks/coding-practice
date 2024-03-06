/*
描述: 使用优先队列实现Dijkstra算法
相关: LeetCode1976. 到达目的地的方案数
*/

import java.util.*;

public class ShortestPathDijkstraPriorityQueue {
    public int[] shortestPath(int n, int[][] edges, int s) {
        List<List<int[]>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            graph.get(edge[0]).add(new int[]{edge[1], edge[2]});
            graph.get(edge[1]).add(new int[]{edge[0], edge[2]});
        }
        int[] dis = new int[n]; // 记录0到i的最短距离
        Arrays.fill(dis, Integer.MAX_VALUE);
        dis[s] = 0;
        // 这里的int[]记录[节点, 最短距离]
        PriorityQueue<int[]> q = new PriorityQueue<>((x, y) -> {
            return x[1] < y[1] ? -1 : 1;
        });
        q.offer(new int[]{s, 0});
        while (!q.isEmpty()) {
            int[] arr = q.poll();
            int node = arr[0];
            int distance = arr[1];
            /* 这行continue不要也能正确，若distance > dis[node]，说明q中前面已有distance更小的[node, distance]，q中的这个arr
            不需要使用进行计算。[oi wiki](https://oi-wiki.org/graph/shortest-path/#%E5%AE%9E%E7%8E%B0_2)上是用了个visited数组，这里是if (vis[u]) continue;
            */
            if (distance > dis[node]) continue;
            for (int[] neighbor : graph.get(node)) {
                int next = neighbor[0];
                int w = neighbor[1];
                if (distance + w < dis[next]) {
                    dis[next] = distance + w;
                    q.offer(new int[]{next, dis[next]});
                }
            }
        }
        return dis;
    }

    public static void main(String[] args) {
        ShortestPathDijkstraPriorityQueue spdpq = new ShortestPathDijkstraPriorityQueue();
        int s = 0;
        System.out.println("源节点" + s + "到其它节点的最短距离分别为: " + Arrays.toString(spdpq.shortestPath(7, new int[][]{{0,6,7},{0,1,2},{1,2,3},{1,3,3},{6,3,3},{3,5,1},{6,5,1},{2,5,1},{0,4,5},{4,6,2}}, s)));
    }
}
