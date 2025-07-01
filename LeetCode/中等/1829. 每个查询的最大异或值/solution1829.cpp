/*
url: https://leetcode.cn/problems/maximum-xor-for-each-query/
标签: 【算法题单】位运算
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1829 {
public:
    vector<int> getMaximumXor(vector<int>& nums, int maximumBit) {
        int n = nums.size();
        vector<int> ans(n);
        int mask = (1 << maximumBit) - 1;
        int sum = 0;
        for (int &x : nums) sum ^= x;

        for (int i = 0; i < n; i++) {
            ans[i] = ~sum & mask;
            sum ^= nums[n - 1 - i];
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1829 solu;
    auto a = solu.getMaximumXor(*new vector<int>{0,1,1,3}, 2);
    return 0;
}