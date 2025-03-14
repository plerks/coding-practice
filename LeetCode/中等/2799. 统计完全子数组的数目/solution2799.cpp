/*
url: https://leetcode.cn/problems/count-complete-subarrays-in-an-array/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2799 {
public:
    int countCompleteSubarrays(vector<int>& nums) {
        int n = nums.size();
        unordered_set<int> st(nums.begin(), nums.end());
        int d = st.size();
        int l = 0;
        unordered_map<int, int> mp;
        int ans = 0;
        for (int r = 0; r < n; r++) {
            mp[nums[r]]++;
            while (mp.size() == d) {
                mp[nums[l]]--;
                if (mp[nums[l]] == 0) mp.erase(nums[l]);
                l++;
            }
            ans += l;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2799 solu;
    cout << solu.countCompleteSubarrays(*new vector<int>{1,3,1,2,2}) << endl;
    return 0;
}