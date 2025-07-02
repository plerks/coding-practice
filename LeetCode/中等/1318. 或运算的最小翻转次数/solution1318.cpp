/*
url: https://leetcode.cn/problems/minimum-flips-to-make-a-or-b-equal-to-c/
标签: 【算法题单】位运算
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1318 {
public:
    int minFlips(int a, int b, int c) {
        int ans = 0;
        for (int i = 0; i < 32; i++) {
            int p = (a >> i) & 1;
            int q = (b >> i) & 1;
            int r = (c >> i) & 1;
            if (r == 0) {
                ans += p + q;
            }
            else ans += (p | q) == 0;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1318 solu;
    cout << solu.minFlips(2, 6, 5) << endl;
    return 0;
}