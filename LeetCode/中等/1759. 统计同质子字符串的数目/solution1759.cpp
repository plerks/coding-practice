/*
url: https://leetcode.cn/problems/count-number-of-homogenous-substrings/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1759 {
public:
    int countHomogenous(string s) {
        int n = s.size();
        const int mod = 1e9 + 7;
        long long ans = 0;
        for (int i = 0; i < n;) {
            int start = i;
            for (i++; i < n && s[i] == s[i - 1]; i++);
            int len = i - start;
            ans += 1LL * (1 + len) * len / 2 % mod;
        }
        return ans % mod;
    }
};

int main(int argc, char const *argv[]) {
    Solution1759 solu;
    cout << solu.countHomogenous("abbcccaa") << endl;
    return 0;
}