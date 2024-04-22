/*
描述: Dijkstra算法解决单源最短路径问题，算法要求所有边的权重都为非负值。(可以有环。Dijkstra算法要求边权重非负的原因在于:
      算法每次选出当前V-S集合中s离其距离最近的节点，然后对这个节点的邻居做松弛操作，选出的这个节点会加入S集合，若所有边权重非负，则能
      保证对S中的所有节点，s到其的最短距离已经找到，这保证了算法的正确性。若边权重可以为负，则本身可能可以通过某条负权边使s到某个
      点的距离更小，但是这个点早已在S集合中，也就意味着之前确信的最短距离并非最短，算法结果也就不正确)
参考: https://oi-wiki.org/graph/shortest-path/#%E5%AE%9E%E7%8E%B0_2
相关: LeetCode1976. 到达目的地的方案数
*/

import java.util.*;

/* 参考[oi wiki]<https://oi-wiki.org/graph/shortest-path/#%E6%97%B6%E9%97%B4%E5%A4%8D%E6%9D%82%E5%BA%A6>
n为节点数，e为边数，暴力法实现的Dijkstra算法时间复杂度为O(n^2)，使用优先队列实现的Dijkstra算法时间复杂度为O(nloge + eloge)。
因此优先队列实现的Dijkstra算法适用于稀疏图，暴力法实现的Dijkstra算法适用于稠密图。
*/
public class ShortestPathDijkstra {
    public int[] shortestPath(int n, int[][] graph, int s) { // 求s到其它点的最短路径
        int[] distance = new int[n];
        Arrays.fill(distance, Integer.MAX_VALUE);
        distance[s] = 0;
        boolean[] discovered = new boolean[n];
        Arrays.fill(discovered, false);
        int[] parent = new int[n]; // 记录最短路径
        for (int i = 0; i < parent.length; i++) {
            parent[i] = i;
        }
        int discoveredNodeCount = 0;
        while (discoveredNodeCount < n) { // 这里也可以直接写for (int cnt = 0; cnt < n; cnt++)
            // 找优先级最高的未发现节点，这个每次找最高优先级节点的过程可以优化
            int node = -1, min = Integer.MAX_VALUE;
            for (int i = 0; i < distance.length; i++) {
                if (!discovered[i]) {
                    if (distance[i] < min) {
                        node = i;
                        min = distance[i];
                    }
                }
            }
            for (int j = 0; j < graph[node].length; j++) { // 用node相关的边做松弛操作
                if (graph[node][j] != Integer.MAX_VALUE) {
                    if (distance[node] + graph[node][j] < distance[j]) {
                        distance[j] = distance[node] + graph[node][j];
                        parent[j] = node;
                    }
                }
            }
            discovered[node] = true;
            discoveredNodeCount++;
        }
        // 最短路径可由parent反向推导出
        System.out.print("最短路径可由parent反向推导出，以s到节点4为例: " + getPath(parent, s, 4));
        return distance;
    }

    public String getPath(int[] parent, int s, int d) {
        StringBuilder sb = new StringBuilder();
        List<Integer> list = new ArrayList<>();
        while (parent[d] != d) {
            list.add(d);
            d = parent[d];
        }
        list.add(d);
        Collections.reverse(list);
        for (int i = 0; i < list.size(); i++) {
            if (i != list.size() - 1) {
                sb.append(list.get(i) + " -> ");
            }
            else sb.append(list.get(i) + "\n");
        }
        return sb.toString();
    }

    public static void main(String[] args) {
        ShortestPathDijkstra solu = new ShortestPathDijkstra();
        int n = 5;
        int[][] graph = new int[n][n];
        for (int[] arr : graph) {
            Arrays.fill(arr, Integer.MAX_VALUE);
        }
        graph[0][1] = 4;
        graph[0][3] = 2;
        graph[1][2] = 4;
        graph[1][3] = 1;
        graph[2][3] = 1;
        graph[2][4] = 3;
        graph[3][4] = 7;
        graph[1][0] = 4;
        graph[3][0] = 2;
        graph[2][1] = 4;
        graph[3][1] = 1;
        graph[3][2] = 1;
        graph[4][2] = 3;
        graph[4][3] = 7;
        int s = 0; // 源节点
        System.out.println("源节点" + s + "到其它节点的最短距离分别为: "+ Arrays.toString(solu.shortestPath(n, graph, s)));
    }
}