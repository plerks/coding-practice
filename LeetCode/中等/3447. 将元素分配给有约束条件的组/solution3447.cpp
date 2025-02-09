/*
url: https://leetcode.cn/problems/assign-elements-to-groups-with-constraints/
参考: https://www.bilibili.com/video/BV1ekN2ebEHx/
标签: LeetCode第436场周赛, 调和级数, 筛法
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3447 {
public:
    // 周赛时的解法，考虑因子，通过。也想过用那个枚举倍数然后调和级数的技巧，但是感觉n * sqrt(n)能过，就写的枚举因子
    vector<int> assignElements(vector<int>& groups, vector<int>& elements) {
        int n = groups.size();
        unordered_map<int, int> factor;
        for (int i = 0; i < elements.size(); i++) {
            if (!factor.count(elements[i])) factor[elements[i]] = i;
        }
        vector<int> ans(n, INT_MAX);
        for (int i = 0; i < n; i++) {
            int x = groups[i];
            for (int d = 1; d * d <= x; d++) {
                if (x % d == 0) {
                    if (d * d != x) {
                        if (factor.count(d)) ans[i] = min(ans[i], factor[d]);
                        if (factor.count(x / d)) ans[i] = min(ans[i], factor[x / d]);
                    }
                    else if (factor.count(d)) ans[i] = min(ans[i], factor[d]);
                }
            }
        }
        for (int &x : ans) {
            if (x == INT_MAX) x = -1;
        }
        return ans;
    }

    /* 灵茶题解解法，枚举倍数。用elements去筛值域，对所有倍数找到第一次因子出现位置。
    这个类似筛法的过程，当elements值各不相同时开销最大（[1, 2, ..., n]），时间复杂度为O(mx/1 + mx/2 + ... + mx/n)，
    时间复杂度O(mx * logn + m)，mx为最大范围，m为groups长度，n为elements长度。
    */
    vector<int> assignElements_implementation2(vector<int>& groups, vector<int>& elements) {
        int mx = *max_element(groups.begin(), groups.end());
        vector<int> map(mx + 1, -1);
        for (int i = 0; i < elements.size(); i++) {
            int x = elements[i];
            if (x > mx || map[x] != -1) continue; // 超范围或者已被更小的筛过，跳过
            for (int y = x; y <= mx; y += x) {
                if (map[y] == -1) map[y] = i;
            }
        }
        vector<int> ans(groups.size());
        for (int i = 0; i < groups.size(); i++) {
            int x = groups[i];
            ans[i] = map[x];
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3447 solu;
    auto a = solu.assignElements(*new vector<int>{2,3,5,7}, *new vector<int>{5,3,3});
    auto b = solu.assignElements_implementation2(*new vector<int>{2,3,5,7}, *new vector<int>{5,3,3});
    return 0;
}