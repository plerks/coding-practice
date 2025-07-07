/*
url: https://leetcode.cn/problems/bitwise-and-of-numbers-range/
标签: 【算法题单】位运算
*/
#include <bits/stdc++.h>

using namespace std;

class Solution201 {
public:
    int rangeBitwiseAnd(int left, int right) {
        long long x = left;
        int ans = 0;
        // left中的0一定最后也为0，只需看left中的1
        // left中的最后一个1，最近的一个此位为0的数是多少？left + lb
        while (x) {
            long long lb = x & -x;
            if (x + lb > right) {
                ans |= lb;
            }
            x -= lb;
        }
        return ans;
    }

    // 官方题解解法，思路差不多，不过官方题解的更简洁，且是从right来考虑的。原来清除lowbit的 x & (x - 1) 技巧有名字，叫 Brian Kernighan算法
    int rangeBitwiseAnd_implementation2(int left, int right) {
        while (left < right) { // 区间存在 right - 1，right的lowbit一定保不住
            right = right & (right - 1);
        }
        return right;
    }
};

int main(int argc, char const *argv[]) {
    Solution201 solu;
    cout << solu.rangeBitwiseAnd(5, 7) << endl;
    cout << solu.rangeBitwiseAnd(1, 2147483647) << endl;
    return 0;
}