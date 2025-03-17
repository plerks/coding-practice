/*
url: https://leetcode.cn/problems/sum-of-square-numbers/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution633 {
public:
    bool judgeSquareSum(int c) {
        long long l = 0, r = sqrt(c);
        while (l <= r) {
            if (l * l + r * r == c) return true;
            if (l * l + r * r < c) l++;
            else r--;
        }
        return false;
    }
};

int main(int argc, char const *argv[]) {
    Solution633 solu;
    cout << solu.judgeSquareSum(5) << endl;
    return 0;
}