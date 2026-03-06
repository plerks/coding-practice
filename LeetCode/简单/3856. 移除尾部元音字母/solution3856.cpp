/*
url: https://leetcode.cn/problems/trim-trailing-vowels/
标签: LeetCode第491场周赛
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3856 {
public:
    string trimTrailingVowels(string s) {
        int n = s.size();
        set<char> st{'a', 'e', 'i', 'o', 'u'};
        int r = n - 1;
        while (r >= 0 && st.count(s[r])) r--;
        return s.substr(0, r + 1);
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}