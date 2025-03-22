/*
url: https://leetcode.cn/problems/shortest-unsorted-continuous-subarray/
标签: 【题单】滑动窗口与双指针, 值域计数, [special]
*/
#include <bits/stdc++.h>

using namespace std;

class Solution581 {
public:
    // 我的解法，值域计数。排序后找第一个不对位置的l, r应该也行
    int findUnsortedSubarray(vector<int>& nums) {
        int n = nums.size();
        vector<int> cnt(2e5 + 1); // -10^5 <= nums[i] <= 10^5
        for (int x : nums) cnt[x + 1e5]++;
        int l = 0, r = n - 1;
        int i = -1e5;
        while (i <= 1e5 && l <= r) {
            if (cnt[i + 1e5] == 0) {
                i++;
            }
            else if (i == nums[l]) {
                cnt[i + 1e5]--;
                l++;
            }
            else break;
        }
        i = 1e5;
        while (i <= 1e5 && l <= r) {
            if (cnt[i + 1e5] == 0) {
                i--;
            }
            else if (i == nums[r]) { // 下一个遇到的数是nums[l]
                cnt[i + 1e5]--;
                r--;
            }
            else break;
        }
        return r - l + 1;
    }

    /* 参考官方题解，以[2,6,4,8,10,9,15]为例，从右到左遍历并记录最小值，当发现6 < 4时，说明4应该换到6的位置，
    最后一个这样的位置即为中间段的l。中间段的r的寻找同理。可以把两次写到同一个循环里。
    这个问题有点特殊。
    */
    int findUnsortedSubarray_implementation2(vector<int>& nums) {
        int n = nums.size();
        int l = 0, r = -1; // 这个初值使得当nums本身就是递增时，结束后l, r不变，并且r - l + 1返回的就是0
        int minn = INT_MAX, maxn = INT_MIN;
        for (int i = 0; i < n; i++) {
            if (nums[i] < maxn) {
                r = i; // 最大值换过来，不用真的换
            }
            else maxn = nums[i];
            
            if (nums[n - 1 - i] > minn) {
                l = n - 1 - i;
            }
            else minn = nums[n - 1 - i];
        }
        return r - l + 1;
    }
};

int main(int argc, char const *argv[]) {
    Solution581 solu;
    // cout << solu.findUnsortedSubarray(*new vector<int>{2,6,4,8,10,9,15}) << endl;
    // cout << solu.findUnsortedSubarray(*new vector<int>{1,2,3,4}) << endl;
    // cout << solu.findUnsortedSubarray(*new vector<int>{1,3,2,4,5}) << endl;
    // cout << solu.findUnsortedSubarray(*new vector<int>{1,2,3,3,3}) << endl;
    cout << solu.findUnsortedSubarray(*new vector<int>{-1,-1,-1,-1}) << endl;

    cout << solu.findUnsortedSubarray_implementation2(*new vector<int>{-1,-1,-1,-1}) << endl;
    return 0;
}