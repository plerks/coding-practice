/*
url: https://leetcode.cn/problems/power-of-four/
相关: LeetCode231. 2 的幂
标签: 【算法题单】位运算, 4的幂
*/
#include <bits/stdc++.h>

using namespace std;

class Solution342 {
public:
    bool isPowerOfFour(int n) {
        // 先用LeetCode231的技巧判断是否是2的幂，然后通过一个mask判断1是否在偶数位上
        return n > 0 && ((n & n - 1) == 0) && (n & 0b01010101010101010101010101010101);
    }

    // 参考官方题解，还有个办法是判断 % 3，4^x = (3 + 1)^x，% 3一定为1，而若一个数为4的幂而非2的幂，则其为4^x * 2，% 3一定为2，所以可以区分
    bool isPowerOfFour_implementation2(int n) {
        return n > 0 && ((n & n - 1) == 0) && (n % 3 == 1);
    }
};

int main(int argc, char const *argv[]) {
    Solution342 solu;
    cout << solu.isPowerOfFour(16) << endl;
    return 0;
}