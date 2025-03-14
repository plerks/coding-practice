/*
url: https://leetcode.cn/problems/count-substrings-that-satisfy-k-constraint-ii/
相关: LeetCode3258. 统计满足 K 约束的子字符串数量 I
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3261 {
public:
    // 我的解法，时间复杂度O(n + qlogn)
    vector<long long> countKConstraintSubstrings(string s, int k, vector<vector<int>>& queries) {
        int n = s.size();
        long long cnt[2]{};
        vector<long long> low(n);
        vector<long long> amount(n);
        for (int l = 0, r = 0; r < n; r++) {
            cnt[s[r] - '0']++;
            while (cnt[0] > k && cnt[1] > k) {
                cnt[s[l] - '0']--;
                l++;
            }
            low[r] = l; // 以r为右边界，左边界在哪里
            amount[r] = r - l + 1;
        }
        vector<long long> pre(n + 1); // 前缀和
        partial_sum(amount.begin(), amount.end(), pre.begin() + 1);
        vector<long long> ans(queries.size());
        for (int i = 0; i < queries.size(); i++) {
            auto &q = queries[i];
            int l = q[0], r = q[1];
            // 搜索左边界>=l的第一个位置
            int index = lower_bound(low.begin(), low.end(), l) - low.begin();
            long long res = 0;
            // [l, index)为右边界的话，左边界 < l的部分要削去，数量是 1 + 2 + ... + (index - l)。不过index - 1可能> r，要取下min
            // 灵茶题解这里的处理方式是lower_bound(low.begin(), low.begin() + r + 1, l)，这样当分割线>r时，得到的分割线为r，这样分割线总是在[l, r]内了
            int bound = min(index, r + 1);
            res += (long long)(1 + bound - l) * (bound - l) / 2;

            // 以[index, r]为右边界的话，左边界>=l，全部子字符串都能取，求这部分的和
            if (r >= index) {
                res += pre[r + 1] - pre[index - 1 + 1];
            }
            ans[i] = res;
        }
        return ans;
    }

    // 参考灵茶题解解法，把每次查询时用二分的结果提前计算出来，且由于单调性，用滑窗来预处理计算。时间复杂度O(n)
    vector<long long> countKConstraintSubstrings_implementation2(string s, int k, vector<vector<int>>& queries) {
        int n = s.size();
        long long cnt[2]{};
        vector<long long> low(n);
        vector<long long> amount(n);
        for (int l = 0, r = 0; r < n; r++) {
            cnt[s[r] - '0']++;
            while (cnt[0] > k && cnt[1] > k) {
                cnt[s[l] - '0']--;
                l++;
            }
            low[r] = l; // 以r为右边界，左边界在哪里
            amount[r] = r - l + 1;
        }
        vector<long long> pre(n + 1); // 前缀和
        partial_sum(amount.begin(), amount.end(), pre.begin() + 1);

        vector<int> upper(n); // low单增可以滑窗，upper[i]表示，当q[0]=i时，第一个>=i的low的元素的下标(即为第一个左边界>=i的位置，这个位置代表右端点)
        for (int i = 0, l = 0; i < n; i++) {
            while (l < n && low[l] < i) l++; // 这里不能写成l <= i，可能需要l一直++到n，直到找到low[l] >= i的位置
            upper[i] = l;
        }

        vector<long long> ans(queries.size());
        for (int i = 0; i < queries.size(); i++) {
            auto &q = queries[i];
            int l = q[0], r = q[1];
            // 分成[l, bound)和[bound, r]两部分
            int bound = min(upper[l], r + 1);
            ans[i] = (long long)(1 + bound - l) * (bound - l) / 2 + pre[r + 1] - pre[bound - 1 + 1];
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3261 solu;
    // auto a = solu.countKConstraintSubstrings("010101", 1, *new vector<vector<int>>{{0,5},{1,4},{2,3}});
    auto b = solu.countKConstraintSubstrings("000", 1, *new vector<vector<int>>{{0,0},{0,1},{0,2},{1,1},{1,2},{2,2}});
    auto c = solu.countKConstraintSubstrings_implementation2("000", 1, *new vector<vector<int>>{{0,0},{0,1},{0,2},{1,1},{1,2},{2,2}});
    return 0;
}