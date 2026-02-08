/*
url: https://leetcode.cn/problems/reverse-letters-then-special-characters-in-a-string/
标签: LeetCode第175场双周赛
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3823 {
public:
    // 双周赛时的写法。可以根据是字母还是特殊字符，原地双指针左右对称交换两轮，空间复杂度O(1)，见灵茶题解
    string reverseByType(string s) {
        int n = s.size();
        vector<int> g1;
        vector<int> g2;
        for (int i = 0; i < n; i++) {
            if ('a' <= s[i] && s[i] <= 'z') {
                g1.push_back(i);
            }
            else g2.push_back(i);
        }
        reverse(g1.begin(), g1.end());
        reverse(g2.begin(), g2.end());
        string ans = s;
        int p1 = 0, p2 = 0;
        for (int i = 0; i < n; i++) {
            if ('a' <= s[i] && s[i] <= 'z') {
                ans[i] = s[g1[p1++]];
            }
            else ans[i] = s[g2[p2++]];
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}