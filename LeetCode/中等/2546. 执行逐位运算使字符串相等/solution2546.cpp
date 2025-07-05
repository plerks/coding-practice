/*
url: https://leetcode.cn/problems/apply-bitwise-operations-to-make-strings-equal/
标签: 【算法题单】位运算
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2546 {
public:
    /*
    选 0 <= i, j < n，
    0 0 -> 0 0
    0 1 -> 1 1
    1 0 -> 1 1
    1 1 -> 1 0

    0 1 -> 1 1 可以增加1
    1 1 -> 1 0 可以减少1 (增加0)
    0 1 -> 1 1 -> 1 0 可以交换 0 1

    由于 i, j 可以任选，可以当成s和target，1全在一边，0全在一边。
    若s的1多，可以消，但是最后1个1消除不了
    若s的1少，可以增，但是如果最开始没1就操作不了
    */
    bool makeStringsEqual(string s, string target) {
        int one1 = 0; for (char c : s) one1 += c == '1';
        int one2 = 0; for (char c : target) one2 += c == '1';

        if (one1 == one2) return true;
        else if (one1 > one2) return one2 > 0;
        return one1 > 0;
    }

    // 灵茶题解写法，都有1 或者 都没有1
    bool makeStringsEqual(string s, string target) {
        return (s.find('1') == -1) == (target.find('1') == -1);
    }
};

int main(int argc, char const *argv[]) {
    Solution2546 solu;
    cout << solu.makeStringsEqual("1010", "0110") << endl;
    return 0;
}