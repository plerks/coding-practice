/*
url: https://leetcode.cn/problems/smallest-subsequence-of-distinct-characters/
相关: LeetCode316. 去除重复字母
标签: 【算法题单】单调栈, 字典序
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1081 {
public:
    // 此题与 LeetCode316. 去除重复字母 完全相同
    string smallestSubsequence(string s) {
        int n = s.size();
        int cnt[26]{}; // s剩余部分字母剩余个数
        for (char c : s) cnt[c - 'a']++;
        int contain[26]{};
        vector<char> st;
        for (int i = 0; i < n; i++) {
            cnt[s[i] - 'a']--;
            if (contain[s[i] - 'a']) {
                continue;
            }
            while (!st.empty() && st.back() >= s[i] && cnt[st.back() - 'a'] > 0) {
                contain[st.back() - 'a']--;
                st.pop_back();
            }
            contain[s[i] - 'a']++;
            st.push_back(s[i]);
        }
        string ans;
        for (char c : st) {
            ans.push_back(c);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1081 solu;
    cout << solu.smallestSubsequence("bcabc") << endl;
    return 0;
}