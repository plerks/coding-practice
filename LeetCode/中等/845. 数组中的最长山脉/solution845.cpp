/*
url: https://leetcode.cn/problems/longest-mountain-in-array/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution845 {
public:
    int longestMountain(vector<int>& arr) {
        int n = arr.size();
        int ans = 0;
        for (int i = 0; i < n;) {
            int start = i;
            for (; i + 1 < n && arr[i + 1] > arr[i]; i++); // 先看下一步能否动
            if (i - start == 0) {
                i++;
                continue; // 没启动单增
            }
            int mid = i;
            for (; i + 1 < n && arr[i + 1] < arr[i]; i++);
            if (i - mid == 0) {
                i++;
                continue; // 没启动单减
            }
            ans = max(ans, i - start + 1);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution845 solu;
    cout << solu.longestMountain(*new vector<int>{2,1,4,7,3,2,5}) << endl;
    cout << solu.longestMountain(*new vector<int>{2,3}) << endl;
    return 0;
}