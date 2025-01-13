// https://leetcode.cn/problems/number-of-ways-to-split-array/description/?envType=daily-question&envId=2025-01-13

#include <bits/stdc++.h>

using namespace std;

class Solution2270 {
public:
    int waysToSplitArray(vector<int>& nums) {
        int n = nums.size();
        long long total = accumulate(nums.begin(), nums.end(), 0LL);
        long long pre = 0;
        int ans = 0;
        for (int i = 0; i <= n - 2; i++) {
            pre += nums[i];
            if (pre >= total - pre) ans++;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2270 solu;
    cout << solu.waysToSplitArray(*new vector<int>{10,4,-8,7}) << endl;
    return 0;
}