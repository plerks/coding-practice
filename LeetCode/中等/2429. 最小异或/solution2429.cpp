/*
url: https://leetcode.cn/problems/minimize-xor/
标签: 【算法题单】位运算
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2429 {
public:
    int minimizeXor(int num1, int num2) {
        int n1 = __builtin_popcount(num1);
        int n2 = __builtin_popcount(num2);
        if (n1 == n2) return num1;
        if (n1 > n2) { // 消掉头部的1
            int cnt = n2;
            int t = 0;
            for (int i = 31; i >= 0 && cnt > 0; i--) {
                if ((num1 & (1 << i)) >> i) {
                    t |= 1 << i;
                    cnt--;
                }
            }
            return t;
        }
        else { // num1原有的1全部消掉，多余的1尽量往右放
            int cnt = n2 - n1;
            int t = num1;
            for (int i = 0; i < 32 && cnt > 0; i++) {
                if (!((num1 & (1 << i)) >> i)) {
                    t |= 1 << i;
                    cnt--;
                }
            }
            return t;
        }
    }

    // 灵茶题解的简洁写法
    int minimizeXor_implementation2(int num1, int num2) {
        int c1 = __builtin_popcount(num1), c2 = __builtin_popcount(num2);
        for (; c1 < c2; c1++) num1 |= num1 + 1; // 最低位的0变成1
        for (; c2 < c1; c2++) num1 &= num1 - 1;// 最低位的1变成0
        return num1;
    }
};

int main(int argc, char const *argv[]) {
    Solution2429 solu;
    // cout << solu.minimizeXor(3, 5) << endl;
    // cout << solu.minimizeXor(1, 12) << endl;
    // cout << solu.minimizeXor(25, 72) << endl;
    cout << solu.minimizeXor(65, 84) << endl;

    cout << solu.minimizeXor_implementation2(65, 84) << endl;
    return 0;
}