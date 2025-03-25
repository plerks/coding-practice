/*
url: https://leetcode.cn/problems/number-of-smooth-descent-periods-of-a-stock/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2110 {
public:
    long long getDescentPeriods(vector<int>& prices) {
        int n = prices.size();
        long long ans = 0;
        for (int i = 0; i < n;) {
            int start = i;
            for (i++; i < n && prices[i] == prices[i - 1] - 1; i++);
            // [start, i)的非空子数组个数
            int len = i - start;
            ans += 1LL * (1 + len) * len / 2;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2110 solu;
    cout << solu.getDescentPeriods(*new vector<int>{3,2,1,4}) << endl;
    return 0;
}