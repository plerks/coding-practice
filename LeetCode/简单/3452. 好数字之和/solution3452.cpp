/*
url: https://leetcode.cn/problems/sum-of-good-numbers/
标签: LeetCode第150场双周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3452 {
public:
    int sumOfGoodNumbers(vector<int>& nums, int k) {
        int n = nums.size();
        int ans = 0;
        for (int i = 0; i < n; i++) {
            bool good1 = false;
            if (i - k < 0 || nums[i] > nums[i - k]) good1 = true;
            bool good2 = false;
            if (i + k >= n || nums[i] > nums[i + k]) good2 = true;
            if (good1 && good2) ans += nums[i];
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}