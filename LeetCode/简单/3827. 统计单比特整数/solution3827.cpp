/*
url: https://leetcode.cn/problems/count-monobit-integers/
标签: LeetCode第487场周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3827 {
public:
    // 周赛时的写法
    int countMonobit(int n) {
        int ans = 0;
        for (int i = 0; i < 31; i++) {
            if ((1 << i) - 1 <= n) ans++;
        }
        return ans;
    }

    /* 参考灵茶题解，可以写得更优，0 <= 2^i - 1 <= n，则 1 <= 2^i <= n + 1，
    则 0 <= i <= __lg(n + 1)，答案为 __lg(n + 1) + 1，也即 n + 1 的 bit_width
    */
    int countMonobit_impl2(int n) {
        return __lg(n + 1) + 1;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}