// https://leetcode.cn/problems/find-the-index-of-the-first-occurrence-in-a-string/
#include <bits/stdc++.h>

using namespace std;

class Solution28 {
public:
    int strStr(string haystack, string needle) {
        return match(haystack, needle);
    }

    int strStr_implementation2(string haystack, string needle) {
        return optimized_match(haystack, needle);
    }

    vector<int> build_next(string p) {
        int m = p.size();
        vector<int> next(m, 0);
        next[0] = -1;
        int t = -1; // t 为 非改进next[j - 1]
        for (int i = 1; i < m; i++) {
            while (t != -1 && p[t] != p[i - 1]) t = next[t];
            ++t;
            next[i] = t;
        }
        return next;
    }

    vector<int> build_optimized_next(string p) {
        int m = p.size();
        vector<int> next(m, 0);
        next[0] = -1;
        int t = -1; // t 为 非改进next[j - 1]
        for (int i = 1; i < m; i++) {
            while (t != -1 && p[t] != p[i - 1]) t = next[t];
            ++t;
            next[i] = (p[t] != p[i]) ? t : next[t];
        }
        return next;
    }

    int match(string s, string p) {
        int n = s.size(), m = p.size();
        vector<int> next = build_next(p);
        int i = 0, j = 0;
        while (i < n && j < m) {
            if (j == -1 || s[i] == p[j]) {
                i++;
                j++;
            }
            else j = next[j];
        }
        return (j == m) ? i - j : -1;
    }

    int optimized_match(string s, string p) {
        int n = s.size(), m = p.size();
        vector<int> next = build_optimized_next(p);
        int i = 0, j = 0;
        while (i < n && j < m) {
            if (j == -1 || s[i] == p[j]) {
                i++;
                j++;
            }
            else j = next[j];
        }
        return (j == m) ? i - j : -1;
    }
};

int main(int argc, char const *argv[]) {
    Solution28 solu;
    cout << solu.strStr("a", "a") << endl;
    cout << solu.strStr_implementation2("a", "a") << endl;
    return 0;
}