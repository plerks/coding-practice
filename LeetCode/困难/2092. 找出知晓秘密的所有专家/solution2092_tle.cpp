/*
url: https://leetcode.cn/problems/find-all-people-with-secret/
标签: 【算法题单】图论算法
*/
#include <bits/stdc++.h>

using namespace std;

class UnionFind {
public:
    vector<int> parent;

    UnionFind(int n) : parent(n) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    void unite(int x, int y) {
        int rx = find(x);
        int ry = find(y);
        if (rx == ry) return;
        parent[rx] = ry;
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
};

class Solution2092 {
public:
    /* 我的解法，超时，33 / 56 个通过的测试用例。
    按时间来分组，对于某个时间t，相当于要跑一遍多源bfs找连通分量，这可以通过并查集来维护。
    但是，假如一个t后状态是 {0,firstPerson} {5,6} ，5和6的相连会导致下一时刻，如果有7告诉6，会把5也连起来了。
    所有一轮t过后，要把非0所在的连通分量拆掉，我的写法会超时。不需要遍历n，只需要遍历当前的t分组就行了。
    */
    vector<int> findAllPeople_tle(int n, vector<vector<int>>& meetings, int firstPerson) {
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
            for (int i = 0; i < n; i++) {
                if (uf.find(i) != uf.find(0)) {
                    uf.parent[i] = i;
                }
            }
        }

        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (uf.find(i) == uf.find(0)) ans.push_back(i);
        }

        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2092 solu;
    auto a = solu.findAllPeople_tle(6, *new vector<vector<int>>{{1,2,5},{2,3,8},{1,5,10}}, 1);
    return 0;
}