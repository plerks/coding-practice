/*
url: https://leetcode.cn/problems/rotate-non-negative-elements/
标签: LeetCode第486场周赛
*/
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    // 周赛时候的写法
    vector<int> rotateElements(vector<int>& nums, int k) {
        int n = nums.size();
        vector<pair<int, int>> negative;
        vector<int> positive;
        for (int i = 0; i < n; i++) {
            if (nums[i] < 0) negative.push_back({nums[i], i}); // (-, 位置)
            else {
                positive.push_back(nums[i]);
            }
        }
        vector<int> shift(positive.size());
        for (int i = 0; i < positive.size(); i++) {
            int sz = positive.size();
            int t = (i - (k % sz) + sz) % sz;
            shift[(i - (k % sz) + sz) % sz] = positive[i];
        }
        for (int i = 0; i < negative.size(); i++) {
            auto [x, p] = negative[i];
            shift.insert(shift.begin() + p, x);
        }
        return shift;
    }

    // 灵茶题解的简洁写法
    vector<int> rotateElements_implementation2(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> a;
        for (int i = 0; i < n; i++) {
            if (nums[i] >= 0) a.push_back(nums[i]);
        }
        if (a.empty()) return nums;
        // 用库函数旋转
        std::rotate(a.begin(), a.begin() + (k % a.size()), a.end());
        int j = 0;
        for (int& x : nums) {
            if (x < 0) continue;
            x = a[j++];
        }
        return nums;
    }

    // 灵茶题解简洁写法二，不用旋转，直接从选出来的非负数的第 k 个位置开始往回放就行
    vector<int> rotateElements_implementation2(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> a;
        for (int i = 0; i < n; i++) {
            if (nums[i] >= 0) a.push_back(nums[i]);
        }
        if (a.empty()) return nums;
        int j = k;
        for (int& x : nums) {
            if (x < 0) continue;
            x = a[j++ % a.size()];
        }
        return nums;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}