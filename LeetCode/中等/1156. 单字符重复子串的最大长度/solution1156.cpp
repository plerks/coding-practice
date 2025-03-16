/*
url: https://leetcode.cn/problems/swap-for-longest-repeated-character-substring/
相关: LeetCode424. 替换后的最长重复字符
标签: 【题单】滑动窗口与双指针, [special]
*/
#include <bits/stdc++.h>

using namespace std;

class Solution1156 {
public:
    /* 一个错误的解法，从右端点考虑，让nums[r]以外的字符在窗口内最多出现一次，
    但是对于"aaabaaa"，当r在b时，会让窗口变成ab，最后的结果是错的。
    */
    int maxRepOpt1_wa(string s) {
        int n = s.size();
        int cnt[26]{};
        int full[26]{};
        for (char c : s) full[c - 'a']++;
        int total = 0;
        int ans = 0;
        for (int l = 0, r = 0; r < n; r++) {
            total++;
            cnt[s[r] - 'a']++;
            while (total - cnt[s[r] - 'a'] > 1) {
                total--;
                cnt[s[l] - 'a']--;
                l++;
            }
            if ((total - cnt[s[r] - 'a']) == 0 || full[s[r] - 'a'] > cnt[s[r] - 'a']) ans = max(ans, r - l + 1);
            else ans = max(ans, r - l);
        }
        return ans;
    }

    // 另一个错误的解法，枚举字母，60 / 61 个通过的测试用例，处理不了"aabba"这种情况
    int maxRepOpt1_wa2(string s) {
        // 窗口内最多一个其它字符，记录窗口内的总字符数和各种字符的数量，这样就能知道杂字符的数量
        // 如果外部还有其他nums[r]，则换入进来
        int n = s.size();
        int full[26]{};
        for (char c : s) full[c - 'a']++;
        int ans = 0;
        // 枚举每种字母
        for (char c = 'a'; c <= 'z'; c++) {
            int cnt[26]{};
            int total = 0;
            for (int l = 0, r = 0; r < n; r++) {
                total++;
                cnt[s[r] - 'a']++;
                if (s[r] != c) continue;
                while (total - cnt[s[r] - 'a'] > 1) {
                    total--;
                    cnt[s[l] - 'a']--;
                    l++;
                }
                if ((total - cnt[s[r] - 'a']) == 0 || full[s[r] - 'a'] > cnt[s[r] - 'a']) ans = max(ans, r - l + 1);
                else ans = max(ans, r - l);
            }
        }
        return ans;
    }

    /* 参考<https://leetcode.cn/problems/swap-for-longest-repeated-character-substring/solutions/3081679/hua-dong-chuang-kou-by-hxxyyyang-8tbb/>
    不要固定窗口内出现得多的那种字符是s[r]，而是把窗口限制定为：最多2种字符，且出现次数少的那种字符出现次数<=1，
    这样l是单调的，且能枚举所有可能的长度为正解的区间。若窗口内高频率字符的频率 < 总个数，则可以换一个进来。
    */
    int maxRepOpt1(string s) {
        int n = s.size();
        int ans = 0;
        unordered_map<char, int> cnt;
        unordered_map<char, int> total;
        for (char c : s) total[c]++;
        for (int l = 0, r = 0; r < n; r++) {
            cnt[s[r]]++;
            while (true) {
                if (cnt.size() > 2) {
                    cnt[s[l]]--;
                    if (cnt[s[l]] == 0) cnt.erase(s[l]);
                    l++;
                }
                else if (cnt.size() == 2 && min(cnt.begin()->second, std::next(cnt.begin())->second) > 1) {
                    cnt[s[l]]--;
                    l++;
                }
                else break;
            }
            if (cnt.size() == 1) ans = max(ans, r - l + 1);
            else { // size == 2
                auto it1 = cnt.begin(), it2 = std::next(cnt.begin());
                auto [ch, freq] = it1->second > it2->second ? *it1 : *it2;
                if (freq < total[ch]) ans = max(ans, r - l + 1);
                else ans = max(ans, r - l);
            }
        }
        return ans;
    }

    /* 用LeetCode424. 替换后的最长重复字符官方题解的那种特殊做法，
    参考<https://leetcode.cn/problems/swap-for-longest-repeated-character-substring/solutions/3603440/ling-shen-ti-dan-zui-jian-dan-de-zuo-fa-161nz/>
    */
    int maxRepOpt1_implementation2(string s) {
        /* 这里maxFreq的含义是，保留至少一个字符用于交换的移动，剩下在窗口中的最大频率是多少。
        例如，s = "aaaab"，现在尝试窗口[0, 3]是否合法，窗口中安全的a有3个，"外面"还有一个a用于交换，
        这个长为4的窗口是否能调整成全是a？由于还保障了一个a可交换，所以4 - 3 是 <= 1的，也就是说，预留
        了一个用于交换的a，在需要交换的次数<=1时，是可以满足这个交换需求的。如果本身a就已经在窗口内了(也就是上面的情况)，
        相当于交换是原地交换，更加能满足需求。
        */
        int n = s.size();
        int maxFreq = 0;
        int cnt[26]{};
        int total[26]{};
        for (char c : s) total[c - 'a']++;
        int l = 0, r = 0;
        for (; r < n; r++) {
            cnt[s[r] - 'a']++;
            if (total[s[r] - 'a'] > cnt[s[r] - 'a']) {
                maxFreq = max(maxFreq, cnt[s[r] - 'a']);
            }
            if (r - l + 1 - maxFreq > 1) {
                cnt[s[l] - 'a']--;
                l++;
            }
        }
        return n - l; // 写r - l / min(maxFreq + 1, n)都行
    }
};

int main(int argc, char const *argv[]) {
    Solution1156 solu;
    cout << solu.maxRepOpt1("ababa") << endl;
    cout << solu.maxRepOpt1("aaabaaa") << endl;
    cout << solu.maxRepOpt1("aabba") << endl;

    // cout << solu.maxRepOpt1_implementation2("ababa") << endl;
    // cout << solu.maxRepOpt1_implementation2("aaabaaa") << endl;
    // cout << solu.maxRepOpt1_implementation2("aabba") << endl;
    cout << solu.maxRepOpt1_implementation2("aaaab") << endl;
    return 0;
}