/*
url: https://leetcode.cn/problems/maximum-points-activated-with-one-addition/
参考: https://leetcode.cn/problems/maximum-points-activated-with-one-addition/solutions/3925851/jian-tu-bfs-by-tsreaper-2i6y/
*/

#include <bits/stdc++.h>

using namespace std;

struct UnionFind {
    vector<int> fa;
    vector<int> size;

    UnionFind(int n) {
        fa.resize(n);
        iota(fa.begin(), fa.end(), 0);
        size.resize(n, 1);
    }

    long long find(int u) {
        if (fa[u] != u) {
            fa[u] = find(fa[u]);
        }
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
    /* 执行用时分布里的代码示例的思路。
    可以直接合并各个点，方式是按 x 和 y 合并，然后合并相邻的相等点
    */
    int maxActivated(vector<vector<int>>& points) {
        int n = points.size();
        vector<int> x_arr(n);
        iota(x_arr.begin(), x_arr.end(), 0);
        auto y_arr = x_arr;
        sort(x_arr.begin(), x_arr.end(), [&](auto x, auto y) {
            return points[x][0] < points[y][0];
        });
        sort(y_arr.begin(), y_arr.end(), [&](auto x, auto y) {
            return points[x][1] < points[y][1];
        });

        UnionFind uf(n);
        for (int i = 1; i < n; i++) {
            if (points[x_arr[i - 1]][0] == points[x_arr[i]][0]) uf.unite(x_arr[i - 1], x_arr[i]);
            if (points[y_arr[i - 1]][1] == points[y_arr[i]][1]) uf.unite(y_arr[i - 1], y_arr[i]);
        }
        int mx1 = 0, mx2 = 0;
        for (int i = 0; i < n; i++) {
            if (uf.fa[i] == i) {
                int sz = uf.size[i];
                if (sz > mx1) {
                    mx2 = mx1;
                    mx1 = sz;
                }
                else if (sz > mx2) mx2 = sz;
            }
        }
        return mx1 + mx2 + 1;
    }
};

int main(int argc, char const *argv[]) {
    Solution3873 solu;
    // cout << solu.maxActivated(*new vector<vector<int>>{{1,1},{1,2},{2,2}}) << endl;
    // cout << solu.maxActivated(*new vector<vector<int>>{{2,2},{1,1},{3,3}}) << endl;
    // cout << solu.maxActivated(*new vector<vector<int>>{{-1000000000,-1000000000},{1000000000,1000000000},{1,1}}) << endl;
    // cout << solu.maxActivated(*new vector<vector<int>>{{5,-4},{5,9}}) << endl;
    cout << solu.maxActivated(*new vector<vector<int>>{{-2,18},{-12,10},{-11,18}}) << endl;
    return 0;
}