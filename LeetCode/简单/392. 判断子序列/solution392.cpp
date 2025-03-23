/*
url: https://leetcode.cn/problems/is-subsequence/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution392 {
public:
    bool isSubsequence(string s, string t) { // 判断s是否为t的子序列
        int i = 0, j = 0;
        while (i < s.size() && j < t.size()) {
            if (s[i] == t[j]) {
                i++; j++;
            }
            else j++;
        }
        return i == s.size();
    }
};

int main(int argc, char const *argv[]) {
    Solution392 solu;
    cout << solu.isSubsequence("abc", "ahbgdc") << endl;
    return 0;
}