/*
url: https://leetcode.cn/problems/minimum-length-of-string-after-deleting-similar-ends/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1750 {
public:
    int minimumLength(string s) {
        int n = s.size();
        int l = 0, r = n - 1;
        while (l < r) { // l == r时不能删除，也直接退出
            if (s[l] != s[r]) break;
            int ll = l, rr = r;
            while (ll < r && s[ll] == s[l]) ll++; // [l, ll - 1]全相等
            while (rr > ll - 1 && s[rr] == s[r]) rr--; // [rr + 1, r]全相等
            l = ll;
            r = rr;
        }
        return r - l + 1;
    }
};

int main(int argc, char const *argv[]) {
    Solution1750 solu;
    // cout << solu.minimumLength("cabaabac") << endl;
    // cout << solu.minimumLength("aabccabba") << endl;
    cout << solu.minimumLength("bcbcb") << endl;
    return 0;
}