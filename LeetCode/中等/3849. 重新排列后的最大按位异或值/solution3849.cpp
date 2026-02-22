/*
url: https://leetcode.cn/problems/maximum-bitwise-xor-after-rearrangement/
标签: LeetCode第490场周赛
*/
#include <bits/stdc++.h>

using namespace std;

class Solution3849 {
public:
    string maximumXor(string s, string t) {
        int n = s.size();
        int cnt[2]{};
        for (char c : t) cnt[c - '0']++;
        string ans = s;
        for (int i = 0; i < n; i++) {
            int cand = (s[i] - '0') ^ 1;
            if (cnt[cand] == 0) cand ^= 1;
            ans[i] = ((s[i] - '0') ^ cand) + '0';
            cnt[cand]--;
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}