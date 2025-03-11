/*
url: https://leetcode.cn/problems/transform-array-by-parity/
标签: LeetCode第151场双周赛
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3467 {
public:
    // 周赛时的做法，通过，但是不需要排序，直接对奇数偶数计数就好了
    vector<int> transformArray(vector<int>& nums) {
        int n = nums.size();
        for (int &x : nums) {
            if (x % 2 == 0) x = 0;
            else x = 1;
        }
        sort(nums.begin(), nums.end());
        return nums;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}