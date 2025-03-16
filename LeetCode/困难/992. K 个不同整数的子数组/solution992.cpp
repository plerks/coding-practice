/*
url: https://leetcode.cn/problems/subarrays-with-k-different-integers/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution992 {
public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        // {>= k} - {>= k+1}
        int n = nums.size();
        int l1 = 0, l2 = 0;
        unordered_map<int, int> mp1;
        unordered_map<int, int> mp2;
        int ans = 0;
        for (int r = 0; r < n; r++) {
            mp1[nums[r]]++;
            mp2[nums[r]]++;
            while (mp1.size() >= k) {
                mp1[nums[l1]]--;
                if (mp1[nums[l1]] == 0) mp1.erase(nums[l1]);
                l1++;
            }
            while (mp2.size() >= k + 1) {
                mp2[nums[l2]]--;
                if (mp2[nums[l2]] == 0) mp2.erase(nums[l2]);
                l2++;
            }
            ans += l1 - l2;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution992 solu;
    cout << solu.subarraysWithKDistinct(*new vector<int>{1,2,1,2,3}, 2) << endl;
    return 0;
}