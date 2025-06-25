/*
url: https://leetcode.cn/problems/making-a-large-island/
标签: 【算法题单】网格图, 并查集
*/

#include <bits/stdc++.h>

using namespace std;

class UnionFind {
public:
    vector<int> parent;
    vector<int> size;

    UnionFind(int n) : parent(n), size(n, 1) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    void unite(int x, int y) {
        int rx = find(x);
        int ry = find(y);
        if (rx == ry) return;
        if (size[rx] < size[ry]) {
            parent[rx] = ry;
            size[ry] += size[rx];
        }
        else {
            parent[ry] = rx;
            size[rx] += size[ry];
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    int getSize(int x) {
        return size[find(x)];
    }
};

class Solution827 {
public:
    int largestIsland(vector<vector<int>>& grid) {
        int n = grid.size(); // grid为方阵

        auto legal = [&](int i, int j) {
            return 0 <= i && i < n && 0 <= j && j < n;
        };

        UnionFind uf(n * n);

        auto hash = [&](int i, int j) {
            return i * n + j;
        };

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    if (legal(i - 1, j) && grid[i - 1][j] == 1) uf.unite(hash(i, j), hash(i - 1, j));
                    if (legal(i + 1, j) && grid[i + 1][j] == 1) uf.unite(hash(i, j), hash(i + 1, j));
                    if (legal(i, j - 1) && grid[i][j - 1] == 1) uf.unite(hash(i, j), hash(i, j - 1));
                    if (legal(i, j + 1) && grid[i][j + 1] == 1) uf.unite(hash(i, j), hash(i, j + 1));
                }
            }
        }

        int ans = *max_element(uf.size.begin(), uf.size.end());
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) continue;
                int t = 1;
                unordered_set<int> st;
                if (legal(i - 1, j) && grid[i - 1][j] == 1) st.insert(uf.find(hash(i - 1, j)));
                if (legal(i + 1, j) && grid[i + 1][j] == 1) st.insert(uf.find(hash(i + 1, j)));
                if (legal(i, j - 1) && grid[i][j - 1] == 1) st.insert(uf.find(hash(i, j - 1)));
                if (legal(i, j + 1) && grid[i][j + 1] == 1) st.insert(uf.find(hash(i, j + 1)));

                for (int x : st) {
                    t += uf.getSize(x);
                }
                ans = max(ans, t);
            }
        }

        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution827 solu;
    // cout << solu.largestIsland(*new vector<vector<int>>{{1, 0}, {0, 1}}) << endl;
    cout << solu.largestIsland(*new vector<vector<int>>{{1, 1}, {1, 0}}) << endl;
    // cout << solu.largestIsland(*new vector<vector<int>>{{1, 1}, {1, 1}}) << endl;
    return 0;
}