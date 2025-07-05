/*
url: https://leetcode.cn/problems/minimum-operations-to-reduce-an-integer-to-0/
参考: https://leetcode.cn/problems/minimum-operations-to-reduce-an-integer-to-0/solutions/2120204/ji-yi-hua-sou-suo-by-endlesscheng-cm6l/
标签: 【算法题单】位运算
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2571 {
public:
    // n分成多个"1"块，每个块，若长度为1则1次，若长度 > 1则2次
    // 但是这样不对，54 = 110110，把中间0加成1，总共3次操作就行了。
    // 灵茶题解解法一，若最后一段的1长度 == 1，-lowbit；> 1，+lowbit
    int minOperations(int n) {
        int ans = 0;
        while (n & (n - 1)) { // 不是 2的幂
            int lb = n & -n;
            if (n & (lb << 1)) n += lb;
            else n -= lb;
            ans++;
        }
        return ans + 1;
        // 或者:
        /* int ans = 0;
        while (n > 0) {
            int lb = n & -n;
            if (n & (lb << 1)) n += lb;
            else n -= lb;
            ans++;
        }
        return ans; */
    }

    /* 灵茶题解解法二，直接返回 3n ^ n 的二进制1个数
    对于最后一段1，如果前面有2个0，例如 00111，3n为10101，异或结果为10010，其中1的个数就是操作次数
    
    但是题解没分析完全最后一段1前面有1个0的情况，例如 ..101111，若前面为00（即00101111），则3n为10001101，异或为10100010，操作次数为3对的，
    但是如果前面为01/10/11之类的呢？这就不好分析了， 3n ^ n 会影响更高的位这一点很难处理。
    不过直接返回 3n ^ n 的二进制1个数仍然是对的。
    */
    int minOperations_implementation2(int n) {
        return __builtin_popcount(3 * n ^ n);
    }
};

int main(int argc, char const *argv[]) {
    Solution2571 solu;
    cout << solu.minOperations(39) << endl;
    cout << solu.minOperations(54) << endl;
    return 0;
}