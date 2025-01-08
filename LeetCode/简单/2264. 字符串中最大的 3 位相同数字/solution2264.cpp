// https://leetcode.cn/problems/largest-3-same-digit-number-in-string/description/?envType=daily-question&envId=2025-01-08

#include <bits/stdc++.h>

using namespace std;

class Solution2264 {
public:
    string largestGoodInteger(string num) {
        int n = num.size();
        vector<int> dp(n, 1); // dp[i]表示从num[i]往左最长的相同字符长度
        string ans = "";
        // 枚举右边界
        for (int i = 1; i < n; i++) {
            dp[i] = num[i] == num[i - 1] ? dp[i - 1] + 1 : 1;
            if (dp[i] >= 3) {
                ans = max(ans, num.substr(i - 2, 3));
            }
        }
        return ans;
        // 这样做即使题目要求重复长度 >> 3 的子串的最大值，时间复杂度也是O(n)
    }
};

int main(int argc, char const *argv[]) {
    Solution2264 solu;
    cout << solu.largestGoodInteger("6777133339") << endl;
    return 0;
}