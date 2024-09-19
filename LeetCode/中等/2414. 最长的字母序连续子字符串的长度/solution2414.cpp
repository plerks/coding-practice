// https://leetcode.cn/problems/length-of-the-longest-alphabetical-continuous-substring/description/?envType=daily-question&envId=2024-09-19

#include <bits/stdc++.h>

using namespace std;

class Solution2414 {
public:
    int longestContinuousSubstring(string s) {
        int pre = 1;
        int n = s.size();
        int ans = 1;
        for (int i = 1; i < n; i++) {
            if (s[i] == s[i - 1] + 1) {
                pre++;
            }
            else pre = 1;
            ans = max(ans, pre);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2414 solu;
    cout << solu.longestContinuousSubstring("abacaba") << endl;
    return 0;
}
