/*
url: https://leetcode.cn/problems/k-th-symbol-in-grammar/
相关: LeetCode3307. 找出第 K 个字符 II, LeetCode1545. 找出第 N 个二进制字符串中的第 K 位
*/

#include <bits/stdc++.h>

using namespace std;

class Solution779 {
public:
    int kthGrammar(int n, int k) {
        if (n == 1) return 0;
        // 第n行的第k个字符由第n - 1行的(k + 1) / 2个字符变来，这题n和k都从1开始
        int x = kthGrammar(n - 1, (k + 1) / 2);
        // 本来是分x是0/1和k的奇偶性，不过可以观察出这个式子
        return (x + (k + 1) % 2) % 2;
    }

    /* [官方题解](https://leetcode.cn/problems/k-th-symbol-in-grammar/solutions/1903508/di-kge-yu-fa-fu-hao-by-leetcode-solution-zgwd/)
    还有两种解法，每行生成的数字都满足：前半部分是后半部分的反转（比如01101001），且每一行的前半部分和上一行相同。
    如果待求的位置在后半部分，则问题变为求前半部分的对应位置的数字再反转一次，然后变为子问题，如果在前半部分，则直接是子问题。
    最终只需要找出反转次数，而结论是反转次数为k - 1中1的个数。和`LeetCode3307. 找出第 K 个字符 II`很像。
    */
};

int main(int argc, char const *argv[]) {
    Solution779 solu;
    cout << solu.kthGrammar(2, 2) << endl;
    return 0;
}
