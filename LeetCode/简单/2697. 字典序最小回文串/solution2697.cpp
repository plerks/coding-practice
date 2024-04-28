// https://leetcode.cn/problems/lexicographically-smallest-palindrome/description/

#include <bits/stdc++.h>

using namespace std;

class Solution2697 {
public:
    string makeSmallestPalindrome(string s) {
        int n = s.size();
        for (int i = 0; i < n; i++) {
            if (s[i] != s[n - 1 - i]) {
                if (s[i] < s[n - 1 - i]) {
                    s[n - 1 - i] = s[i];
                }
                else s[i] = s[n - 1 - i];
            }
        }
        return s;
    }
};

int main(int argc, char const *argv[]) {
    Solution2697 solu;
    cout << solu.makeSmallestPalindrome("egcfe") << endl;
    return 0;
}