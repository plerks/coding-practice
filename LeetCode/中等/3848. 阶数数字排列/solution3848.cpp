/*
url: https://leetcode.cn/problems/check-digitorial-permutation/
标签: LeetCode第490场周赛
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3848 {
public:
    bool isDigitorialPermutation(int n) {
        int t = n;
        vector<int> fac(10, 1);
        for (int i = 1; i < 10; i++) {
            fac[i] = fac[i - 1] * i;
        }
        long long s = 0;
        while (n > 0) {
            int x = n % 10;
            s += fac[x];
            n /= 10;
        }
        vector<int> mp1(10);
        vector<int> mp2(10);
        while (s > 0) {
            int x = s % 10;
            mp1[x]++;
            s /= 10;
        }
        while (t > 0) {
            int x = t % 10;
            mp2[x]++;
            t /= 10;
        }
        for (int i = 0; i < 10; i++) if (mp1[i] != mp2[i]) return false;
        return true;
    }

    /*
    这题也可以打表，具体见灵茶题解，9! = 362880 ，
    后续即使 n = 999... ，增加一位 9，阶乘之和也只增加 362880，但 n 的值却乘 10 了，
    所以只有有限个数是符合 所有位数的阶乘之和等于数字本身 的，7 个 9 时，362880 * 9 就 < 9999999 了。
    最后打表出来只有 1,2,145,40558 这 4 个数以及其排列是符合的。
    */
};

int main(int argc, char const *argv[]) {
    return 0;
}