/*
url: https://leetcode.cn/problems/minimum-one-bit-operations-to-make-integers-zero/
参考: https://leetcode.cn/problems/minimum-one-bit-operations-to-make-integers-zero/solutions/435645/hua-shan-yi-tiao-dao-wo-men-di-gui-zhao-zou-by-luc/
      https://leetcode.cn/problems/minimum-one-bit-operations-to-make-integers-zero/solutions/671561/ni-ge-lei-ma-by-mt19937-p3ue/
相关: LeetCode89. 格雷编码
标签: 【算法题单】位运算, 格雷码, 格雷码的反函数
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1611 {
public:
    /* 对这题有些想法，但是不知道该怎么写，
    每次能做的两个操作为，翻转最后一位，或者把x100..00的形式的x翻转
    主要看9这个用例，需要14次，操作序列为
    1001 1011 1010 1110 1111 1101 1100 0100 101 111 110 010 11 1 0
    这个过程能看到变成 1100..00 100..00 的这种形状是比较特殊的，但是不知道该怎么写，
    此外，能看出这个变化过程有格雷码的样子，但是如果去思考求格雷码距离，就要求出一个二进制对应的格雷码编号，而0 <= n <= 10^9，
    想先把格雷码表求出来也不可行。（实际可以直接求逆）
    */

    /* 参考题解解法一，这题有两个子问题，
    1. 把当前数变成0，需要找到最高位的1，然后把右侧变成100..00，然后把最高位1变成0，然后再把100..00变成0，而把100..00变成0的次数
        有规律，2^n 所需的次数是 2^(n + 1) - 1。
        这个规律可以严格证明：
            把100..00变成0的次数极为y(i)，首先，需要把00..00变成10..00，这正是y(i - 1)的逆过程，然后把首位1变成0，然后再把10..00变成0
            y(i) = y(i - 1) + 1 + y(i - 1)，y(0) = 1，所以y(i)为2^(n + 1) - 1
    2. 把当前数变成10..00的形式，如果1对应的位置已经为1，则递归为把后面的数变成0；如果1对应的位置为0，则要把后面变成1..00，然后变成11..00，
        然后把1..00变成0..00 (y)
    */
    int minimumOneBitOperations(int n) {
        return f(n);
    }

    // 把n变成0
    int f(int n) {
        if (n <= 1) return n; // n为0和1的情况
        int t = __lg(n); // 最高位1所在的幂次
        return g(n ^ (1 << t), t - 1) + 1 + (1 << t) - 1;
    }

    // 把n变成10..00 (1 << t)的形式，t + 1为有效位长度，n的有效位长不超过1 << t
    int g(int n, int t) {
        if (t == 0) return 1 - n; // 把 n 变成 1
        if (n & (1 << t)) return f(n ^ (1 << t));
        else return g(n, t - 1) + 1 + (1 << t) - 1;
    }

    /* 参考题解解法二，这题实际是已知格雷码码值n，求其编号(编号从0开始)。
    由LeetCode89：Gray(i) = i ^ (i >> 1)。已知 i ^ (i >> 1) = g 如何求 i ？也就是如何求 Gray 函数的反函数 ？
    首先，
    i的最高位 == g的最高位
    g的第x位 == i的第x位 ^ i的第x + 1位，由异或性质，i的第x位 = i的第x + 1位 ^ g的第x位
    这就导出了由g一位位求i的过程：
    i_k = g_k
    i_{k - 1} = g_{k - 1} ^ i_{k}
    ...
    i_0 = g_0 ^ i_1

    注意以上 i_k 为 i 在第 k 位上的 0/1 值，没算上位权，考虑上位权的话，
    i_k * 2_k = g_k * 2_k
    i_{k - 1} * 2_{k - 1} = (g_{k - 1} * 2_{k - 1}) ^ (i_{k} * 2_{k - 1}) = (g_{k - 1} * 2_{k - 1}) ^ (g_k * 2_k / 2)
    ...

    所以，i的每一位为g的前缀异或（从g的最高位到当前位置，g的每一位都参与异或构成i的这一位）
    i = g ^ (g >> 1) ^ (g >> 2) ^ ...

    时间复杂度为 g 的位长
    */
    int minimumOneBitOperations_implementation2(int g) {
        int i = 0;
        while (g) {
            i = i ^ g;
            g >>= 1;
        }
        return i;
    }
};

int main(int argc, char const *argv[]) {
    Solution1611 solu;
    cout << solu.minimumOneBitOperations(3) << endl;
    cout << solu.minimumOneBitOperations(6) << endl;
    cout << solu.minimumOneBitOperations(9) << endl;

    cout << solu.minimumOneBitOperations_implementation2(3) << endl;
    cout << solu.minimumOneBitOperations_implementation2(6) << endl;
    cout << solu.minimumOneBitOperations_implementation2(9) << endl;
    return 0;
}