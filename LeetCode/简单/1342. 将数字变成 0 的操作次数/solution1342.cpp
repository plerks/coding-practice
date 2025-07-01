/*
url: https://leetcode.cn/problems/number-of-steps-to-reduce-a-number-to-zero/
标签: 【算法题单】位运算
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1342 {
public:
    int numberOfSteps(int num) {
        if (num == 0) return 0;
        return 32 - __builtin_clz(num) - 1 + __builtin_popcount(num);
    }
};

int main(int argc, char const *argv[]) {
    Solution1342 solu;
    cout << solu.numberOfSteps(14) << endl;
    return 0;
}