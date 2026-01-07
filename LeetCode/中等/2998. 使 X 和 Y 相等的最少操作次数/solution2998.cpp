/*
url: https://leetcode.cn/problems/minimum-number-of-operations-to-make-x-and-y-equal/
标签: 【题单】图论算法
*/

#include <bits/stdc++.h>

using namespace std;

class Solution2998 {
public:
    int minimumOperationsToMakeEqual(int x, int y) {
        if (x <= y) return y - x; // 参考灵茶题解，这种情况直接计算，因为其它 3 种操作都会把 x 变小
        queue<int> q;
        unordered_set<int> vis;
        q.push(x);
        vis.insert(x);
        int level = 1;

        auto add = [&](int x) {
            if (x == y) return true;
            if (vis.count(x)) return false;
            q.push(x);
            vis.insert(x);
            return false;
        };

        while (!q.empty()) {
            int sz = q.size();
            for (int _ = 0; _ < sz; _++) {
                int cur = q.front(); q.pop();
                if (cur % 11 == 0) {
                    if (add(cur / 11)) return level;
                }
                if (cur % 5 == 0) {
                    if (add(cur / 5)) return level;
                }
                if (add(cur - 1)) return level;
                if (add(cur + 1)) return level;
            }
            level++;
        }
        return -1;
    }
};

int main(int argc, char const *argv[]) {
    Solution2998 solu;
    // cout << solu.minimumOperationsToMakeEqual(26, 1) << endl;
    cout << solu.minimumOperationsToMakeEqual(1, 1) << endl;
    return 0;
}