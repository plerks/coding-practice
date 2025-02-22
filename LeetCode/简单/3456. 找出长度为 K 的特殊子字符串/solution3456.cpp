/*
url: https://leetcode.cn/problems/find-special-substring-of-length-k/
标签: LeetCode第437场周赛
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3456 {
public:
    // 周赛时的暴力解法，通过
    bool hasSpecialSubstring(string s, int k) {
        int n = s.size();
        for (int i = 0; i < 26; i++) {
            char ch = 'a' + i;
            string sub(k, ch);
            int start = 0;
            while (true) {
                int index = s.find(sub, start);
                if (index == -1) break;
                start = index + k;
                if ((index - 1 < 0 || s[index - 1] != ch) && (index + k >= n || s[index + k] != ch)) return true;
            }
        }
        return false;
    }

    // 用分组循环分段，看有没有长度为k的就行
    bool hasSpecialSubstring_implementation2(string s, int k) {
        int n = s.size();
        for (int i = 0; i < n;) {
            int start = i;
            for (i++; i < n && s[i] == s[i - 1]; i++);
            if (i - start == k) return true;
        }
        return false;
    }
};

int main(int argc, char const *argv[]) {
    Solution3456 solu;
    cout << solu.hasSpecialSubstring("aaaa", 3) << endl;
    cout << solu.hasSpecialSubstring_implementation2("aaaa", 3) << endl;
    return 0;
}