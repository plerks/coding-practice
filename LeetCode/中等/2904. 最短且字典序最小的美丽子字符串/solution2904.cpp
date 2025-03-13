/*
url: https://leetcode.cn/problems/shortest-and-lexicographically-smallest-beautiful-string/
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution2904 {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int n = s.size();
        int minLen = n + 1;
        string ans;
        int l = 0;
        int cnt = 0; // 窗口1的个数
        for (int r = 0; r < n; r++) {
            cnt += s[r] - '0';
            // 或者while (s[l] == '0' || cnt > k)
            while (l <= r && cnt - (s[l] - '0') >= k) { // 这里可以不写 l <= r
                cnt -= s[l] - '0';
                l++;
            }
            if (cnt == k) {
                int len = r - l + 1;
                if (len < minLen) {
                    minLen = len;
                    ans = s.substr(l, len);
                }
                else if (len == minLen) ans = min(ans, s.substr(l, len));
            }
        }
        return ans;
    }

    // 换一种比较标准的写法
    string shortestBeautifulSubstring_implementation2(string s, int k) {
        int n = s.size();
        int minLen = n + 1;
        string ans;
        int l = 0;
        int cnt = 0; // 窗口1的个数
        for (int r = 0; r < n; r++) {
            cnt += s[r] - '0';
            while (cnt >= k) {
                cnt -= s[l] - '0';
                l++;
            }
            if (l != 0) { // [l - 1, r]为不合法窗口
                int len = r - l + 2; // [l - 1, r]为最小合法窗口
                if (len < minLen) {
                    minLen = len;
                    ans = s.substr(l - 1, len);
                }
                else if (len == minLen) ans = min(ans, s.substr(l - 1, len));
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2904 solu;
    // cout << solu.shortestBeautifulSubstring("100011001", 3) << endl;
    cout << solu.shortestBeautifulSubstring_implementation2("11000111", 1) << endl;
    return 0;
}