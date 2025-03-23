/*
url: https://leetcode.cn/problems/camelcase-matching/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1023 {
public:
    // LeetCode392. 判断子序列
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
    
    vector<bool> camelMatch(vector<string>& queries, string pattern) {
        int n = queries.size();
        vector<bool> ans(n);
        for (int i = 0; i < queries.size(); i++) {
            string &s = queries[i];
            ans[i] = false;
            if (isSubsequence(pattern, s)) {
                int cnt1 = 0, cnt2 = 0;
                for (char c : s) if (isupper(c)) cnt1++;
                for (char c : pattern) if (isupper(c)) cnt2++;
                if (cnt1 == cnt2) ans[i] = true;
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1023 solu;
    auto a = solu.camelMatch(*new vector<string>{"FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"}, "FB");
    return 0;
}