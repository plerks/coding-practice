/*
url: https://leetcode.cn/problems/special-array-i/description/
标签: LeetCode第398场周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3151 {
public:
    bool isArraySpecial(vector<int>& nums) {
        int n = nums.size();
        int r = nums[0] % 2;
        for (int i = 1; i < n; i++) {
            if (nums[i] % 2 == r) return false;
            else {
                r = nums[i] % 2;
            }
        }
        return true;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}
