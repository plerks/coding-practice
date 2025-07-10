/*
url: https://leetcode.cn/problems/find-all-people-with-secret/
参考: https://leetcode.cn/problems/find-all-people-with-secret/solutions/1126330/5941c-bing-cha-ji-yi-miao-liao-you-shi-y-x8s9/
标签: 【算法题单】图论算法
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

    /* isolate会不会发生：y通过x合并到z，现在isolate(x)，导致parent[y]不对了？
    会，也不会，上面那种情况，xyz都不是0所在的连通分量，后面y也必定会isolate，所以没问题。这个isolate()函数确实不具备通用性，只是此题能用，
    因为这题除了0所在的连通分量，所有其它分量的所有点都会全部拆成独立的，所以可以写出isolate函数。
    且size也可以正常维护。
    */
    void isolate(int x) {
        parent[x] = x;
        size[x] = 1;
    }
};

class Solution2092 {
public:
    /* 参考题解，拆非0所在的连通分量时不需要遍历n，只需要遍历当前的t分组就行了。
    isolate会不会发生：y通过x合并到z，现在isolate(x)，导致parent[y]不对了？
    会，也不会，上面那种情况，xyz都不是0所在的连通分量，后面y也必定会isolate，所以没问题。这个isolate()函数确实不具备通用性，只是此题能用，
    因为这题除了0所在的连通分量，所有其它分量的所有点都会全部拆成独立的，所以可以写出isolate函数。
    且size也可以正常维护。
    */
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        sort(meetings.begin(), meetings.end(), [&](auto &x, auto & y) {
            return x[2] < y[2];
        });
        UnionFind uf(n);
        uf.unite(0, firstPerson);

        // 分组循环
        for (int i = 0; i < meetings.size();) {
            int start = i;
            for (i++; i < meetings.size() && meetings[i][2] == meetings[i - 1][2]; i++);
            // [start, i)
            for (int k = start; k < i; k++) {
                int x = meetings[k][0], y = meetings[k][1], t = meetings[k][2];
                uf.unite(x, y);
            }

            // 把非0所在的连通分量拆掉
            for (int k = start; k < i; k++) {
                int x = meetings[k][0], y = meetings[k][1], t = meetings[k][2];
                if (uf.find(x) != uf.find(0)) {
                    uf.isolate(x);
                    uf.isolate(y);
                }
            }
        }

        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (uf.find(i) == uf.find(0)) ans.push_back(i);
        }

        return ans;
    }

    // 见灵茶题解，也可以分组循环，每次建当前t分组的图，然后从所有知晓秘密的点dfs / 多源bfs，找到下一轮知晓所有秘密的人
};

int main(int argc, char const *argv[]) {
    Solution2092 solu;
    auto a = solu.findAllPeople(6, *new vector<vector<int>>{{1,2,5},{2,3,8},{1,5,10}}, 1);
    return 0;
}