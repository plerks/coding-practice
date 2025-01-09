/*
url: https://leetcode.cn/problems/maximum-score-of-non-overlapping-intervals/description/
参考: https://leetcode.cn/problems/maximum-score-of-non-overlapping-intervals/solutions/3039058/dong-tai-gui-hua-er-fen-cha-zhao-you-hua-wmuy/
      https://www.bilibili.com/video/BV18srKYLEd8/
相关: LeetCode1235. 规划兼职工作
标签: LeetCode第431场周赛
*/

// 这次周赛2题

#include <bits/stdc++.h>

using namespace std;

class Solution3414 {
public:
    /* 此题为`LeetCode1235. 规划兼职工作`加上最多选k个区间的约束
    则dp时需要加一个参数，f[i][j]表示对jobs[i, n-1]，至多选择j个job(0<=j<=4)的最大收益。
    排序之后会打乱编号，而题目要求输出原始的编号，所以要把原本的编号带着走
    */
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();
        struct tuple {int l, r, w, idx;};
        vector<tuple> jobs;
        for (int i = 0; i < n; i++) {
            jobs.push_back({intervals[i][0], intervals[i][1], intervals[i][2], i});
        }
        sort(jobs.begin(), jobs.end(), [&](const tuple& x, const tuple& y){
            return x.l < y.l;
        });
        // f[i][j] = max(f[i + 1][j], w + f[k][j - 1])，k为第一个开始时间 > r 的任务 (这题端点重叠不合法)
        // f[i][j]是(值, 选择序列)
        vector<vector<pair<long long, vector<int>>>> f(n + 1, vector<pair<long long, vector<int>>>(5, make_pair(0, vector<int>())));
        for (int i = n - 1; i >= 0; i--) {
            auto [l, r, w, idx] = jobs[i];

            int left = 0, right = jobs.size() - 1;
            while (left <= right) {
                int mid = (left + right) / 2;
                if (jobs[mid].l <= r) left = mid + 1;
                else right = mid - 1;
            }
            int k = left;
            
            for (int j = 1; j < 5; j++) {
                long long s1 = f[i + 1][j].first;
                long long s2 = w + f[k][j - 1].first;
                if (s1 > s2) {
                    f[i][j] = f[i + 1][j];
                    continue;
                }
                vector<int> new_idx = f[k][j - 1].second;
                new_idx.push_back(idx);
                sort(new_idx.begin(), new_idx.end());
                if (s2 > s1) {
                    f[i][j] = {s2, new_idx};
                }
                else {
                    f[i][j] = {s1, min(f[i + 1][j].second, new_idx)};
                }
            }
        }
        return f[0][4].second;
    }
};

int main(int argc, char const *argv[]) {
    Solution3414 solu;
    auto a = solu.maximumWeight(*new vector<vector<int>>{{1,3,2},{4,5,2},{1,5,5},{6,9,3},{6,7,1},{8,9,1}});
    return 0;
}