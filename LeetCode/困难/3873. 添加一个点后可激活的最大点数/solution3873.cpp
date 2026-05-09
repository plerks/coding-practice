/*
url: https://leetcode.cn/problems/maximum-points-activated-with-one-addition/
参考: https://leetcode.cn/problems/maximum-points-activated-with-one-addition/solutions/3925832/bing-cha-ji-pythonjavacgo-by-endlesschen-n00l/
标签: 中介并查集
*/

#include <bits/stdc++.h>

using namespace std;

struct UnionFind {
    unordered_map<long long, long long> fa;
    unordered_map<long long, long long> size;

    long long find(int u) {
        // 可以用 auto it = fa.find() ，再用 it 来判断，减小查询次数
        if (!fa.count(u)) {
            fa[u] = u, size[u] = 1;
            return u;
        }
        if (fa[u] != u) fa[u] = find(fa[u]);
        return fa[u];
    }

    void unite(int u, int v) {
        if (find(u) == find(v)) return;
        if (size[u] < size[v]) swap(u, v);
        // v 合并到 u 上
        long long ru = find(u), rv = find(v);
        fa[rv] = ru;
        size[ru] += size[rv];
    }
};

class Solution3873 {
public:
    /* 参考灵茶题解，
    如何去合并 x坐标相同 or y坐标相同 的点？
    使用横纵坐标作为中介，将中介的数字作为代表元（并查集要改为用map），(y 要加上 offset 以使其与 x 取值不同)，此时，
    x / y 的值相同的集合通过中介连起来了，集合之间连起来了，然后在把点数累加到每个类的代表元里就行。
    */
    int maxActivated(vector<vector<int>>& points) {
        long long OFFSET = 2e9 + 1; // -10^9 <= xi, yi <= 10^9，这样 + OFFSET 后保证 x, y 的值不重复，也可以离散化处理
        UnionFind uf;
        for (auto& p : points) {
            uf.unite(p[0], p[1] + OFFSET);
        }

        // 先把中介点合并起来，然后才能统计分量中的点数（累加到代表元（某个中介）上）
        unordered_map<long long, long long> node_size;
        for (auto& p : points) {
            node_size[uf.find(p[0])]++;
        }

        int mx1 = 0, mx2 = 0;
        for (auto &[k, v] : node_size) {
            if (v > mx1) {
                mx2 = mx1;
                mx1 = v;
            }
            else if (v > mx2) mx2 = v;
        }
        return mx1 + mx2 + 1;
    }
};

int main(int argc, char const *argv[]) {
    Solution3873 solu;
    // cout << solu.maxActivated(*new vector<vector<int>>{{1,1},{1,2},{2,2}}) << endl;
    // cout << solu.maxActivated(*new vector<vector<int>>{{2,2},{1,1},{3,3}}) << endl;
    cout << solu.maxActivated(*new vector<vector<int>>{{-1000000000,-1000000000},{1000000000,1000000000},{1,1}}) << endl;
    return 0;
}