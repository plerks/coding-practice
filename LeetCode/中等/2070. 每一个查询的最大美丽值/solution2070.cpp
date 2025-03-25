/*
url: https://leetcode.cn/problems/most-beautiful-item-for-each-query/
标签: 【题单】二分算法
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2070 {
public:
    vector<int> maximumBeauty(vector<vector<int>>& items, vector<int>& queries) {
        int n = items.size();
        sort(items.begin(), items.end());
        vector<int> mx(n);
        mx[0] = items.front()[1];
        for (int i = 1; i < n; i++) mx[i] = max(mx[i - 1], items[i][1]); // 记前缀最大值
        vector<int> ans(queries.size());
        for (int i = 0; i < queries.size(); i++) {
            int q = queries[i];
            // 搜索最后一个<=q的price，查最大美丽值
            int index = lower_bound(items.begin(), items.end(), q, [&](auto &x, int q) {
                return x[0] <= q;
            }) - items.begin() - 1;
            if (index == -1) ans[i] = 0;
            else ans[i] = mx[index];
        }
        return ans;
    }

    /* 参考灵茶题解，排序之后，对于相同的price的pair，只需要留beauty值最大的那个即可，
    而对于不同的price，如果price小的beauty值还大，那么price大的那个pair完全不需要留，
    于是，整理之后，能让item变成price互不相同，且beauty值严格单增的序列。
    */
    vector<int> maximumBeauty_implementation2(vector<vector<int>>& items, vector<int>& queries) {
        int n = items.size();
        sort(items.begin(), items.end());
        int k = 0; // 原地优化，k记最后一个位置，k + 1为长度
        for (int i = 1; i < n; i++) {
            if (items[i][0] == items[k][0]) {
                items[k][1] = items[i][1];
            }
            else if (items[i][1] > items[k][1]) {
                items[++k] = items[i];
            }
        }
        vector<int> ans(queries.size());
        for (int i = 0; i < queries.size(); i++) {
            int q = queries[i];
            // 搜索最后一个<=q的price
            int index = lower_bound(items.begin(), items.begin() + k + 1, q, [&](auto &x, int q) {
                return x[0] <= q;
            }) - items.begin() - 1;
            if (index == -1) ans[i] = 0;
            else ans[i] = items[index][1];
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2070 solu;
    auto a = solu.maximumBeauty(*new vector<vector<int>>{{1,2},{3,2},{2,4},{5,6},{3,5}}, *new vector<int>{1,2,3,4,5,6});
    auto b = solu.maximumBeauty_implementation2(*new vector<vector<int>>{{1,2},{3,2},{2,4},{5,6},{3,5}}, *new vector<int>{1,2,3,4,5,6});
    return 0;
}