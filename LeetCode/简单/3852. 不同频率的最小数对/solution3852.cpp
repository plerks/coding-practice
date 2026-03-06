/*
url: https://leetcode.cn/problems/smallest-pair-with-different-frequencies/
标签: LeetCode第177场双周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3852 {
public:
    // 双周赛时写的暴力双重循环
    vector<int> minDistinctFreqPair(vector<int>& nums) {
        int n = nums.size();
        map<int, int> mp;
        for (int x : nums) mp[x]++;
        sort(nums.begin(), nums.end());
        pair<int, int> ans = {INT_MAX, INT_MAX};
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int x = nums[i];
                int y = nums[j];
                if (x >= y || mp[x] == mp[y]) continue;
                ans = min(ans, {x, y});
            }
        }
        if (ans == pair<int, int>{INT_MAX, INT_MAX}) return {-1, -1};
        return {ans.first, ans.second};
    }

    // 参考灵茶题解，x 选出现过的最小的那个值，y 选最小的和 freq[x] 不相等的值
    vector<int> minDistinctFreqPair_impl2(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int, int> freq;
        int min_x = INT_MAX;
        for (int x : nums) freq[x]++, min_x = min(x, min_x);
        int min_y = INT_MAX;
        for (auto [y, fq] : freq) {
            if (min_x != y && fq != freq[min_x]) min_y = min(min_y, y);
        }
        if (min_y == INT_MAX) return {-1, -1};
        return {min_x, min_y};
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}