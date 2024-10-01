/*
url: https://leetcode.cn/problems/subsequence-with-the-minimum-score/description/
参考: https://leetcode.cn/problems/subsequence-with-the-minimum-score/solutions/2107010/qian-hou-zhui-fen-jie-san-zhi-zhen-pytho-6cmr/
相关: LeetCode3302. 字典序最小的合法序列
标签: 前后缀分解, 前后缀分解例题, 字符串, 子序列
*/

// LeetCode3302. 字典序最小的合法序列 用到此题

#include <bits/stdc++.h>

using namespace std;

class Solution2565 {
public:
    // 参考灵茶山艾府题解，但是把pre和suf数组都定义出来了
    int minimumScore(string s, string t) {
        /* 对s的每个i位置，考虑s[:i]和s[i+1:]能匹配t的长度，若匹配不完整t，则缺失的长度就是t需要删除的
        */
        int n = s.size();
        int m = t.size();
        vector<int> pre(n); // pre[i]表示s[:i]匹配t的结束下标
        for (int i = 0, j = 0; i < n; i++) {
            if (s[i] == t[j]) { // 如果s[i]能和t下一个要匹配的字符对上
                j++;
            }
            if (j == m) return 0; // t是s的子串，直接返回0
            pre[i] = j - 1; // 上一个匹配的字符是j - 1位置
        }
        vector<int> suf(n + 1); // suf[i]表示s[i:]匹配t的开始下标
        suf[n] = m; // 后面有suf[i + 1]，所以需要suf[n]
        // 这里只关心匹配长度，不关心匹配时字符是尽量往前还是往后
        for (int i = n - 1, j = m - 1; i >= 0; i--) {
            if (s[i] == t[j]) {
                j--;
            }
            if (j == -1) return 0;
            suf[i] = j + 1;
        }
        // 这里初值必须是suf[0]，否则漏了一种情况！
        // 这里枚举的逻辑是，对于s[:i]，尽量把t的字符匹配到s[:i]的范围内，然后后缀[i+1:]也尽量放t的字符，然后看t中间放不进去的部分有多长
        // 也就是，把s分成前缀[:i]和后缀[i+1:]，然后把t匹配进去
        // suf[0]对应前缀长为0的情况
        /*
        以s,t内部字符各不相同为例，假设s和t的最优匹配关系是
        -----------------
         O O X O X O O
        其中O代表匹配，X代表无法匹配的字符
        在第一个O处划分，后缀只能匹配2个字符，于是会认定需要删除3个字符
        而在第二个O处划分，前缀匹配2个，后缀匹配2个，于是会认定需要删除2个字符
        所以，所有划分方式都需要遍历，才不会错过最优解
        */
        int ans = suf[0];
        for (int i = 0; i < n; i++) {
            // [pre[i] + 1, suf[i + 1] - 1]这段是要删除的
            ans = min(ans, suf[i + 1] - pre[i] - 1);
        }
        return ans;
    }

    // 参考灵茶山艾府题解，在枚举前缀长度过程中计算pre
    int minimumScore_implementation2(string s, string t) {
        int n = s.size();
        int m = t.size();
        vector<int> suf(n + 1);
        suf[n] = m;
        // 这里只关心匹配长度，不关心匹配时字符是尽量往前还是往后
        for (int i = n - 1, j = m - 1; i >= 0; i--) {
            if (s[i] == t[j]) {
                j--;
            }
            if (j == -1) return 0;
            suf[i] = j + 1;
        }
        int ans = suf[0];
        int j = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == t[j]) j++;
            ans = min(ans, suf[i + 1] - j);
        }
        return ans;
    }
};

int main(int argc, char const *argv[]) {
    Solution2565 solu;
    // cout << solu.minimumScore("abacaba", "bzaa") << endl;
    // cout << solu.minimumScore("acdedcdbabecdbebda", "bbecddb") << endl;
    cout << solu.minimumScore("gbjbacdiiiecgceeafdcdhjhhcjfchjbejibhejgjhhhjhifahfbbcfcajehjgcjgffjdejbhjahgffgdaifhhgaadjiabfdf", "hidefgbgjghceagdaaib") << endl;
    cout << solu.minimumScore_implementation2("gbjbacdiiiecgceeafdcdhjhhcjfchjbejibhejgjhhhjhifahfbbcfcajehjgcjgffjdejbhjahgffgdaifhhgaadjiabfdf", "hidefgbgjghceagdaaib") << endl;
    return 0;
}
