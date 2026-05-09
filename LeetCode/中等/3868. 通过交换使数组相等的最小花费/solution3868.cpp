// https://leetcode.cn/problems/minimum-cost-to-equalize-arrays-using-swaps/

#include <bits/stdc++.h>

using namespace std;

class Solution3868 {
public:
    int minCost(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> mp1;
        unordered_map<int, int> mp2;
        unordered_map<int, int> mp;
        for (int x : nums1) mp1[x]++, mp[x]++;
        for (int x : nums2) mp2[x]++, mp[x]++;
        for (auto [x, freq] : mp) {
            if (freq % 2 != 0) return -1;
        }
        int ans = 0;
        for (auto [x, freq] : mp) {
            if (mp1[x] > (mp1[x] + mp2[x]) / 2) {
                ans += mp1[x] - (mp1[x] + mp2[x]) / 2;
            }
        }
        return ans;
    }

    // 灵茶题解解法，更简洁
    int minCost_impl2(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        unordered_map<int, int> diff;
        for (int i = 0; i < n; i++) {
            diff[nums1[i]]++;
            diff[nums2[i]]--;
        }
        int ans = 0;
        for (auto [_, d] : diff) {
            if (d % 2) return -1; // 负数取模会是-1 / 0, 不过这里没问题
            if (d > 0) ans += d;
        }
        return ans / 2;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}