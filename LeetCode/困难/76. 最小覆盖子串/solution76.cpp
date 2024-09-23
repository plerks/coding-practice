/*
url: https://leetcode.cn/problems/minimum-window-substring/description/
参考: https://www.bilibili.com/video/BV1WRtDejEjD/
相关: LeetCode3297. 统计重新排列后包含另一个字符串的子字符串数目 I, LeetCode3298. 统计重新排列后包含另一个字符串的子字符串数目 II
标签: 滑动窗口
*/

#include <bits/stdc++.h>

using namespace std;

// LeetCode3298. 统计重新排列后包含另一个字符串的子字符串数目 II用到此题
class Solution76 {
public:
    string minWindow(string s, string t) {
        int n = s.size();
        unordered_map<int, int> diff; // 统计字母频率之差
        for (char c : t) {
            diff[c - 'a']--;
        }

        int count = 0; // s不够频率的字母个数
        for (auto &d : diff) {
            count += (d.second < 0);
        }

        int left = 0;
        int start = 0;
        int minLen = n + 1;
        for (int right = 0; right < n; right++) {
            int c = s[right] - 'a';
            diff[c]++;
            if (diff[c] == 0) {
                count--;
            }
            while (count == 0) {
                int c2 = s[left] - 'a';
                diff[c2]--;
                if (diff[c2] == -1) {
                    count++;
                }
                left++;
            }
            // 题目保证最小子串唯一
            if (left > 0) { // 如果left > 0，说明有合法子串[left - 1, right]
                if (right - left + 2 < minLen) {
                    minLen = right - left + 2;
                    start = left - 1;
                }
            }
        }
        return minLen == n + 1 ? "" : s.substr(start, minLen);
    }
};

int main(int argc, char const *argv[]) {
    Solution76 solu;
    // cout << solu.minWindow("ADOBECODEBANC", "ABC") << endl;
    cout << solu.minWindow("ab", "a") << endl;
    return 0;
}
