/*
url: https://leetcode.cn/problems/closest-equal-element-queries/
标签: 【题单】二分算法
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3488 {
public:
    vector<int> solveQueries(vector<int>& nums, vector<int>& queries) {
        int n = nums.size(), m = queries.size();
        unordered_map<int, vector<int>> mp;
        for (int i = 0; i < n; i++) mp[nums[i]].push_back(i);
        vector<int> ans(m);
        for (int i = 0; i < m; i++) {
            int x = queries[i];
            auto &vec = mp[nums[x]];
            if (vec.size() == 1) {
                ans[i] = -1;
                continue;
            }
            int sz = vec.size();
            // 第一个>=，一定能搜索到等于
            int p = lower_bound(vec.begin(), vec.end(), x) - vec.begin();
            int res = INT_MAX;
            int xpre = vec[(p - 1 + sz) % sz];
            int xnxt = vec[(p + 1 + sz) % sz];
            int dis1 = abs(x - xpre); // p - ppre可能是负数，例如 14 14，第一个14的上一个14在后面(循环数组)
            int dis2 = abs(xnxt - x);
            res = min({res, dis1, n - dis1, dis2, n - dis2});
            ans[i] = res;
        }
        return ans;
    }

    // 参考灵茶题解，用哨兵处理循环数组的问题
    vector<int> solveQueries_implementation2(vector<int>& nums, vector<int>& queries) {
        int n = nums.size(), m = queries.size();
        unordered_map<int, vector<int>> mp;
        for (int i = 0; i < n; i++) mp[nums[i]].push_back(i);
        for (auto &[_, vec] : mp) {
            // 前后增加哨兵，这样考虑最近元素就只需看左右，不用考虑前一个和后一个元素的下标突变大小的问题
            int temp = vec.front();
            vec.insert(vec.begin(), vec.back() - n);
            vec.push_back(temp + n);
        }
        vector<int> ans(m);
        for (int i = 0; i < m; i++) {
            int x = queries[i]; // x为在nums中的下标
            auto &vec = mp[nums[x]];
            if (vec.size() == 3) {
                ans[i] = -1;
                continue;
            }
            // 第一个>=，一定能搜索到等于
            int p = lower_bound(vec.begin(), vec.end(), x) - vec.begin(); // p为x在vec中的下标
            ans[i] = min(x - vec[p - 1], vec[p + 1] - x);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3488 solu;
    auto a = solu.solveQueries(*new vector<int>{1,3,1,4,1,3,2}, *new vector<int>{0,3,5});
    auto b = solu.solveQueries(*new vector<int>{14,14,4,2,19,19,14,19,14}, *new vector<int>{2,4,8,6,3});

    auto c = solu.solveQueries_implementation2(*new vector<int>{1,3,1,4,1,3,2}, *new vector<int>{0,3,5});
    return 0;
}