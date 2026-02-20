/*
url: https://leetcode.cn/problems/house-robber-v/
标签: LeetCode第176场双周赛
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3840 {
public:
    long long rob(vector<int>& nums, vector<int>& colors) {
        int n = nums.size();
        vector<long long> f(n);
        f[0] = nums[0];
        for (int i = 1; i < n; i++) {
            if (colors[i - 1] == colors[i]) {
                f[i] = max({f[i], f[i - 1], (i - 2 < 0 ? 0 : f[i - 2]) + nums[i]});
            }
            else {
                f[i] = max(f[i], f[i - 1] + nums[i]);
            }
        }
        return f[n - 1];
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}