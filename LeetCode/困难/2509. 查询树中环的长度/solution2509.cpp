/*
url: https://leetcode.cn/problems/cycle-length-queries-in-a-tree/
标签: 【算法题单】位运算
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2509 {
public:
    // 找lca，用编号的二进制性质
    vector<int> cycleLengthQueries(int n, vector<vector<int>>& queries) {
        vector<int> ans(queries.size());

        auto f = [&](int x, int y) {
            if (x > y) swap(x, y);
            int len1 = __lg(x) + 1;
            int len2 = __lg(y) + 1;
            int c = 0;
            while ((y >> c + (len2 - len1)) != (x >> c)) c++;
            return 2 * c + len2 - len1 + 1;
        };

        for (int i = 0; i < queries.size(); i++) {
            ans[i] = f(queries[i][0], queries[i][1]);
        }

        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2509 solu;
    auto a = solu.cycleLengthQueries(3, *new vector<vector<int>>{{5,3},{4,7},{2,3}});
    return 0;
}