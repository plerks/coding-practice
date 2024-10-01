/*
url: https://leetcode.cn/problems/minimum-element-after-replacement-with-digit-sum/description/
标签: LeetCode第140场双周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3300 {
public:
    int minElement(vector<int>& nums) {
        int ans = INT_MAX;
        for (int x : nums) {
            int sum = 0;
            while (x > 0) {
                sum += x % 10;
                x /= 10;
            }
            ans = min(ans, sum);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}
