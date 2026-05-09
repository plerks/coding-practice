/*
url: https://leetcode.cn/problems/longest-arithmetic-sequence-after-changing-at-most-one-element/
参考: https://leetcode.cn/problems/longest-arithmetic-sequence-after-changing-at-most-one-element/solutions/3925831/qian-hou-zhui-fen-jie-pythonjavacgo-by-e-hys8/
标签: 前后缀分解, 分组循环, 状态机dp
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3872 {
public:
    // 周赛时写的巨复杂的前后缀分解
    int longestArithmetic(vector<int>& nums) {
        int n = nums.size();
        bool ok = true;
        for (int i = 2; i < n; i++) {
            if (nums[i] - nums[i - 1] != nums[i - 1] - nums[i - 2]) {
                ok = false;
                break;
            }
        }
        if (ok) return n;
        // 现在 n >= 3

        // 前后缀分解
        vector<int> pre(n + 1);
        pre[0 + 1] = 1;
        pre[1 + 1] = 2;
        for (int i = 2; i < n; i++) {
            if (nums[i] - nums[i - 1] == nums[i - 1] - nums[i - 2]) {
                pre[i + 1] = pre[i - 1 + 1] + 1;
            }
            else pre[i + 1] = 2;
        }
        vector<int> suf(n + 1);
        suf[n - 1] = 1;
        suf[n - 2] = 2;
        for (int i = n - 3; i >= 0; i--) {
            if (nums[i] - nums[i + 1] == nums[i + 1] - nums[i + 2]) {
                suf[i] = suf[i + 1] + 1;
            }
            else suf[i] = 2;
        }

        int ans = 0;
        // i = 0 和 i = n - 1
        ans = max(1 + suf[1], pre[n - 2 + 1] + 1);
        // i = 1
        ans = max(ans, 1 + suf[2]); // 不拼，就改 i
        if ((nums[0] + nums[2]) % 2 == 0) {
            if (n == 3) ans = max(ans, 3);
            else {
                int expect = (nums[0] + nums[2]) / 2;
                if (expect - nums[2] == nums[2] - nums[3]) ans = max(ans, 2 + suf[2]);
            }
        }
        // i = n - 2
        ans = max(ans, pre[n - 3 + 1] + 1); // 不拼，就改 i
        if ((nums[n - 1] + nums[n - 3]) % 2 == 0) {
            if (n == 3) ans = max(ans, 3);
            else {
                int expect = (nums[n - 1] + nums[n - 3]) / 2;
                if (expect - nums[n - 3] == nums[n - 3] - nums[n - 4]) ans = max(ans, pre[n - 3 + 1] + 2);
            }
        }
        // 现在 i 的左右至少两个元素
        for (int i = 2; i < n - 2; i++) {
            // 不拼，就改 i
            ans = max(ans, 1 + suf[i + 1]);
            ans = max(ans, pre[i - 1 + 1] + 1);
            // 先尝试拼一个
            if ((nums[i - 1] + nums[i + 1]) % 2 == 0) {
                if (n == 3) ans = max(ans, 3);
                else {
                    int expect = (nums[i - 1] + nums[i + 1]) / 2;
                    if (expect - nums[i + 1] == nums[i + 1] - nums[i + 2]) ans = max(ans, 2 + suf[i + 1]);
                    if (expect - nums[i - 1] == nums[i - 1] - nums[i - 2]) ans = max(ans, pre[i - 1 + 1] + 2);
                }
            }
            // 尝试拼更长的
            int d1 = nums[i - 2] - nums[i - 1];
            int d2 = nums[i + 1] - nums[i + 2];
            if ((nums[i - 1] + nums[i + 1]) % 2 == 0) {
                int expect = (nums[i - 1] + nums[i + 1]) / 2;
                if (d1 == d2 && nums[i - 1] - expect == d1 && expect - nums[i + 1] == d1) {
                    ans = max(ans, pre[i - 1 + 1] + 1 + suf[i + 1]);
                }
            }
        }
        return ans;
    }

    vector<int> calc(vector<int>& nums) {
        int n = nums.size();
        vector<int> pre(n);
        pre[0] = 1;
        pre[1] = 2;
        for (int i = 2; i < n; i++) {
            if (nums[i] - nums[i - 1] == nums[i - 1] - nums[i - 2]) {
                pre[i] = pre[i - 1] + 1;
            }
            else pre[i] = 2;
        }
        return pre;
    }

    // 灵茶题解的前后缀分解写法
    int longestArithmetic_impl2(vector<int>& nums) {
        int n = nums.size();
        vector<int> pre = calc(nums);
        int ans = *max_element(pre.begin(), pre.end()) + 1;
        if (ans >= n) ans = n; // 这样就包含了 a[i] 修改后作为端点的情况
        reverse(nums.begin(), nums.end());
        vector<int> suf = calc(nums);
        reverse(suf.begin(), suf.end());
        reverse(nums.begin(), nums.end());
        // max(pre) == max(suf)，无需重复计算

        /* 枚举多种情况
        一. 若 d = (a[i + 1] - a[i - 1]) / 2 为整数，修改中间位置的值
            如果 a[i - 1] - a[i - 2] == d == a[i + 2] - a[i + 1]，则拼接后的长度为 pre[i - 1] + 1 + suf[i + 1]
        二.
        1. d 为整数的前提：只满足 a[i - 1] - a[i - 2] == d，只能在 a[i - 1] 后拼 a[i] 和 a[i + 1]
        2. d 为整数的前提：只满足 a[i + 2] - a[i + 1] == d，只能在 a[i + 1] 前拼 a[i] 和 a[i - 1]
        3. 修改 a[i] ，拼在 pre[i - 1] 后面 / 修改 a[i] ，拼在 suf[i + 1] 前面，这两种情况被 max(pre) + 1 包含
        */
        for (int i = 1; i < n - 1; i++) {
            if ((nums[i + 1] - nums[i - 1]) % 2) continue;
            int d = (nums[i + 1] - nums[i - 1]) / 2;
            bool ok_left = i - 2 >= 0 && nums[i - 1] - nums[i - 2] == d;
            bool ok_right = i + 2 < n && nums[i + 2] - nums[i + 1] == d;
            if (ok_left && ok_right) ans = max(ans, pre[i - 1] + 1 + suf[i + 1]); // 左右都接
            else if (ok_left) ans = max(ans, pre[i - 1] + 2); // 一侧只能接一个元素，因为两侧公差不等
            else if (ok_right) ans = max(ans, suf[i + 1] + 2);
        }
        return ans;
    }

    /* 灵茶题解解法二，
    修改的位置一定在原本的等差子数组外两端，用分组循环枚举原等差段，然后往左右扩展。
    时间复杂度 O(n)
    */
    int longestArithmetic_impl3(vector<int>& nums) {
        int n = nums.size();
        int i = 1;
        int ans = 0;
        while (true) {
            int start = i - 1;
            int d = nums[i] - nums[i - 1];
            i++;
            while (i < n && nums[i] - nums[i - 1] == d) i++;

            // 现在 [start, i - 1] 是等差子数组，要么改 nums[start - 1]，要么改 nums[i]

            // 改 nums[start - 1]
            if (start - 2 >= 0 && nums[start] - nums[start - 2] == 2 * d) {
                ans = max(ans, 2 + i - start); // 不需要再往左扩展了，最多看到 start - 2 位置，再往左的话等同于之前的循环轮往右扩展
            }
            else ans = max(ans, i - max(start - 1, 0));

            if (i == n) return ans;

            // 改 nums[i]
            if (i + 1 < n && nums[i + 1] - nums[i - 1] == 2 * d) {
                int j = i + 2;
                // 这里的循环不会导致爆时间复杂度。因为既然 j 可以往右扩展，下一轮外循环会包含这里，往右的扩展不会重复遍历
                while (j < n && nums[j] - nums[j - 1] == d) j++;
                ans = max(ans, j - start);
            }
            else ans = max(ans, i - start + 1);
        }
        return -1;
    }

    /* 灵茶题解解法三，状态机dp，
    f(i, flag) 表示以 i 为右端点的最大长度，flag 表示还有没有修改机会，但不允许修改 i 位置，不然变成子问题时公差不一致了
    */
    int longestArithmetic_impl4(vector<int>& nums) {
        int n = nums.size();
        vector<array<int, 2>> f(n, {2, 2});
        f[0][0] = f[0][1] = 1;
        f[1][0] = f[1][1] = 2;
        for (int i = 2; i < n; i++) {
            // f[i][0]
            if (nums[i] - nums[i - 1] == nums[i - 1] - nums[i - 2]) {
                f[i][0] = f[i - 1][0] + 1;
                f[i][1] = f[i - 1][1] + 1; // 包含了不做修改的情况
            }

            // f[i][1]
            // 修改 i - 1 位置，长度至少为 3；如果 i - 3 能接上（公差相等），还可以更长。确认公差相等后，变成子问题 f[i - 2]
            f[i][1] = max(f[i][1], 3);
            if (i - 3 >= 0) {
                if ((nums[i - 2] - nums[i - 3]) * 2 == nums[i] - nums[i - 2]) { // 此时 (nums[i] + num[i - 2]) / 2 一定为整数
                    f[i][1] = max(f[i][1], f[i - 2][0] + 2);
                }
                // 修改 i - 2 位置，长度至少为 3；但是无法递归为子问题 f[i - 2]，因为此时 i - 2 已经改了
                // 必须再讨论一次，变成去用子问题 f[i - 3]
                int d = nums[i] - nums[i - 1];
                if (nums[i - 1] - nums[i - 3] == 2 * d) {
                    f[i][1] = max(f[i][1], 4);
                    if (i - 4 >= 0 && nums[i - 3] - nums[i - 4] == d) {
                        f[i][1] = max(f[i][1], f[i - 3][0] + 3);
                    }
                }
            }
            // 修改 <= i - 3 的位置，那么需要 i - 2, i - 1, i 已成等差，这种情况被包含在
            // 上面的 f[i][1] = f[i - 1][1] + 1; 中
        }
        int ans = 0;
        for (int i = 0; i < n; i++) ans = max(ans, f[i][1]);
        for (int i = 0; i < n - 1; i++) ans = max(ans, f[i][0] + 1); // f[i][0] 不允许修改 i 位置，这里允许改，要 + 1
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3872 solu;
    cout << solu.longestArithmetic(*new vector<int>{9,7,5,10,1}) << endl;
    cout << solu.longestArithmetic_impl4(*new vector<int>{1,1,2,3}) << endl;
    return 0;
}