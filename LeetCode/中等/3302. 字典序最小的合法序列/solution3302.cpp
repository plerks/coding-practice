/*
url: https://leetcode.cn/problems/find-the-lexicographically-smallest-valid-sequence/description/
参考: https://leetcode.cn/problems/find-the-lexicographically-smallest-valid-sequence/solutions/2934051/qian-hou-zhui-fen-jie-zi-xu-lie-pi-pei-t-le8d/
相关: LeetCode3303. 第一个几乎相等子字符串的下标, 典型问题/Z函数
标签: LeetCode第140场双周赛, 前后缀分解, 前后缀分解例题, 字符串, 子序列, 字典序
*/

#include <bits/stdc++.h>

using namespace std;

class Solution3302 {
public:
    vector<int> validSequence(string word1, string word2) {
        /* 前后缀分解word1，枚举前缀长度，假设前缀匹配的长度是x，若后缀匹配的长度够长（或者使用字符改变机会后够长），则说明这就是一个可行解，
        字符改变应该不吝啬地使用，以获得字典序最小的结果。
        由于是从左到右遍历的，于是前面选出的是字典序最小的。然后关键在于，后缀匹配的长度是尽量靠右的，不是字典序
        最小，所以还要继续循环找字典序最小的其它部分
        */
        int n = word1.size();
        int m = word2.size();
        vector<int> suf(n + 1); // suf[i]表示word1[i:]匹配word2的开始下标
        suf[n] = m; // 后面有suf[i + 1]，所以需要suf[n]
        for (int i = n - 1, j = m - 1; i >= 0; i--) {
            if (word1[i] == word2[j]) j--;
            if (j < 0) break;
            suf[i] = j + 1;
        }
        int j = 0; // j代表word2前缀已经匹配了的字符的个数，也代表下一个尝试匹配word2的位置
        bool changed = false;
        vector<int> ans(m);
        for (int i = 0; i < n; i++) {
            /* 如果word1[i] == word2[j]，则直接加入ans，否则，如果能够改字符，且，改字符后能在后续匹配上word2的
            剩余部分，那么应该直接在当前用掉这次改动机会，以获得字典序最小
            */
            if (word1[i] == word2[j] || !changed && suf[i + 1] <= j + 1) {
                if (word1[i] == word2[j]) {
                    ans[j] = i;
                    j++;
                }
                else {
                    changed = true;
                    ans[j] = i;
                    j++;
                }
                if (j == m) return ans;
            }
        }
        return {};
    }
};

int main(int argc, char const *argv[]) {
    Solution3302 solu;
    auto a = solu.validSequence("vbcca", "abc");
    for (int x : a) cout << x << " ";
    return 0;
}
