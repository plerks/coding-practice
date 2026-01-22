/*
url: https://leetcode.cn/problems/best-reachable-tower/
标签: LeetCode第174场双周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3809 {
public:
    vector<int> bestTower(vector<vector<int>>& towers, vector<int>& center, int radius) {
        int cx = center[0], cy = center[1];
        int max_w = 0;
        pair<int, int> ans = {-1, -1};
        for (auto& vec : towers) {
            int u = vec[0], v = vec[1], w = vec[2];
            if (abs(u - cx) + abs(v - cy) <= radius) {
                if (w > max_w) {
                    ans = {u, v};
                    max_w = w;
                }
                else if (w == max_w) {
                    if (ans == make_pair(-1, -1)) ans = {u, v};
                    else ans = min(ans, {u, v});
                }
            }
        }
        return {ans.first, ans.second};
    }

    // 灵茶题解的简洁写法，组装成tuple再用tuple的比较
    vector<int> bestTower(vector<vector<int>>& towers, vector<int>& center, int radius) {
        int cx = center[0], cy = center[1];
        auto ans = tuple{1, -1, -1}; // 质量并列，取字典序最小的坐标，则要求 min tuple 才行，于是要把质量反号求出的才是最大tuple
        for (auto &vec : towers) {
            int u = vec[0], v = vec[1], w = vec[2];
            if (abs(u - cx) + abs(v - cy) <= radius) ans = min(ans, {-w, u, v});
        }
        return {get<1>(ans), get<2>(ans)};
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}