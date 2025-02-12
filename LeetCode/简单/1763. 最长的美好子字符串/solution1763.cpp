/*
url: https://leetcode.cn/problems/longest-nice-substring/
相关: LeetCode395. 至少有 K 个重复字符的最长子串
标签: 【题单】滑动窗口与双指针
*/

#include <bits/stdc++.h>

using namespace std;

class Solution1763 {
public:
    // 具体见`LeetCode395. 至少有 K 个重复字符的最长子串`中的滑窗写法，是个巧妙的技巧
    string longestNiceSubstring(string s) {
        int n = s.size();
        int maxLen = 0;
        string ans;
        for (int t = 1; t < n; t++) {
            int l = 0;
            int all = 0; // 窗口中字母种类
            int cnt = 0; // 窗口中大小写都出现的字母种类
            int upper[26]{};
            int lower[26]{};
            for (int r = 0; r < n; r++) {
                int index = tolower(s[r]) - 'a';
                if (islower(s[r])) {
                    if (!lower[index] && !upper[index]) all++;
                    if (!lower[index] && upper[index]) cnt++;
                    lower[index]++;
                }
                else {
                    if (!lower[index] && !upper[index]) all++;
                    if (lower[index] && !upper[index]) cnt++;
                    upper[index]++;
                }
                while (all > t) {
                    int index = tolower(s[l]) - 'a';
                    if (islower(s[l])) {
                        if (lower[index] == 1 && !upper[index]) all--;
                        if (lower[index] == 1 && upper[index]) cnt--; // 注意这里还要判断upper[index] > 0，不然会导致cnt多减变成负数
                        lower[index]--;
                    }
                    else {
                        if (!lower[index] && upper[index] == 1) all--;
                        if (upper[index] == 1 && lower[index]) cnt--;
                        upper[index]--;
                    }
                    l++;
                }
                if (all == cnt && r - l + 1 > maxLen) {
                    maxLen = max(maxLen, r - l + 1);
                    ans = s.substr(l, r - l + 1);
                }
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution1763 solu;
    cout << solu.longestNiceSubstring("YazaAay") << endl;
    return 0;
}