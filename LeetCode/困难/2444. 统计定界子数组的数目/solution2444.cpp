/*
url: https://leetcode.cn/problems/count-subarrays-with-fixed-bounds/
相关: LeetCode795. 区间子数组个数
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2444 {
public:
    long long countSubarrays(vector<int>& nums, int minK, int maxK) {
        int n = nums.size();
        int p = -1; // p代表最右一个< minK || > maxK的位置
        int p1 = -1, p2 = -1; // p1, p2代表最右一个minK，maxK的位置
        long long ans = 0;
        for (int r = 0; r < n; r++) {
            if (nums[r] < minK || nums[r] > maxK) p = r;
            if (nums[r] == minK) p1 = r;
            if (nums[r] == maxK) p2 = r;
            // 左端点的范围: (p, min(p1, p2)]
            ans += max(0, min(p1, p2) - p);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2444 solu;
    cout << solu.countSubarrays(*new vector<int>{1,3,5,2,7,5}, 1, 5) << endl;
    return 0;
}