/*
url: https://leetcode.cn/problems/make-lexicographically-smallest-array-by-swapping-elements/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2948 {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        // 用标号数组排序后，相近的(abs <= limit)可以作为一个连通块，然后把这些相连的元素按大小顺序排
        int n = nums.size();
        vector<int> idx(n);
        iota(idx.begin(), idx.end(), 0);
        sort(idx.begin(), idx.end(), [&](const int x, const int y) {
            return nums[x] < nums[y];
        });
        vector<int> ans(n);
        for (int i = 0; i < n;) {
            int start = i;
            for (i++; i < n && abs(nums[idx[i]] - nums[idx[i - 1]]) <= limit; i++);
            vector<int> ordered_pos(idx.begin() + start, idx.begin() + i);
            sort(ordered_pos.begin(), ordered_pos.end());
            for (int j = start; j < i; j++) {
                ans[ordered_pos[j - start]] = nums[idx[j]];
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2948 solu;
    auto a = solu.lexicographicallySmallestArray(*new vector<int>{1,5,3,9,8}, 2);
    return 0;
}