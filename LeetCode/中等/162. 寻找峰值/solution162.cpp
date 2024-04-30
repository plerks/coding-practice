/*
url: https://leetcode.cn/problems/find-peak-element/description/
相关: LeetCode1901. 寻找峰值 II, 典型问题/有序范围内的二分查找
标签: 二分查找
*/

#include <bits/stdc++.h>

using namespace std;

class Solution162 {
public:
    /* 这题很有意思，有点颠覆认知，二分查找是由于输入有序，所以仅用O(logn)时间就可得出结果，连知晓所有输入值所需的
    O(n)时间都不需要用到。但是这题有关输入的信息比"有序"这一条件还要少，只有nums[-1] = nums[n] = 负无穷，竟然也连
    知晓所有输入值的O(n)时间都不需要。 */
    int findPeakElement(vector<int>& nums) {
        /* 题目要求时间复杂度为O(logn)，肯定需要二分。题目中说可以假设nums[-1] = nums[n] = 负无穷，且元素各不相同
        则中间一定会有个极大值，二分，若mid在邻域内就是极大值，直接返回；若mid在邻域内是极小值，则(-1, mid)和(mid, n)都
        会有个极大值，选一边即可；若mid邻域内单增，则(mid, n)一定有个极大值；若mid邻域内单减，则(-1, mid)一定有个极大值。
        */
        int n = nums.size();
        int left = -1, right = n; // 分析的时候都按开区间写的，试下开区间二分
        while (left + 1 < right) { // 区间不为空
            int mid = (left + right) >> 1;
            if ((mid - 1 < 0 || nums[mid] > nums[mid - 1]) && (mid + 1 >= n || nums[mid] > nums[mid + 1])) {
                return mid;
            }
            else if (mid - 1 >= 0 && mid + 1 < n && nums[mid] < nums[mid - 1] && nums[mid] < nums[mid + 1]) {
                right = mid;
            }
            else if ((mid - 1 < 0 || nums[mid - 1] < nums[mid]) && (mid + 1 >= n || nums[mid] < nums[mid + 1])) {
                left = mid;
            }
            else right = mid;
        }
        return left + 1; // 循环结束时left + 1 == right
    }
};

int main(int argc, char const *argv[]) {
    Solution162 solu;
    vector<int> nums = {1,2,3,1};
    cout << solu.findPeakElement(nums) << endl;
    return 0;
}
