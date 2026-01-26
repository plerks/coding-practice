/*
url: https://leetcode.cn/problems/find-nth-smallest-integer-with-k-one-bits/
参考: https://leetcode.cn/problems/find-nth-smallest-integer-with-k-one-bits/solutions/3888450/shi-tian-fa-zu-he-shu-xue-pythonjavacgo-d099n/
      https://www.bilibili.com/video/BV1W2zQBnE3g/
标签: LeetCode第486场周赛, Gosper's Hack
*/

// 这次周赛3题，但是这次周赛题简单

#include <bits/stdc++.h>

using namespace std;

constexpr int MX = 50; // 可以取等到的最大范围
long long comb[MX + 1][MX + 1];
auto init = [] {
    // 用 C_{n}^{m} = C_{n - 1}^{m - 1} + C_{n - 1}^{m} 递推预处理组合数
    for (int i = 0; i <= MX; i++) {
        comb[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
        }
    }
    return 0;
}();

class Solution3821 {
public:
    /* 参考灵茶题解，试填法。

    从高位到低位看，如果当前位填 0，右边还有 p 个位，如果当前还剩 q 个 1，则有 C_{p}^{q} 个数，如果这 < n，则说明不能填 0 ，方案数不够
    要填1。
    问题变为对剩下的部分找第 n - C_{p}^{q} 个数，此外，1 的个数也用了 1 个

    用有2个二进制1的数来看：
    0011
    0101
    0110
    1001
    1010
    看 2^3 位置是否为 1 ，就是要看上面 2^3 位置填 0 的时候，个数够不够 k 个。
    也就是 < 2^3 的合法数的个数是 < n 还是 >= n (ans 在上面，也就是说 ans < 2^3)

    试填法相当于在考虑 ans < 2^i / ans >= 2^i 这样的二分方式。

    此外视频题解里提了个估计组合数的技巧，(1 + 1)^n 做二项式展开可得 2^n >= C_{n}^{i}，这题 n 的范围为 50，所以 C_{n}^{i} <= 2^50，
    这里预处理组合数不会爆 long long。

    这题第一反应是Gosper's Hack，但是用不上，这题 n <= 2^50，用Gosper's Hack直接模拟会超时，问题还是最终归到了"求第几大/小可以二分"的题目类型上了。
    */
    long long nthSmallest(long long n, int k) {
        long long ans = 0;
        for (int i = 50; i >= 0; i--) {
            long long c = comb[i][k]; // 第 i 位填 0，右边能组合出多少个数
            if (c < n) { // 不够，必须填 1
                ans |= 1LL << i;
                n -= c;
                k--;
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution3821 solu;
    cout << solu.nthSmallest(4, 1) << endl;
    return 0;
}