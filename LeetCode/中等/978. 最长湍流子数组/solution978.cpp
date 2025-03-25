/*
url: https://leetcode.cn/problems/longest-turbulent-subarray/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution978 {
public:
    int maxTurbulenceSize(vector<int>& arr) {
        int n = arr.size();
        if (n == 1) return 1;
        int ans = 1;
        for (int i = 0; i < n;) {
            while (i + 1 < n && arr[i + 1] == arr[i]) i++; // 相同元素要跳过
            int start = i;
            if (i + 1 == n) break;
            for (i++; i + 1 < n && 1LL * (arr[i + 1] - arr[i]) * (arr[i] - arr[i - 1]) < 0; i++); // 判断 i + 1 能否加入，不能的话继续从i开始
            ans = max(ans, i - start + 1);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution978 solu;
    // cout << solu.maxTurbulenceSize(*new vector<int>{9,4,2,10,7,8,8,1,9}) << endl;
    // cout << solu.maxTurbulenceSize(*new vector<int>{100}) << endl;
    cout << solu.maxTurbulenceSize(*new vector<int>{9, 9}) << endl;
    return 0;
}