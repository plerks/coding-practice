/*
url: https://leetcode.cn/problems/minimum-number-of-operations-to-make-array-xor-equal-to-k/
标签: 【算法题单】位运算
*/

#include <bits/stdc++.h>

using namespace std;

class Solution2997 {
public:
    int minOperations(vector<int>& nums, int k) {
        int a = 0;
        for (auto& x : nums) a ^= x;
        a ^= k;
        return __builtin_popcount(a);
    }
};

int main(int argc, char const *argv[]) {
    Solution2997 solu;
    cout << solu.minOperations(*new vector<int>{2,1,3,4}, 1) << endl;
    return 0;
}