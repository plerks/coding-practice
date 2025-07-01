/*
url: https://leetcode.cn/problems/maximum-xor-after-operations/
相关: LeetCode2527. 查询数组异或美丽值
标签: 【算法题单】位运算, 拆位
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2317 {
public:
    /* 要让nums中所有元素的异或最大，那么要让所有位尽量为1。
    nums[i] AND (nums[i] XOR x)的操作可以让某一位变1吗？
    可以， nums[i] == 1 && (nums[i] XOR x) == 1，x可以任意，操作可以任意次数地做。
    于是，想让nums[i]某一位为0，则随时可以取x办到；想让某一位为1，则只需原本那一位为1。
    所以，最大值为nums中元素，所有有1出现过的位置全变为1。
    */
    int maximumXOR(vector<int>& nums) {
        int ans = 0;
        for (int &x : nums) {
            for (int i = 0; i < 32; i++) {
                ans |= x & (1 << i);
            }
        }
        return ans;
    }

    // 算的时候不需要按位来，可以一起做
    int maximumXOR_implementation2(vector<int>& nums) {
        int ans = 0;
        for (int &x : nums) {
            ans |= x;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2317 solu;
    cout << solu.maximumXOR(*new vector<int>{3,2,4,6}) << endl;

    cout << solu.maximumXOR_implementation2(*new vector<int>{3,2,4,6}) << endl;
    return 0;
}