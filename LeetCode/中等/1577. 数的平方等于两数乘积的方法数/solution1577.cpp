/*
url: https://leetcode.cn/problems/number-of-ways-where-square-of-number-is-equal-to-product-of-two-numbers/
相关: LeetCode611. 有效三角形的个数
标签: 【题单】滑动窗口与双指针, 恰好型滑动窗口
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1577 {
public:
    int numTriplets(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size();
        int n2 = nums2.size();
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        int ans = 0;
        for (int x : nums1) { // 可以将x^2去重
            /* 恰好型滑动窗口，{ == x^2 } = { >= x^2 } - { > x^2 }
            */
            int l1 = 0, l2 = 0;
            for (int r = n2 - 1; r > 0; r--) {
                while (l1 < r && (long long)nums2[l1] * nums2[r] < (long long)x * x) l1++;
                while (l2 < r && (long long)nums2[l2] * nums2[r] <= (long long)x * x) l2++;
                /* 相向双指针，当l移动到某一极大位置时，r继续往左，这时有可能l > r（不只是l == r + 1），
                这时要求区间长度，需要与0取max，不能简单用端点相减。
                */
                // [l1, r) - [l2, r)，这个区间的长度为r - l1/l2，由于l1, l2可能>r，r - l1可能为负数，需要与0取max
                ans += max(0, r - l1) - max(0, r - l2);
            }
        }
        for (int x : nums2) {
            int l1 = 0, l2 = 0;
            for (int r = n1 - 1; r > 0; r--) {
                while (l1 < r && (long long)nums1[l1] * nums1[r] < (long long)x * x) l1++;
                while (l2 < r && (long long)nums1[l2] * nums1[r] <= (long long)x * x) l2++;
                ans += max(0, r - l1) - max(0, r - l2);
            }
        }
        return ans;
    }

    /* 尝试改成反向双指针，但是是错的，反向(背向)双指针得是从中间某个位置往两边。以下的过程是
    l从n - 2到0，r往右，但是看[4] [5,2,8,9]这个用例，x^2等于16，一开始l * r = 8 * 9 = 72就大于16！，
    当l减小为2时，r该尝试增大，但是这就错过了 4 * 4 = 2 * 8，这种情况r不是单调增大的。同理，从小到大枚举r，
    l也不一定是单调减小的。反向双指针不能这么写。
    */
    int numTriplets_wa(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size();
        int n2 = nums2.size();
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        int ans = 0;
        for (long long x : nums1) {
            int r1 = n2 - 1, r2 = n2 - 1;
            for (int l = n2 - 2; l >= 0; l--) {
                while (r1 < n2 && (long long)nums2[l] * nums2[r1] < x * x) r1++;
                while (r2 < n2 && (long long)nums2[l] * nums2[r2] <= x * x) r2++;
                // [r1, n) - [r2, n)，这种区间形式不用担心区间长为负的问题，n是虚拟的极大元素，r1不会越过n。但是反向双指针必须是从中间往两边，这题不能这么做
                ans += r2 - r1;
            }
        }
        for (int x : nums2) {
            int r1 = n1 - 1, r2 = n1 - 1;
            for (int l = n1 - 2; l >= 0; l--) {
                while (r1 < n1 && (long long)nums1[l] * nums1[r1] < x * x) r1++;
                while (r2 < n1 && (long long)nums1[l] * nums1[r2] <= x * x) r2++;
                ans += r2 - r1;
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1577 solu;
    // cout << solu.numTriplets(*new vector<int>{7,4}, *new vector<int>{5,2,8,9}) << endl;
    cout << solu.numTriplets(*new vector<int>{1,1}, *new vector<int>{1,1,1}) << endl;

    cout << solu.numTriplets_wa(*new vector<int>{7,4}, *new vector<int>{5,2,8,9}) << endl;
    cout << solu.numTriplets_wa(*new vector<int>{1,1}, *new vector<int>{1,1,1}) << endl;
    return 0;
}