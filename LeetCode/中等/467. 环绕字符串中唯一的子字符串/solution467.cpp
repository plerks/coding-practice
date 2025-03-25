/*
url: https://leetcode.cn/problems/unique-substrings-in-wraparound-string/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution467 {
public:
    int findSubstringInWraproundString(string s) {
        int n = s.size();
        long long ans = 0;
        int cnt[26]{}; // 枚举每个字母作为头，最长能多长
        for (int i = 0; i < n;) {
            int start = i;
            for (i++; i < n && s[i] == (s[i - 1] - 'a' + 1) % 26 + 'a'; i++);
            // [start, i)
            for (int j = start; j < i; j++) {
                cnt[s[j] - 'a'] = max(cnt[s[j] - 'a'], i - j);
            }
        }
        for (int len : cnt) ans += len;
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution467 solu;
    cout << solu.findSubstringInWraproundString("cac") << endl;
    cout << solu.findSubstringInWraproundString("zab") << endl;
    return 0;
}