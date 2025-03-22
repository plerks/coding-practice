/*
url: https://leetcode.cn/problems/shortest-subarray-to-be-removed-to-make-array-sorted/
相关: LeetCode2972. 统计移除递增子数组的数目 II
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1574 {
public:
    // 我的解法，二分，时间复杂度O(nlogn)
    int findLengthOfShortestSubarray(vector<int>& arr) {
        int n = arr.size();
        int l = 1, r = n - 2;
        while (l < n && arr[l] >= arr[l - 1]) l++;
        while (r >= 0 && arr[r] <= arr[r + 1]) r--;
        // [0, l - 1]是单增前缀，[r + 1, n - 1]是单增后缀
        if (l - 1 >= r + 1) return 0;
        int ans = n - (r + 1);
        for (int i = l - 1; i >= 0; i--) {
            int x = arr[i];
            // 后缀第一个>=x
            int index = lower_bound(arr.begin() + r + 1, arr.end(), x) - arr.begin();
            ans = max(ans, i + 1 + n - index);
        }
        return n - ans;
    }

    // 参考灵茶题解，双指针，时间复杂度O(n)，不过也要把单增的前缀和后缀找出来
    int findLengthOfShortestSubarray_implementation2(vector<int>& arr) {
        int n = arr.size();
        int r = n - 1;
        while (r > 0 && arr[r - 1] <= arr[r]) r--;
        // [r, n)是单增后缀
        if (r == 0) return 0;
        int ans = r; // 删除[0, r)的情况
        for (int l = 0; l == 0 || arr[l - 1] <= arr[l]; l++) {
            while (r < n && arr[r] < arr[l]) r++;
            // 删除[l + 1, r)
            ans = min(ans, r - l - 1);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1574 solu;
    cout << solu.findLengthOfShortestSubarray(*new vector<int>{1,2,3,10,4,2,3,5}) << endl;
    cout << solu.findLengthOfShortestSubarray_implementation2(*new vector<int>{1,2,3,10,4,2,3,5}) << endl;
    return 0;
}