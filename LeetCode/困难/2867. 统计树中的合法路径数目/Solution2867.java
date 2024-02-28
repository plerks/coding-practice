/*
url: https://leetcode.cn/problems/count-valid-paths-in-a-tree/description/?envType=daily-question&envId=2024-02-27
LeetCode参考: https://leetcode.cn/problems/count-valid-paths-in-a-tree/solutions/2654126/tong-ji-shu-zhong-de-he-fa-lu-jing-shu-m-yyuw/
相关: 典型问题/筛法, LeetCode1390. 四因数, LeetCode2846. 边权重均等查询
标签: 数论, 埃拉托斯特尼筛法, 欧拉筛法, 最近公共祖先, 树中节点路径, 并查集
*/

import java.util.*;

public class Solution2867 {
    // 我的解法，757 / 922 个通过的测试用例，超时
    public long countPaths(int n, int[][] edges) {
        // 选1号节点作为根，然后通过dfs找出父子关系，从而可以找出最近公共祖先，通过最近公共祖先即可找到路径，这里找路径和LeetCode2846. 边权重均等查询相似
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i <= n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            graph.get(edge[0]).add(edge[1]);
            graph.get(edge[1]).add(edge[0]);
        }
        Set<Integer> primes = new HashSet<>();
        boolean[] isPrime = new boolean[n + 1]; // 用筛法求0-n的素数
        Arrays.fill(isPrime, true);
        isPrime[0] = isPrime[1] = false;
        // 埃拉托斯特尼筛法
        for (int i = 2; i <= n; i++) {
            if (isPrime[i]) {
                primes.add(i);
            }
            if ((long)i * i > n) continue;
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
        // 选1号节点作为根
        int[] parent = new int[n + 1];
        parent[1] = -1;
        int[] depth = new int[n + 1];
        boolean[] visited = new boolean[n + 1];
        dfs(1, graph, parent, depth, visited);
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                if (isLegalPath(i, j, parent, depth, primes)) {
                    ans++;
                }
            }
        }
        return ans;
    }

    private boolean isLegalPath(int i, int j, int[] parent, int[] depth, Set<Integer> primes) {
        int primeCount = 0;
        if (depth[i] > depth[j]) {
            int temp = i;
            i = j;
            j = temp;
        }
        while (depth[j] > depth[i]) {
            if (primes.contains(j)) primeCount++;
            j = parent[j];
        }
        while (i != j) {
            if (primes.contains(i)) primeCount++;
            if (primes.contains(j)) primeCount++;
            i = parent[i];
            j = parent[j];
        }
        if (primes.contains(i)) primeCount++; // 这时候i == j为最近公共祖先
        return primeCount == 1;
    }

    private void dfs(int root, List<List<Integer>> graph, int[] parent, int[] depth, boolean[] visited) {
        if (!visited[root]) {
            visited[root] = true;
            for (int child : graph.get(root)) {
                if (!visited[child]) {
                    parent[child] = root;
                    depth[child] = depth[root] + 1;
                    dfs(child, graph, parent, depth, visited);
                    visited[child] = true;
                }
            }
        }
    }

    /* 官方题解的解法，我的解法超时之后我有考虑可能要从每个素数编号节点去dfs，但是没想清楚记录子树个数和节点数量怎么简单，以及从多个素数编号
    起点去dfs有没有可能有重复计数的问题(实际不会，因为每次都只会有那么一个素数节点) */
    public long countPaths_implementation2(int n, int[][] edges) {
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i <= n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            graph.get(edge[0]).add(edge[1]);
            graph.get(edge[1]).add(edge[0]);
        }
        Set<Integer> primes = new HashSet<>();
        boolean[] isPrime = new boolean[n + 1]; // 用筛法求0-n的素数
        Arrays.fill(isPrime, true);
        isPrime[0] = isPrime[1] = false;
        // 埃拉托斯特尼筛法
        for (int i = 2; i <= n; i++) {
            if (isPrime[i]) {
                primes.add(i);
            }
            if ((long)i * i > n) continue;
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
        List<Integer> seen = new ArrayList<>();
        long ans = 0;
        int[] count = new int[n + 1]; // count[i]记录了i号节点不包含素数的连通分量的节点数目
        for (int i = 1; i <= n; i++) {
            if (!isPrime[i]) continue;
            int current = 0; // 这里有技巧，并没有去记录有多少个不含素数的连通分量及大小，而是通过current记录当前查到的连通分量节点数之和
            for (int neighbor : graph.get(i)) {
                if (isPrime[neighbor]) continue;
                if (count[neighbor] == 0) {
                    seen.clear();
                    // 这里有dfs防返回的技巧，graph是树结构，只需用一个pre指示上一层就可以防止dfs时从neighbor返回去访问root，通用的办法应该是把seen改成Set<Integer> visited
                    // 这里dfs2()是在反复读树的，应该可以用并查集提前把不含素数的连通分量及大小求出来，防止反复dfs
                    dfs2(graph, seen, neighbor, i, isPrime);
                    for (int node : seen) {
                        count[node] = seen.size();
                    }
                }
                ans += current * count[neighbor]; // 从不含素数的子连通分量经过i到另一个不含素数的子连通分量的合法路径数
                current += count[neighbor];
            }
            ans += current; // 这里是加上从子节点到i的合法路径
        }
        return ans;
    }

    private void dfs2(List<List<Integer>> graph, List<Integer> seen, int root, int pre, boolean[] isPrime) {
        seen.add(root);
        for (int neighbor : graph.get(root)) {
            if (!isPrime[neighbor] && neighbor != pre) { // neighbor != pre防返回
                dfs2(graph, seen, neighbor, root, isPrime);
            }
        }
    }

    static int N = 100000;
    static Set<Integer> primes = new HashSet<>();
    static boolean[] isPrime = new boolean[N + 1]; // 用筛法求0-n的素数
    static {
        Arrays.fill(isPrime, true);
        isPrime[0] = isPrime[1] = false;
        // 埃拉托斯特尼筛法
        for (int i = 2; i <= N; i++) {
            if (isPrime[i]) {
                primes.add(i);
            }
            if ((long)i * i > N) continue;
            for (int j = i * i; j <= N; j += i) {
                isPrime[j] = false;
            }
        }
    }

    /* 用static块尝试优化countPaths_implementation2()对每个用例都要计算isPrime的问题，但是和LeetCode1390. 四因数sumFourDivisors_implementation4()一样
    没起效果，countPaths_implementation2()LeetCode运行用时39ms，countPaths_implementation3()LeetCode运行用时72ms，奇怪。不过这里对每个用例只需要筛n范围
    的，LeetCode1390. 四因数那里是对每个用例都要筛100000范围的 */
    public long countPaths_implementation3(int n, int[][] edges) {
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i <= n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            graph.get(edge[0]).add(edge[1]);
            graph.get(edge[1]).add(edge[0]);
        }
        List<Integer> seen = new ArrayList<>();
        long ans = 0;
        int[] count = new int[n + 1];
        for (int i = 1; i <= n; i++) {
            if (!isPrime[i]) continue;
            int current = 0;
            for (int neighbor : graph.get(i)) {
                if (isPrime[neighbor]) continue;
                if (count[neighbor] == 0) {
                    seen.clear();
                    dfs2(graph, seen, neighbor, i, isPrime);
                    for (int node : seen) {
                        count[node] = seen.size();
                    }
                }
                ans += current * count[neighbor];
                current += count[neighbor];
            }
            ans += current;
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution2867 solu = new Solution2867();
        System.out.println(solu.countPaths(5, new int[][]{{1,2},{1,3},{2,4},{2,5}}));
        System.out.println(solu.countPaths_implementation2(5, new int[][]{{1,2},{1,3},{2,4},{2,5}}));
        System.out.println(solu.countPaths_implementation3(5, new int[][]{{1,2},{1,3},{2,4},{2,5}}));
    }
}
