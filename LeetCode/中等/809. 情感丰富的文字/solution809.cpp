/*
url: https://leetcode.cn/problems/expressive-words/
相关: LeetCode925. 长按键入
标签: 【题单】滑动窗口与双指针, 分组循环
*/
#include <bits/stdc++.h>

using namespace std;

class Solution809 {
public:
    int expressiveWords(string s, vector<string>& words) {
        int ans = 0;
        for (string &w : words) {
            if (check(w, s)) ans++;
        }
        return ans;
    }

    bool check(const string &w, const string &s) {
        int n = w.size(), m = s.size();
        int i1 = 0, i2 = 0;
        for (; i1 < n && i2 < m;) {
            int start1 = i1, start2 = i2;
            if (w[start1] != s[start2]) return false;
            for (i1++; i1 < n && w[i1] == w[i1 - 1]; i1++);
            for (i2++; i2 < m && s[i2] == s[i2 - 1]; i2++);
            // 前面已经判断了字符相同
            int len1 = i1 - start1, len2 = i2 - start2;
            if (!(len1 == len2 || (len1 < len2 && len2 >= 3))) return false; 
        }
        return i1 == n && i2 == m; // 若w或s有剩余字母，则要返回false
    }
};

int main(int argc, char const *argv[]) {
    Solution809 solu;
    // cout << solu.expressiveWords("heeellooo", *new vector<string>{"hello", "hi", "helo"}) << endl;
    // cout << solu.expressiveWords("abcd", *new vector<string>{"abc"}) << endl;
    // cout << solu.expressiveWords("heeellooo", *new vector<string>{"heeelloooworld"}) << endl;
    cout << solu.expressiveWords("dddiiiinnssssssoooo", *new vector<string>{"dinnssoo","ddinso","ddiinnso","ddiinnssoo","ddiinso","dinsoo","ddiinsso","dinssoo","dinso"}) << endl;
    return 0;
}