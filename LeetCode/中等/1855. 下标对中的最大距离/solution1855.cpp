/*
url: https://leetcode.cn/problems/maximum-distance-between-a-pair-of-values/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1855 {
public:
    int maxDistance(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size(), n2 = nums2.size();
        int l1 = 0, l2 = 0;
        int ans = 0;
        while (l1 < n1 && l2 < n2) {
            if (nums1[l1] <= nums2[l2]) {
                ans = max(ans, l2 - l1);
                l2++;
            }
            else {
                l1++;
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1855 solu;
    cout << solu.maxDistance(*new vector<int>{55,30,5,4,2}, *new vector<int>{100,20,10,10,5}) << endl;
    return 0;
}