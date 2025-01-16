/*
url: https://leetcode.cn/problems/find-all-anagrams-in-a-string/
相关: LeetCode1888. 使二进制字符串字符交替的最少反转次数
标签: 【题单】滑动窗口与双指针
*/
#include <bits/stdc++.h>

using namespace std;

class Solution438 {
public:
    // 这题与LeetCode1888相同
    vector<int> findAnagrams(string s, string p) {
        int m = s.size();
        int n = p.size();
        int diff[26]{};
        for (char c : p) diff[c - 'a']--;
        vector<int> ans;
        int r = m - 1;
        for (int l = m - 1; l >= 0; l--) {
            int x = s[l] - 'a';
            diff[x]++;
            // 窗口内多余的字符丢掉，所有字符由l引入，因此窗口内一直没有多余的字符，相等/少
            while (diff[x] > 0) {
                diff[s[r] - 'a']--;
                r--;
            }
            if (r - l + 1 == n) ans.push_back(l);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution438 solu;
    auto a = solu.findAnagrams("cbaebabacd", "abc");
    return 0;
}