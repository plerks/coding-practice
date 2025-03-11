/*
url: https://leetcode.cn/problems/permutations-iv/
参考: https://www.bilibili.com/video/BV1m39bYiEVV/
      https://leetcode.cn/problems/permutations-iv/solutions/3591426/cong-zuo-wang-you-gou-zao-pythonjavacgo-a0tqz/
相关: LeetCode3145. 大数组元素的乘积
标签: LeetCode第151场双周赛, 排列, 试填法
*/

// 这次双周赛2题

#include <bits/stdc++.h>

using namespace std;

vector<long long> f = {1}; // f[i]表示确定首位奇偶性后，i个正整数的总排列数
auto init = []() {
    for (int i = 1; f.back() < 1e15; i++) { // k <= 1e15
        f.push_back(f.back() * i);
        f.push_back(f.back() * i);
    }
    return 0;
}();

class Solution3470 {
public:
    /* 灵茶题解，从左到右填，
    周赛时知道是要用试填法一个个填，但是写不动，没有清晰的思路。
    首先，n个正整数，按题目的约束来，已确认了首尾的奇偶性的情况下(奇/偶)，有多少种排列？
    若n为奇数，则为⌈n/2⌉! * ⌊n/2⌋!，
    若n为偶数，则为⌊n/2⌋! * ⌊n/2⌋!，
    预先递推地计算种数，
    f[0] = 1，f[1] = f[0] * 1, f[2] = f[1] * 1，相比上一项乘的数分别是1 1 2 2 3 3 ...
    然后，要填i时，先看用后面的n-1-i个数有多少种排法，无论ans[i]选的是谁，每组都是f[n-1-i]个，
    先算组大小size，然后k/size是组号，k%size是k'，然后问题递归为(i + 1, k')。
    */
    vector<int> permute(int n, long long k) {
        if (n < f.size() && f[n] * (2 - n % 2) < k) return {};
        k--; // 把k改成从0开始
        // 先把奇偶数都放数组里
        vector<int> cand[2];
        for (int i = 2; i <= n; i += 2) cand[0].push_back(i);
        for (int i = 1; i <= n; i += 2) cand[1].push_back(i);

        vector<int> ans(n);

        int parity = 1; // 当前要填的位置的奇偶性
        for (int i = 0; i < n; i++) { // 一位位填
            /* 例如当前填ans[0]，那么后面有n-1个数字，算这n-1位的情况下，有多少种方案，记为size，
            那么，每size就分为一组，先算组号，然后求余数就是新的k，这样就变成(i + 1, k')的问题，然后
            继续填下去
            */
            int j = 0;
            if (n - 1 - i < f.size()) {
                long long size = f[n - 1 - i]; // 这里提示要判断n - 1 - i < f.size()
                j = k / size; // 组号
                k = k % size; // k'
                // i==0，n为偶的话，首位有2种情况，既可以已奇数启动，也可以以偶数启动，要确认首位的parity
                if (i == 0 && n % 2 == 0) {
                    parity = 1 - j % 2; // 如果组号为奇数，则ans[0]为偶，反之为奇
                    j /= 2;
                }
            }
            
            // 循环开始的部分，若n - 1 - i > f.size()，说明n很大，这时j应为0，前面每次填最小的头元素，直至耗完才开始算中间位置到底在哪。
            ans[i] = cand[parity][j];
            cand[parity].erase(cand[parity].begin() + j);
            parity ^= 1;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3470 solu;
    // auto a = solu.permute(4, 6);
    auto b = solu.permute(33, 444242051606221);
    return 0;
}