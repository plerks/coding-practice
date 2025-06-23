/*
url: https://leetcode.cn/problems/sum-of-total-strength-of-wizards/
相关: LeetCode1856. 子数组最小乘积的最大值
标签: 【算法题单】单调栈, 贡献法, 前缀和的前缀和
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2281 {
public:
    // 这题想来想去还是分析出来了，一开始想的分析(l, r)中每个数会在nums[i] * sum的sum中出现多少次，这样的思路分析不出来，
    // 大概会是 (r - i) * 1 * x1 + (r - i) * 2 * x2 + ... 的形式，倒是能启发要用前缀和的前缀和。
    // 要看以某一个位置为左边界的话，有哪些子数组（有哪些右边界）
    int totalStrength(vector<int>& nums) {
        int n = nums.size();
        const int MOD = 1e9 + 7;
        vector<int> left(n); // 左侧第一个 <
        vector<int> right(n, n); // 右侧第一个 <=
        stack<int> st;
        for (int i = 0; i < n; i++) {
            while (!st.empty() && nums[st.top()] >= nums[i]) {
                right[st.top()] = i;
                st.pop();
            }
            left[i] = st.empty() ? -1 : st.top();
            st.push(i);
        }

        vector<long long> pre(n + 1);
        for (int i = 0; i < n; i++) {
            pre[i + 1] = pre[i] + nums[i];
        }
        vector<long long> ppre(n + 1);
        for (int i = 0; i < n; i++) {
            ppre[i + 1] = ppre[i] + pre[i + 1];
        }
        ppre.insert(ppre.begin(), 0); // 再偏移一下，ppre向右偏移2
        
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            // nums[i]作为最小值，有 (right - i) * (i - left) 个子数组
            // (l, r)
            int l = left[i];
            int r = right[i];
            /* (l .. i .. r) 怎么算贡献总和？
                此题的定义为最小值 * 子数组的和，考虑 l + 1 这个位置，其右端点范围为[i...r)。于是总贡献为
                nums[i] * (pre[r - 1]-pre[l] + pre[r - 2]-pre[l] + ... + pre[i]-pre[l])
              = nums[i] * (pre[r - 1] + ... + pre[i] - (r - i) * pre[l])
                这说明要计算前缀和的前缀和，类似`LeetCode1508. 子数组和排序后的区间和`

                一般的，考虑左端点在x位置，l + 1 <= x <= i，这个左端点所关联的区间，总贡献为：
                nums[i] * (pre[r - 1] + ... + pre[i] - (r - i) * pre[x - 1])
              = nums[i] * (ppre[r - 1] - ppre[i - 1] - (r - i) * pre[x - 1])
              
                然后再把所有x的可能取值在加起来，总和为
                nums[i] * (ppre[r - 1] - ppre[i - 1]) * (i - l) - nums[i] * (r - i) * (pre[l] + ... + pre[i - 1])
              = nums[i] * (ppre[r - 1] - ppre[i - 1]) * (i - l) - nums[i] * (r - i) * (ppre[i - 1] - ppre[l - 1])
            */

            // cout << l << endl;
            // l可能为-1，ppre向右偏移1还不够，ppre[l - 1 + offset]，offset为1，l可能为-1，会越界，得让ppre向右偏移2

            // ans = ans + nums[i] * (ppre[r - 1 + 2] - ppre[i - 1 + 2]) * (i - l) - nums[i] * (r - i) * (ppre[i - 1 + 2] - ppre[l - 1 + 2]);
            long long t1 = nums[i] * ((ppre[r - 1 + 2] - ppre[i - 1 + 2]) % MOD) % MOD; // ppre可能比较大（超int），相乘可能超long long，要先 % 一下
            long long part1 = t1 * (i - l) % MOD;
            
            long long t2 = (long long)nums[i] * (r - i) % MOD;
            long long part2 = t2 * ((ppre[i - 1 + 2] - ppre[l - 1 + 2]) % MOD) % MOD;
            
            ans = (ans + (part1 - part2 + MOD) % MOD) % MOD; // 本身每次ans都是增加的，但是part1和part2都先经过了%处理，现在可能已经part1 < part2了，所以要 + MOD 处理负数
        }
        return ans % MOD;
    }

    // 参考灵茶题解，把上面奇乱无比的 % MOD 写得清楚一点，把nums[i]先提出来
    int totalStrength_implementation2(vector<int>& nums) {
        int n = nums.size();
        const int MOD = 1e9 + 7;
        vector<int> left(n); // 左侧第一个 <
        vector<int> right(n, n); // 右侧第一个 <=
        stack<int> st;
        for (int i = 0; i < n; i++) {
            while (!st.empty() && nums[st.top()] >= nums[i]) {
                right[st.top()] = i;
                st.pop();
            }
            left[i] = st.empty() ? -1 : st.top();
            st.push(i);
        }

        vector<long long> ppre(n + 2);
        long long pre = 0; // 算前缀和的前缀和，前缀和可以只用一个变量记录，不用申请一个vector
        for (int i = 0; i < n; i++) {
            pre += nums[i];
            ppre[i + 2] = (ppre[i + 1] + pre) % MOD; // ppre就提前取模，改变了大小关系，ans每次加的量可能变成负数了。在 % MOD 之前加上足够的 MOD 变成正的
        }
        
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            int l = left[i];
            int r = right[i];
            // ans = ans + nums[i] * { (ppre[r - 1 + 2] - ppre[i - 1 + 2]) * (i - l) - (r - i) * (ppre[i - 1 + 2] - ppre[l - 1 + 2]) };
            long long t = (ppre[r - 1 + 2] - ppre[i - 1 + 2]) * (i - l) - (r - i) * (ppre[i - 1 + 2] - ppre[l - 1 + 2]);
            t = (t + MOD) % MOD;
            ans = (ans + nums[i] * t) % MOD;
        }
        return (ans + MOD) % MOD;
    }
};

int main(int argc, char const *argv[]) {
    Solution2281 solu;
    cout << solu.totalStrength(*new vector<int>{1,3,1,2}) << endl;
    cout << solu.totalStrength(*new vector<int>{5,4,6}) << endl;
    
    cout << solu.totalStrength_implementation2(*new vector<int>{5,4,6}) << endl;
    return 0;
}