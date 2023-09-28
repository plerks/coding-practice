import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public class ShortestPath {
    public int[] shortestPath(int n, int[][] graph, int s) { // 求s到其它点的最短路径
        int[] distance = new int[n];
        Arrays.fill(distance, Integer.MAX_VALUE);
        boolean[] discovered = new boolean[n];
        Arrays.fill(discovered, false);
        distance[s] = 0;
        int discoveredNodeCount = 0;
        int[] parent = new int[n]; // 记录最短路径
        for (int i = 0; i < parent.length; i++) {
            parent[i] = i;
        }
        while (discoveredNodeCount < n) {
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
        ShortestPath solu = new ShortestPath();
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