/*
url: https://leetcode.cn/problems/next-greater-element-i/
相关: LeetCode1081. 不同字符的最小子序列
标签: 【算法题单】单调栈, 字典序
*/
#include <bits/stdc++.h>

using namespace std;

class Solution316 {
public:
    // 当前的s[i]让栈中比自己大，且后面还有剩的元素出栈，如果当前st已经有了s[i]，则跳过
    string removeDuplicateLetters(string s) {
        int n = s.size();
        int cnt[26]{}; // 字母剩余个数，包含栈中的和s剩余部分
        for (char c : s) cnt[c - 'a']++;
        int contain[26]{};
        vector<char> st;
        for (int i = 0; i < n; i++) {
            if (contain[s[i] - 'a']) {
                cnt[s[i] - 'a']--;
                continue;
            }
            while (!st.empty() && st.back() >= s[i] && cnt[st.back() - 'a'] > 1) {
                cnt[st.back() - 'a']--;
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
    Solution316 solu;
    // cout << solu.removeDuplicateLetters("bcabc") << endl;
    // cout << solu.removeDuplicateLetters("cbacdcbc") << endl;
    // cout << solu.removeDuplicateLetters("abacb") << endl;
    cout << solu.removeDuplicateLetters("bbcaac") << endl;
    return 0;
}