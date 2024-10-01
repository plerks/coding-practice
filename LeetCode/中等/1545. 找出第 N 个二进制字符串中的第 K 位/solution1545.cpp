/*
url: https://leetcode.cn/problems/find-kth-bit-in-nth-binary-string/
相关: LeetCode779. 第K个语法符号, LeetCode3307. 找出第 K 个字符 II
*/

#include <bits/stdc++.h>

using namespace std;

class Solution1545 {
public:
    char findKthBit(int n, int k) {
        if (n == 1) return '0';
        // n和k都从1开始，第i行的长度为2^i - 1
        int m = 1 << (n - 1); // 正中间的编号
        if (k == m) return '1';
        if (k > m) { // 右边
            return ((findKthBit(n - 1, (1 << n) - k) - '0') ^ 1) + '0';
        }
        else { // 左边
            return findKthBit(n - 1, k);
        }
    }
};

int main(int argc, char const *argv[]) {
    Solution1545 solu;
    cout << solu.findKthBit(4, 11) << endl;
    return 0;
}
