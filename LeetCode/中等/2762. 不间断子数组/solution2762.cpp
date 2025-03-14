/*
url: https://leetcode.cn/problems/continuous-subarrays/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2762 {
public:
    // 这题用multiset有个问题，如果nums存在大量重复元素，multiset内也会有大量元素，时间复杂度会是O(nlogn)，不如用map
    long long continuousSubarrays(vector<int>& nums) {
        int n = nums.size();
        long long ans = 0;
        multiset<int> st;
        for (int l = 0, r = 0; r < n; r++) {
            st.insert(nums[r]);
            while (*st.rbegin() - *st.begin() > 2) {
                auto it = st.find(nums[l]);
                st.erase(it); // std::multiset，erase(value)会删除所有这个元素，得erase(it)才是只删除一个，是个坑
                l++;
            }
            ans += r - l + 1;
        }
        return ans;
    }

    // 改成用map，map内最多只有3个元素，所以每次l移动的时间复杂度是O(1)级别，总体时间复杂度O(n)
    long long continuousSubarrays_implementation2(vector<int>& nums) {
        int n = nums.size();
        long long ans = 0;
        map<int, int> mp;
        for (int l = 0, r = 0; r < n; r++) {
            mp[nums[r]]++;
            while (mp.rbegin()->first - mp.begin()->first > 2) {
                mp[nums[l]]--;
                if (mp[nums[l]] == 0) mp.erase(nums[l]);
                l++;
            }
            ans += r - l + 1;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2762 solu;
    // cout << solu.continuousSubarrays(*new vector<int>{5,4,2,4}) << endl;
    cout << solu.continuousSubarrays(*new vector<int>{42,41,42,41,41,40,39,38}) << endl;
    cout << solu.continuousSubarrays_implementation2(*new vector<int>{42,41,42,41,41,40,39,38}) << endl;
    return 0;
}