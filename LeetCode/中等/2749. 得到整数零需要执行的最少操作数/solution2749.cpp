/*
url: https://leetcode.cn/problems/minimum-operations-to-make-the-integer-zero/
参考: https://leetcode.cn/problems/minimum-operations-to-make-the-integer-zero/solutions/2319632/mei-ju-da-an-pythonjavacgo-by-endlessche-t4co/
标签: 【算法题单】位运算
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2749 {
public:
    /* 参考灵茶题解，一个个枚举答案k，操作k次后，num1变成 num1 - k * num2 - 多个2^i
    问题变成 num1 - k * num2 能否变成k个2的幂之和。
    记x = num1 - k * num2。
    如果 x < 0，不能变成2的幂之和，且1 <= num1 <= 10^9，-10^9 <= num2 <= 10^9，x < 0说明 num2 一定为正，k更大时 x 更负，后面不用试了。
    如果 x < k，即使每次减1，也会让其变成负数，不行
    如果 x 的二进制1个数 > k，不行
    否则，虽然 x 的二进制1个数 <= k，但是把 x 变成0的操作次数最少为 popcount <= k，最多为 x > k (每次减1)，把减popcount
    的操作拆分(例如2^i拆成两个2^(i+1))，能得到刚好为 k 次的方案

    如何控制k的枚举结束？
    num2若为正，则 k > num1 / num2 时，x会变成负数，无需尝试，k > num1 / (num2 + 1) 时，x会变成负数，无需尝试。只需判断后者
    num2若为负，x的二进制1个数的增长是对数的，而k的增长是线性的，一定能发生 x >= k && popcount(x) <= k ，一定有解，且 k * (num2 + 1) > num1 一直为false，会一直尝试下去。
    num2若为0，也是一定有解，且由于 popcount(num1) <= num1 ，一定会在发生 k * (0 + 1) > num1 之前找到解

    时间复杂度：popcount(n1 - k * n2) <= k 会很快发生
    */
    int makeTheIntegerZero(int num1, int num2) {
        for (long long k = 0; k * (num2 + 1) <= num1; k++) {
            long long x = num1 - k * num2;
            if (__builtin_popcountll(x) <= k) return k;
        }
        return -1;
    }
};

int main(int argc, char const *argv[]) {
    Solution2749 solu;
    cout << solu.makeTheIntegerZero(3, -2) << endl;
    return 0;
}