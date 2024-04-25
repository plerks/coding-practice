/*
url: https://leetcode.cn/problems/next-greater-numerically-balanced-number/description/
LeetCode参考: https://leetcode.cn/problems/next-greater-numerically-balanced-number/solutions/2555817/xia-yi-ge-geng-da-de-shu-zhi-ping-heng-s-rm9d/
*/

#include <bits/stdc++.h>

using namespace std;

// 逆天，还以为有什么特殊技巧可以直接求出下一个>n的数值平衡数，结果官方题解一个解法直接暴力枚举，另一个解法直接打表数值平衡数，然后二分查找
class Solution2048 {
public:
    // 暴力枚举每个>n的数
    int nextBeautifulNumber(int n) {
        for (int i = n + 1;; i++) {
            if (isBeautifulNumber(i)) {
                return i;
            }
        }
        return -1;
    }

    bool isBeautifulNumber(int x) {
        int count[10] = {0};
        string s = to_string(x);
        for (char c : s) {
            int digit = c - '0';
            count[digit]++;
            if (count[digit] > digit) return false;
        }
        for (int i = 0; i < 10; i++) {
            if (count[i] > 0 && count[i] != i) return false;
        }
        return true;
    }
};

int main(int argc, char const *argv[]) {
    Solution2048 solu;
    cout << solu.nextBeautifulNumber(1000) << endl;
    return 0;
}
