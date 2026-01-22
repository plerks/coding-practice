/*
url: https://leetcode.cn/problems/vowel-consonant-score/
标签: LeetCode第485场周赛
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3813 {
public:
    int vowelConsonantScore(string s) {
        int mask = 0;
        mask |= (1 << ('a' - 'a'));
        mask |= (1 << ('e' - 'a'));
        mask |= (1 << ('i' - 'a'));
        mask |= (1 << ('o' - 'a'));
        mask |= (1 << ('u' - 'a'));
        int v = 0, c = 0;
        for (char ch : s) {
            if (ch == ' ' || isdigit(ch)) continue;
            if (mask & (1 << (ch - 'a'))) v++;
            else c++;
        }
        return c == 0 ? 0 : (v / c);
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}