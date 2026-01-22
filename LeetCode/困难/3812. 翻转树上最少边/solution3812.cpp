/*
url: https://leetcode.cn/problems/minimum-edge-toggles-on-a-tree/
参考: https://leetcode.cn/problems/minimum-edge-toggles-on-a-tree/solutions/3883163/dfspythonjavacgo-by-endlesscheng-5m1i/
标签: LeetCode第174场双周赛
*/

// 这次双周赛两题

#include <bits/stdc++.h>

using namespace std;

class Solution3812 {
public:
    /* 参考灵茶题解，树的问题，先从单链考虑，一条边要么翻转，要么不翻转，翻转多次只等价于奇偶性。
    而边上的点翻不翻转是固定的。
    因此，要从叶子节点开始看，每步能确定到底要不要翻转，最后到根。
    选任一个点作为树根都行。
    */
    vector<int> minimumFlips(int n, vector<vector<int>>& edges, string start, string target) {
        vector<vector<pair<int, int>>> g(n); // 答案要返回边的编号，所以建图时把边编号也带上
        for (int i = 0; i < edges.size(); i++) {
            int u = edges[i][0], v = edges[i][1];
            g[u].push_back({v, i});
            g[v].push_back({u, i});
        }

        vector<int> ans; // 要翻转的边

        // dfs的返回值表示 r - fa 这条边是否要翻转
        auto dfs = [&](auto& dfs, int r, int fa) -> bool {
            bool rev = start[r] != target[r]; // rev 表示 r 的颜色是否还需要翻转
            for (auto [nbr, idx] : g[r]) {
                if (nbr == fa) continue;
                if (dfs(dfs, nbr, r)) {
                    ans.push_back(idx); // 由父节点统计一条边翻转与否
                    rev = !rev;
                }
            }
            return rev;
        };

        if (dfs(dfs, 0, -1)) return {-1}; // 选 0 作为树根
        sort(ans.begin(), ans.end());
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3812 solu;
    auto a = solu.minimumFlips(3, *new vector<vector<int>>{{0,1},{1,2}}, "010", "100");
    auto b = solu.minimumFlips(7, *new vector<vector<int>>{{0,1},{1,2},{2,3},{3,4},{3,5},{1,6}}, "0011000", "0010001");
    return 0;
}