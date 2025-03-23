/*
url: https://leetcode.cn/problems/longest-word-in-dictionary-through-deleting/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution524 {
public:
    string findLongestWord(string s, vector<string>& dictionary) {
        string ans;
        for (string &w : dictionary) {
            if (!check(s, w)) continue;
            if (w.size() > ans.size()) ans = w;
            else if (w.size() == ans.size()) ans = min(ans, w);
        }
        return ans;
    }

    bool check(const string& s, const string &w) {
        int i = 0, j = 0;
        while (i < w.size()) {
            if (j == s.size()) return false;
            if (w[i] == s[j]) {
                i++; j++;
            }
            else j++;
        }
        return true;
    }
};

int main(int argc, char const *argv[]) {
    Solution524 solu;
    cout << solu.findLongestWord("abpcplea", *new vector<string>{"ale","apple","monkey","plea"}) << endl;
    return 0;
}