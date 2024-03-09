/*
描述: 求图两点之间的所有路径数。
相关: LeetCode1976. 到达目的地的方案数, 典型问题/最短路径问题/最短路径数-Floyd, LeetCode797. 所有可能的路径
*/

public class AllPathCount {
    // 这里graph是按邻接表给出的有向图，若是无向图则转为有向图即可，没考虑图有自环以及两点之间可能有多条边。
    /*
    由`LeetCode1976. 到达目的地的方案数`的Floyd算法解法和`典型问题/最短路径问题/最短路径数-Floyd`想到的，尝试用Floyd算法的思想求解所有路径数。
    结论是不能这样做，但是或许对有向无环图(DAG)，这样的代码能给出所有节点对之间的所有简单路径(或简单回路，对i==j时)数
    */
    // 待做: 搞清楚以下这样写是否能对有向无环图给出所有节点对之间的所有简单路径(或简单回路)数
    public int allPathCount_wrong(int[][] graph) {
        /* int n = graph.length;
        int[][] dis = new int[n][n];
        int[][] count = new int[n][n];
        for (int[] arr : dis) java.util.Arrays.fill(arr, Integer.MAX_VALUE);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < graph[i].length; j++) {
                dis[i][graph[i][j]] = 1; // 不需管距离的具体值，只需区分是否是无穷即可
                count[i][graph[i][j]] = 1;
            }
        }
        for (int i = 0; i < n; i++) {
            dis[i][i] = 0;
            count[i][i] = 0;
        }
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (i != k && j != k) {
                        if (dis[i][k] != Integer.MAX_VALUE && dis[k][j] != Integer.MAX_VALUE) {
                            count[i][j] += count[i][k] * count[k][j];
                            dis[i][j] = 1;
                        }
                    }
                }
            }
        }
        return count[0][n - 1]; */

        // 观察上面代码，实际dis数组完全不需要，只需要count数组即可。

        int n = graph.length;
        int[][] count = new int[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < graph[i].length; j++) {
                count[i][graph[i][j]] = 1;
            }
        }
        for (int i = 0; i < n; i++) {
            count[i][i] = 0;
        }
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (i != k && j != k) { // 对有向无环图，这里是否判断i != k && j != k应该是一样的
                        count[i][j] += count[i][k] * count[k][j];
                    }
                }
            }
        }
        return count[0][n - 1]; // 这里只返回了节点0到节点n-1的
    }

    /*
    1. 把三重循环里if (i != k && j != k)的判断去掉，以上allPathCount_wrong()是否给出了节点之间的所有路径数？
    否，若两个节点i, j之间有环，则i, j之间的路径有无数条，仅凭此可以断定无法给出所有路径数。

    2. 把三重循环里if (i != k && j != k)的判断去掉，allPathCount_wrong()是否给出了节点之间长度(步数)小于等于2n的所有路径数？
    为什么这里会想着2n，因为k == n-1时，上面的代码会考虑路径i ~ n-1 ~ j，这里能考虑出的路径最长为2n，但是，这里i ~ n-1和
    n-1 ~ j的路径只会有[0, n-2]的点，不会有n-1，则上面代码不能给出长度(步数)小于等于2n的所有路径数。

    3. allPathCount_wrong()是否给出了节点之间的所有简单路径(或简单回路，对i==j时)数？
    否，考虑路径i ~ n-1 ~ j时，i ~ n-1和n-1 ~ j中间使用了节点0,...,k-1，但是与Floyd算法求最短路径时不同，这里i ~ n-1和n-1 ~ j
    两段出现同一个节点x的情况是被考虑进去了的，也就是路径i ~ n-1 ~ j中间可以存在回路，不是简单路径。为什么Floyd算法求最短路径时路径i ~ n-1 ~ j
    不会考虑出回路？因为Floyd算法要求图中无负权回路，则若路径i ~ n-1 ~ j存在回路，则将回路去掉路径一定更短，因此最终考虑出的最短路径一定无回路。

    4. 若图是有向无环图，则allPathCount_wrong()是否能给出节点之间的所有简单路径(或简单回路，对i==j时)数？
    我感觉是。若图是有向无环图，则路径i ~ n-1 ~ j中间一定不会考虑进去回路，因为没有回路。这样allPathCount_wrong()相当于给出了
    所有节点对的简单路径(简单回路)数。本来可以通过提交LeetCode797. 所有可能的路径来测的，但是LeetCode797要求返回所有路径，这里只是
    计算出了路径数，所以不能通过提交LeetCode797来测，不确定我想的对不对。
    */

    /* 要求两点之间的所有路径数，应该用图的邻接矩阵的这个结论:
        设A为n阶有向图的邻接矩阵，则:
            A^L中元素a_ij为节点i到节点j长度为L的通路数。(若L取0，则A^0 = 单位矩阵，相当于i不走动到i有一条路径(长度为0))
            B = A + A^2 + A^3 + ... + A^L中元素b_ij为节点i到节点j长度小于等于L的通路数。
    这个结论用矩阵乘法的计算方式可以理解。邻接矩阵的这个结论对图没有限制，可以有自环，两点之间可以有多条边。
    */
    public int allPathCount(int[][] graph) {
        return -1; // 这里没实现，反正按图的邻接矩阵的结论就行
    }

    public static void main(String[] args) {
        AllPathCount apc = new AllPathCount();
        // 用例不足，只有LeetCode797. 所有可能的路径的两个用例和自己编的简单用例
        System.out.println(apc.allPathCount_wrong(new int[][]{{1,2},{3},{3},{}})); // DAG
        System.out.println(apc.allPathCount_wrong(new int[][]{{4,3,1},{3,2,4},{3},{4},{}})); // DAG
        System.out.println(apc.allPathCount_wrong(new int[][]{{1,2},{0,2},{0,1}})); // 3个节点的有向完全图
    }
}
