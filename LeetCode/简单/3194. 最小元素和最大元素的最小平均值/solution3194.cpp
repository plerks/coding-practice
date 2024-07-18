/*
url: https://leetcode.cn/problems/minimum-average-of-smallest-and-largest-elements/
标签: LeetCode第403场周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3194 {
public:
    double minimumAverage(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        double ans = 1000;
        for (int i = 0; i < n / 2; i++) {
            ans = min(ans, (nums[i] + nums[n - 1 - i]) / 2.0); // 这里可以改下，最后再除以2，避免中途用浮点数
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}
