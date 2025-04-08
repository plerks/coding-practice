/*
url: https://leetcode.cn/problems/maximum-value-at-a-given-index-in-a-bounded-array/
标签: 【题单】二分算法
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1802 {
public:
    int maxValue(int n, int index, int maxSum) {
        auto check = [&](int x) {
            long long d1 = min(index, x - 1); // 左侧能单减的次数，和为 x - d1, x - d1 + 1, ... x - 1 相加，剩余[0, index - d1)全1
            long long d2 = min(n - index - 1, x - 1); // x - d2, x - d2 + 1, ... x - 1 相加，剩余 n - index - 1 - d2 个1
            long long sum = index - d1 + (2 * x - d1 - 1) * d1 / 2 + x + (2 * x - d2 - 1) * d2 / 2 + n - index - 1 - d2;
            return sum <= maxSum;
        };

        int left = 1, right = maxSum;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (check(mid)) left = mid + 1;
            else right = mid - 1;
        }
        return right;
    }
};

int main(int argc, char const *argv[]) {
    Solution1802 solu;
    // cout << solu.maxValue(4, 2, 6) << endl;
    cout << solu.maxValue(6, 1, 10) << endl;
    return 0;
}