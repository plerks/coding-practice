/*
url: https://leetcode.cn/problems/minimum-numbers-of-function-calls-to-make-target-array/
标签: 【算法题单】位运算
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1558 {
public:
    // nums[i]里的1是通过 +1 弄出来的，位长是移位出来的
    // 把nums[i]补前置0变成最长的那个，然后每轮：step1: 每个数是否要加1？ step2: 移位
    int minOperations(vector<int>& nums) {
        int ans = 0;
        int mx = 0;
        for (int x : nums) {
            ans += __builtin_popcount(x);
            mx = max(mx, __lg(x) + 1); // 最大位长
        }
        return max(0, ans + (mx - 1));
    }
};

int main(int argc, char const *argv[]) {
    Solution1558 solu;
    cout << solu.minOperations(*new vector<int>{1,5}) << endl;
    cout << solu.minOperations(*new vector<int>{0}) << endl;
    return 0;
}