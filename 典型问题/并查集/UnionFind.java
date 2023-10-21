/* 并查集，在`LeetCode2316. 统计无向图中无法互相到达点对数`中第一次上手用。
参考: https://leetcode.cn/problems/count-unreachable-pairs-of-nodes-in-an-undirected-graph/solutions/1624997/by-lfool-6rtm/
      https://leetcode.cn/problems/count-unreachable-pairs-of-nodes-in-an-undirected-graph/solutions/2487673/tong-ji-wu-xiang-tu-zhong-wu-fa-hu-xiang-q5eh/
      https://zhuanlan.zhihu.com/p/93647900
*/

import java.util.Arrays;

class UnionFind {
    private int[] parents;

    // 连续只调用union时，不会触发路径压缩，只用调用find()会触发路径压缩。size[i]表示以i为root的子树的规模，用于在union时控制树高，要把小树加入到大树中
    private int[] sizes;

    public UnionFind(int n) {
        this.parents = new int[n];
        for (int i = 0; i < n; i++) {
            parents[i] = i;
        }
        this.sizes = new int[n];
        Arrays.fill(sizes, 1);
    }

    public void union(int x, int y) {
        int rx = find(x);
        int ry = find(y);
        if (rx == ry) return; // x, y已经相连
        if (sizes[rx] < sizes[ry]) {
            parents[rx] = ry;
            sizes[ry] += sizes[rx];
        }
        else {
            parents[ry] = rx;
            sizes[rx] += sizes[ry];
        }
    }

    public int find(int x) {
        if (parents[x] != x) {
            parents[x] = find(parents[x]); // 在find()时进行路径压缩，让中间节点直接记录根
        }
        return parents[x];
    }

    public int getSize(int x) {
        return sizes[x];
    }
}

/* https://leetcode.cn/problems/count-unreachable-pairs-of-nodes-in-an-undirected-graph/solutions/1624997/by-lfool-6rtm/中，并查集还可提供
connected(int p, int q)和count()接口，分别返回p, q是否连通和图中的连通分量数。不过connected()和count()用基础的UnionFind也能实现。
*/
class UnionFindMoreApi {
    private int[] parents;

    // 连续只调用union时，不会触发路径压缩，只用调用find()会触发路径压缩。size[i]表示以i为root的子树的规模，用于在union时控制树高，要把小树加入到大树中
    private int[] sizes;

    private int count;

    public UnionFindMoreApi(int n) {
        this.parents = new int[n];
        for (int i = 0; i < n; i++) {
            parents[i] = i;
        }
        this.sizes = new int[n];
        Arrays.fill(sizes, 1);
        this.count = n;
    }

    public void union(int x, int y) {
        int rx = find(x);
        int ry = find(y);
        if (rx == ry) return; // x, y已经相连
        if (sizes[rx] < sizes[ry]) {
            parents[rx] = ry;
            sizes[ry] += sizes[rx];
        }
        else {
            parents[ry] = rx;
            sizes[rx] += sizes[ry];
        }
        count--; // 只有union时会改变连通分量数
    }

    public int find(int x) {
        if (parents[x] != x) {
            parents[x] = find(parents[x]); // 在find()时进行路径压缩，让中间节点直接记录根
        }
        return parents[x];
    }

    public int getSize(int x) {
        return sizes[x];
    }

    // 返回p，q是否在同一集合中，直接判断根是否相同即可
    public boolean connected(int p, int q) {
        return find(p) == find(q);
    }

    // 返回集合数，可以直接对[0, n)遍历，用HashSet存根，根数即count
    public int count() {
        return this.count;
    }
}

// UnionFind + 能查询每个子集合的边数。LeetCode2685. 统计完全连通分量的数量用到，我的题解: https://leetcode.cn/problems/count-the-number-of-complete-components/solutions/2491899/bing-cha-ji-qiu-lian-tong-fen-liang-bian-y9co/
class UnionFindWithEdgeCount {
    private int[] parents;

    private int[] sizes;

    private int[] edgeCount;

    public UnionFindWithEdgeCount(int n) {
        this.parents = new int[n];
        for (int i = 0; i < n; i++) {
            parents[i] = i;
        }
        this.sizes = new int[n];
        Arrays.fill(sizes, 1);
        this.edgeCount = new int[n];
    }

    public void union(int x, int y) {
        int rx = find(x);
        int ry = find(y);
        if (rx == ry) {
            edgeCount[rx]++;
            return;
        }
        if (sizes[rx] < sizes[ry]) {
            parents[rx] = ry;
            sizes[ry] += sizes[rx];
            edgeCount[ry] += edgeCount[rx] + 1;
        }
        else {
            parents[ry] = rx;
            sizes[rx] += sizes[ry];
            edgeCount[rx] += edgeCount[ry] + 1;
        }
    }

    public int find(int x) {
        if (parents[x] != x) {
            parents[x] = find(parents[x]);
        }
        return parents[x];
    }

    public int getSize(int x) {
        return sizes[x];
    }

    public int getEdgeCount(int x) {
        return edgeCount[x];
    }
}

class TestUnionFind {
    public static void main(String[] args) {
        UnionFind uf = new UnionFind(3);
        uf.union(0, 1);
        System.out.println(uf.find(1));
        System.out.println(uf.getSize(uf.find(1)));

        UnionFindMoreApi uf2 = new UnionFindMoreApi(3);
        uf2.union(0, 2);
        System.out.println(uf2.connected(0, 1));
        System.out.println(uf2.count());

        UnionFindWithEdgeCount uf3 = new UnionFindWithEdgeCount(3);
        uf3.union(0, 2);
        uf3.union(0, 1);
        System.out.println(uf3.getEdgeCount(uf3.find(2)));
    }
}