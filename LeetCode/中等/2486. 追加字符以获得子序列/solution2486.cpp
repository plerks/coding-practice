/*
url: https://leetcode.cn/problems/append-characters-to-string-to-make-subsequence/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2486 {
public:
    int appendCharacters(string s, string t) {
        int n = s.size(), m = t.size();
        int i = 0, j = 0;
        while (i < n) {
            if (s[i] == t[j]) {
                i++; j++;
            }
            else i++;
        }
        return m - j;
    }
};

int main(int argc, char const *argv[]) {
    Solution2486 solu;
    cout << solu.appendCharacters("coaching", "coding") << endl;
    cout << solu.appendCharacters("lbg", "g") << endl;
    return 0;
}