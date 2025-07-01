/*
url: https://leetcode.cn/problems/xor-operation-in-an-array/
标签: 【算法题单】位运算, 异或的性质
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1486 {
public:
    /* 参考灵茶题解，没想出来怎么O(1)，这个解法很妙。
    要计算的值为 start ^ (start + 2) ^ (start + 4) ^ ... ^ (start + 2 * (n - 1))。奇偶性都是相同的。
    最后一位的值取决于：若start为偶数，则最后一位为0，若start为奇数，则最后一位取决于n的奇偶性，n % 2。
    确定最后一位的值b后，把上述的值都 / 2，并记 a = ⌊start / 2⌋，则答案为 a ^ (a + 1) ^ ... ^ (a + n - 1)。
    这是连续n个数的异或和，再变一下，变成求 0 ^ .. ^ a ^ (a + 1) ^ ... ^ (a + n - 1) ^ (0 ^ ... ^ (a - 1))，
    这是因为任何数 x ^ x = 0，而0是异或的单位元，也就是说对于异或运算 x 的逆元为 x。
    然后变成求 0 ^ ... ^ n，怎么求？
    若 x 为偶数，则 x ^ (x + 1) = 1，于是 x ^ (x + 1) ^ (x + 2) ^ (x + 3) = 1 ^ 1 = 0，从一个偶数开始，每4个数就会变成单位元0。
    [0, n]共n + 1个数，
    当 (n + 1) % 4分别为 0, 1, 2, 3 时，n分别为 4k - 1, 4k, 4k + 1, 4k + 2 (奇 偶 奇 偶)
    结果分别为:
        0
        n
        (n - 1) ^ n = 偶 ^ (偶 + 1) = 1
        (n - 2) ^ (n - 1) ^ n = 1 ^ 偶 = n + 1
    
    ans为xor([0,a + n - 1]) ^ xor([0, a - 1]) * 2 + b
    */
    int xorOperation(int n, int start) {
        int a = start / 2;
        int b = start & n & 1; // start和n都是奇数时b才为1
        return (xor_n(a + n - 1) ^ xor_n(a - 1)) * 2 + b;
    }

    // 求[0, n]的异或值
    int xor_n(int n) {
        switch ((n + 1) % 4) {
            case 0: return 0;
            case 1: return n;
            case 2: return 1;
            case 3: return n + 1;
        }
        return -1;
    }
};

int main(int argc, char const *argv[]) {
    Solution1486 solu;
    cout << solu.xorOperation(4, 3) << endl;
    cout << solu.xorOperation(1, 7) << endl;
    return 0;
}