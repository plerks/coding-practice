/*
url: https://leetcode.cn/problems/element-appearing-more-than-25-in-sorted-array/
相关: LeetCode162. 寻找峰值
标签: 【题单】二分算法
*/
#include <bits/stdc++.h>

using namespace std;

// 这题和LeetCode162. 寻找峰值有点像，属于居然能优化到logn的，都不需要一次线性遍历知道各个值
class Solution1287 {
public:
    /* 参考灵茶题解，O(logn)的做法，题目arr有序，寻找出现频率超过25%的唯一数，则出现次数要>=⌊n/4⌋ + 1，
    记m = ⌊n/4⌋，把arr分成4段 [0, m - 1] m [m + 1, 2m] 2m+1 [2m+2, 3m+1] 3m+2 [3m+3, n]，每段
    的长度为m，则ans一定会出现在在m, 2m + 1, 3m + 2之一。于是，对arr[m]，arr[2m + 1]二分求左右边界，看
    出现次数是否>=⌊n/4⌋ + 1，若都不是，则arr[3m + 2]为ans。再优化，只需二分求左边界，然后看arr[l + m]
    是否为x。且l + m不用考虑可能>n，题目保证答案存在，从左到右遍历的，一定不会越界。
    */
    int findSpecialInteger(vector<int>& arr) {
        int m = arr.size() / 4;
        for (int p : {m, 2 * m + 1}) {
            int x = arr[p];
            // 第一个>=x的位置
            int l = lower_bound(arr.begin(), arr.end(), x) - arr.begin();
            if (arr[l + m] == x) return x;
        }
        return arr[3 * m + 2];
    }
};

int main(int argc, char const *argv[]) {
    Solution1287 solu;
    cout << solu.findSpecialInteger(*new vector<int>{1,2,2,6,6,6,6,7,10}) << endl;
    return 0;
}