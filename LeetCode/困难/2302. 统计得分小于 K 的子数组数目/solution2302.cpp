/*
url: https://leetcode.cn/problems/count-subarrays-with-score-less-than-k/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2302 {
public:
    // 这题力扣标的是困难，不过是中等题难度
    long long countSubarrays(vector<int>& nums, long long k) {
        int n = nums.size();
        long long sum = 0;
        long long ans = 0;
        for (int l = 0, r = 0; r < n; r++) {
            sum += nums[r];
            while (sum * (r - l + 1) >= k) {
                sum -= nums[l];
                l++;
            }
            ans += r - l + 1;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2302 solu;
    cout << solu.countSubarrays(*new vector<int>{2,1,4,3,5}, 10) << endl;
    return 0;
}