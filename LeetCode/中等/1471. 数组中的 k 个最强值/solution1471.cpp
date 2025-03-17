/*
url: https://leetcode.cn/problems/the-k-strongest-values-in-an-array/
相关: LeetCode658. 找到 K 个最接近的元素
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1471 {
public:
    vector<int> getStrongest(vector<int>& arr, int k) {
        int n = arr.size();
        sort(arr.begin(), arr.end());
        int l = 0, r = n - 1; // 从两边往中间选，且题目保证k <= n，l, r不会有越界的情况
        int m = arr[(n - 1) >> 1];
        vector<int> ans(k);
        for (int i = 0; i < k; i++) {
            if (abs(arr[r] - m) >= abs(arr[l] - m)) {
                ans[i] = arr[r];
                r--;
            }
            else {
                ans[i] = arr[l];
                l++;
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1471 solu;
    auto a = solu.getStrongest(*new vector<int>{1,2,3,4,5}, 2);
    return 0;
}