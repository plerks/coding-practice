// https://leetcode.cn/problems/minimum-operations-to-exceed-threshold-value-i/?envType=daily-question&envId=2025-01-14
#include <bits/stdc++.h>

using namespace std;

class Solution3065 {
public:
    int minOperations(vector<int>& nums, int k) {
        int ans = 0;
        for (int x : nums) ans += x < k;
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}