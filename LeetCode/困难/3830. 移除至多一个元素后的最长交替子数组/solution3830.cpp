/*
url: https://leetcode.cn/problems/longest-alternating-subarray-after-removing-at-most-one-element/
标签: LeetCode第487场周赛
*/

// 这次周赛两题，1，3题

#include <bits/stdc++.h>

using namespace std;

class Solution3830 {
public:
    // 周赛时的dp思路，是对的，但是我没调出来，可惜。
    int longestAlternating(vector<int>& t) {
        int n = t.size();
        int maxn = 1e5 + 1;
        int f[maxn][2][2];
        for (int i = 0; i < n; i++) f[i][0][0] = f[i][0][1] = f[i][1][0] = f[i][1][1] = 1;
        // vector<vector<vector<int>>> f(n, vector<vector<int>>(2, vector<int>(2, 1))); // 三重 vector 1500+ms，int 数组 70+ms
        for (int i = 0; i < n; i++) {
            int pre;
            // f[][][1] 表示还可以删除，则 t[i] 的上一个元素要么是 i - 1 ，要么是 i - 2 (用掉删除机会)
            // f[][0][] 表示从 i -> pre 往下走
            pre = i - 2;
            if (pre >= 0) {
                if (t[i] > t[pre]) {
                    f[i][0][1] = max(f[i][0][1], f[pre][1][0] + 1);
                }
                if (t[i] < t[pre]) {
                    f[i][1][1] = max(f[i][1][1], f[pre][0][0] + 1);
                }
            }
            pre = i - 1;
            if (pre >= 0) {
                if (t[i] > t[pre]) {
                    f[i][0][1] = max(f[i][0][1], f[pre][1][1] + 1);
                }
                if (t[i] < t[pre]) {
                    f[i][1][1] = max(f[i][1][1], f[pre][0][1] + 1);
                }
            }
            
            // f[][][0] 表示不能再删除了
            pre = i - 1;
            if (pre >= 0) {
                if (t[i] > t[pre]) {
                    f[i][0][0] = max({f[i][0][0], f[pre][1][0] + 1});
                }
                if (t[i] < t[pre]) {
                    f[i][1][0] = max({f[i][1][0], f[pre][0][0] + 1});
                }
            }
        }
        int ans = 1;
        for (int i = 0; i < n; i++) {
            ans = max({ans, f[i][0][1], f[i][1][1]});
        }
        return ans;
    }

    // 计算以 i 结尾的交替子数组长度（无删除）
    vector<int> calc(vector<int>& nums) {
        int n = nums.size();
        vector<int> f(n);
        for (int i = 0; i < n; i++) {
            if (i == 0 || nums[i] == nums[i - 1]) f[i] = 1;
            else if (i >= 2 && nums[i - 1] != nums[i - 2] && (nums[i] > nums[i - 1] == nums[i - 2] > nums[i - 1])) {
                f[i] = f[i - 1] + 1;
            }
            else {
                f[i] = 2;
            }
        }
        return f;
    }

    // 参考灵茶题解，枚举删除的一个点的位置，还可以前后缀分解，枚举删除的位置，然后把两端拼起来。
    int longestAlternating_impl2(vector<int>& nums) {
        int n = nums.size();
        vector<int> pre = calc(nums);
        reverse(nums.begin(), nums.end());
        vector<int> suf = calc(nums);
        reverse(suf.begin(), suf.end());
        reverse(nums.begin(), nums.end());

        int ans = *max_element(pre.begin(), pre.end()); // 不删除

        for (int i = 1; i < n - 1; i++) { // 删除头元素和尾元素没价值
            int len = 0;
            if (nums[i - 1] < nums[i + 1]) {
                // 由于 pre 和 suf 数组没有记录前一个位置是往上还是往下走，这里要判断，写得繁琐了些，把 pre 定义成 int [n][2] ，用第二个维度记录走向要好些
                // 这样如果 nums[i - 1] < nums[i + 1]，就直接是 len = pre[i - 1][1] + suf[i + 1][0]
                if (i - 2 < 0 || nums[i - 2] > nums[i - 1]) { // 线段 (i - 1) —— (i + 1) 左边那条线段符合交替关系
                    len += pre[i - 1];
                }
                else len += 1; // 就算线段没接上，至少可以增加 nums[i - 1] 这个点
                if (i + 2 >= n || nums[i + 1] > nums[i + 2]) {
                    len += suf[i + 1];
                }
                else len += 1;
            }
            else if (nums[i - 1] > nums[i + 1]) {
                if (i - 2 < 0 || nums[i - 2] < nums[i - 1]) {
                    len += pre[i - 1];
                }
                else len += 1;
                if (i + 2 >= n || nums[i + 1] < nums[i + 2]) {
                    len += suf[i + 1];
                }
                else len += 1;
            }
            ans = max(ans, len);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3830 solu;
    cout << solu.longestAlternating(*new vector<int>{1,2,2,1,1,2}) << endl;
    cout << solu.longestAlternating_impl2(*new vector<int>{1,1,2,2,1,1}) << endl;
    return 0;
}